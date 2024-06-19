#include "..//header//gamehandler.h"
#include "../header/globals.h"
#include <stdlib.h>

GameHandler::GameHandler()
{
   m_nrOfPellets = 0;
   for(int i = 0; i < 10; i++)
   {
      m_pellets[i] = NULL;
   }

   m_gameWindow = NULL;

   m_gameState = GAMESTATE::GAME_INIT;
   m_input     = SnakeHandler::INPUT::NONE;
}

GameHandler::GameHandler(RenderWindow* window)
{
   Time randTime = m_currentClock.restart();
   srand((unsigned int)randTime.asMicroseconds());

   m_gameState  = GAMESTATE::GAME_INIT;
   m_input      = SnakeHandler::INPUT::NONE;

   m_gameWindow = window;

   loadResource();

   m_nrOfPellets = 3;
   for(int i = 0; i < m_nrOfPellets; i++)
   {
      m_pellets[i] = new Pellets();

      float x = static_cast<float>(rand() % Const_Window::WINDOW_WIDTH);
      float y = static_cast<float>(rand() % Const_Window::WINDOW_HEIGHT);
      m_pellets[i]->setPos(x, y);
   }

   for(int i = m_nrOfPellets; i < 10; i++)
   {
      m_pellets[i] = NULL;
   }

   m_scoreHandler.initText(m_font);

   m_gameState = GAMESTATE::GAME_RUN;
}

GameHandler::~GameHandler()
{
   for(int i = 0; i < 10; i++)
   {
      if(m_pellets[i] != NULL)
      {
         delete m_pellets[i];
      }
   }
}

void
GameHandler::Update()
{
   while(m_gameState == GAMESTATE::GAME_RUN)
   {
      Time dt = m_currentClock.restart();

      m_input = SnakeHandler::INPUT::NONE;
      HandleEvent();

      m_snakeHand.Update(dt.asSeconds(), (int)m_input);
      m_scoreHandler.setAngle(m_snakeHand.getAngle());

      CheckCollition();

      Draw();
   }

   while(m_gameState == GAMESTATE::GAME_PAUS)
   {
      HandleEvent();

      Draw();
   }
}

void
GameHandler::Draw()
{
   m_gameWindow->clear();

   // Background
   m_gameWindow->draw(m_bgSprite);
   
   // Pellets and obsticle
   for(int i = 0; i < m_nrOfPellets; i++)
   {
      m_pellets[i]->Draw(*m_gameWindow);
   }

   // Snake
   m_snakeHand.Draw(*m_gameWindow);

   // Score
   m_scoreHandler.Draw(*m_gameWindow);

   m_gameWindow->display();
}

void
GameHandler::loadResource()
{
   m_bgTexture.loadFromFile("Resources\\Textures\\bg_earth.png");
   m_bgSprite.setTexture(m_bgTexture);

   m_font.loadFromFile("Resources\\Fonts\\Retro Stereo Wide.ttf");
}

void
GameHandler::HandleEvent()
{
   Event event;
   while(m_gameWindow->pollEvent(event))
   {
      switch(event.type)
      {
         case Event::KeyPressed:
            HandleKeyboardEvent(event);
            break;

         default:
            break;
      }
   }
}

void
GameHandler::HandleKeyboardEvent(const Event& event)
{
   switch(event.key.code)
   {
      case Keyboard::Escape:
         if(m_gameState == GAMESTATE::GAME_RUN)
         {
            m_gameState = GAMESTATE::GAME_PAUS;
         }
         else if(m_gameState == GAMESTATE::GAME_PAUS)
         {
            m_gameWindow->close();
            m_gameState = GAMESTATE::GAME_QUIT;
         }
         break;

      case Keyboard::Left:
         m_input = SnakeHandler::INPUT::LEFT;
         break;

      case Keyboard::Right:
         m_input = SnakeHandler::INPUT::RIGHT;
         break;

      case Keyboard::Up:
         m_input = SnakeHandler::INPUT::UP;
         break;

      case Keyboard::Down:
         m_input = SnakeHandler::INPUT::DOWN;
         break;

      default:
         break;
   }
}

bool
GameHandler::CheckCollition()
{
   Snake head = m_snakeHand.getSnakeHead();

   for(int i = 0; i < m_nrOfPellets; i++)
   {
      if(CircleCollition(head, m_pellets[i]->getXpos(), m_pellets[i]->getYpos(), m_pellets[i]->getRadius()))
      {
         float x = static_cast<float>(rand() % Const_Window::WINDOW_WIDTH);
         float y = static_cast<float>(rand() % Const_Window::WINDOW_HEIGHT);
         m_pellets[i]->setPos(x, y);

         m_scoreHandler.addScore(10);
         m_snakeHand.addBody();
         m_snakeHand.addSpeed(0.25f);

         return true;
      }
   }

   for(int i = (int)SnakeHandler::INDEX::INDEX_COLISION; i < m_snakeHand.getLength(); i++)
   {
      if(CircleCollition(head, m_snakeHand.getSnakeBody(i).getXpos(), m_snakeHand.getSnakeBody(i).getYpos(), m_snakeHand.getSnakeBody(i).getRadius()))
      {
         m_scoreHandler.resetScore();
         m_snakeHand.die();
      }
   }
   return false;
}

bool
GameHandler::CircleCollition(Snake head, float xPos, float yPos, float radius)
{
   float totRad = powf(head.getRadius() + radius, 2.0f);

   float deltaX = head.getXpos() - xPos;
   float deltaY = head.getYpos() - yPos;
   float absLen = powf(deltaX, 2.0f) + powf(deltaY, 2.0f);

   if(absLen < totRad)
   {
      return true;
   }

   return false;
}
