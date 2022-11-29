#include "..\header\mainhandler.h"
#include "..\header\globals.h"

MainHandler::MainHandler()
{
   m_state = MAINSTATE::MAIN_INIT;

   initWindow();

   m_game = new GameHandler(m_MainWindow);
}

MainHandler::~MainHandler()
{
   if(m_MainWindow != NULL)
   {
      delete m_MainWindow;
      m_MainWindow = NULL;
   }

   delete m_game;
}

void
MainHandler::initWindow()
{
   m_MainWindow = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake");
}

void
MainHandler::updateMenu()
{

}

void
MainHandler::updateGame()
{
   m_game->Update();

   m_game->Draw();
}

int
MainHandler::Run()
{
   m_state = MAINSTATE::MAIN_GAME;

   while(m_MainWindow->isOpen())
   {
      Event event;
      while(m_MainWindow->pollEvent(event))
      {
         switch(event.type)
         {
            case Event::Closed:
               this->m_MainWindow->close();
               break;

            default:
               break;
         }
      }

      switch(m_state)
      {
         case MAINSTATE::MAIN_MENU:
            updateMenu();
            break;

         case MAINSTATE::MAIN_GAME:
            updateGame();
            break;

         default:
            break;
      }
   }

   return 1;
}
