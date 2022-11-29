#include <math.h>
#include <iostream>

#include "..\header\snakehandler.h"
#include "..\header\snakehead.h"
#include "..\header\snakebody.h"

#include "..\header\globals.h"

using namespace std;

SnakeHandler::SnakeHandler()
{
   //m_angle = PI * 0.5f;
   m_angle = 0.0f;
   m_currSpeed = START_SPEED;

   m_snakeLenght    = 0;
   m_snakeMaxLength = 10;
   m_snake = new Snake * [m_snakeMaxLength];

   for(int i = 0; i < m_snakeMaxLength; i++)
   {
      m_snake[i] = NULL;
   }

   // Load from file once for all body parts.
   m_texture.loadFromFile("Resources\\Textures\\blueMarble.png");

   resetSnake();

//   m_snake[(int)INDEX::INDEX_HEAD] = new SnakeHead(DEFAULT_X_POS, DEFAULT_Y_POS, 0.0f, m_currSpeed);
//   m_snakeLenght++;
/*
   for(int i = 1; i < DEFAULT_BODY; i++)
   {
      m_snake[i] = new SnakeBody(DEFAULT_X_POS, DEFAULT_Y_POS, 0.0f, 0.0f, m_texture);
      m_snakeLenght++;
   }

   for(int i = DEFAULT_BODY; i < m_snakeMaxLength; i++)
   {
      m_snake[i] = NULL;
   }
*/
}

SnakeHandler::~SnakeHandler()
{
   for(int i = 0; i < m_snakeMaxLength; i++)
   {
      if(m_snake[i] != NULL)
      {
         delete m_snake[i];
      }
   }

   delete[] m_snake;
}

void
SnakeHandler::Update(float dt, int input)
{
   // Update head
   float xVel = 0.0f;
   float yVel = 0.0f;

   float xPos = m_snake[(int)INDEX::INDEX_HEAD]->getXpos();
   float yPos = m_snake[(int)INDEX::INDEX_HEAD]->getYpos();

   switch(input)
   {
      /************************************************************
      //       PI * 1.5f
      //   PI              0
      //       PI * 0.5f
      //
      // Always take the shortest way to designated angle
      *************************************************************/
      case (int)INPUT::LEFT:
         // Towards PI
         if(m_angle >= 0.0f && m_angle < PI)
         {
            m_angle = normalize(m_angle + (ROTATION_SPEED * dt));

            if(m_angle > PI)
            {
               m_angle = PI;
            }
         }
         else
         {
            if(m_angle > PI)
            {
               m_angle = normalize(m_angle + (-ROTATION_SPEED * dt));

               if(m_angle < PI)
               {
                  m_angle = PI;
               }
            }
         }
         break;

      case (int)INPUT::RIGHT:
         // Towards 0
         if(m_angle <= PI)
         {
            m_angle = normalize(m_angle + (-ROTATION_SPEED * dt));

            if(m_angle > PI * 1.5f)
            {
               m_angle = 0.0f;
            }
         }
         else
         {
            if(m_angle > PI)
            {
               m_angle = normalize(m_angle + (ROTATION_SPEED * dt));

               if(m_angle < PI * 0.5f)
               {
                  m_angle = 0.0f;
               }
            }
         }
         break;

      case (int)INPUT::UP:
         // Towards PI+PI/2
         if(m_angle >= PI * 0.5f && m_angle < PI * 1.5)
         {
            m_angle = normalize(m_angle + (ROTATION_SPEED * dt));

            if(m_angle > PI * 1.5f)
            {
               m_angle = PI * 1.5f;
            }
         }
         else
         {
            m_angle = normalize(m_angle + (-ROTATION_SPEED * dt));

            if(m_angle < PI * 1.5f && m_angle > PI)
            {
               m_angle = PI * 1.5f;
            }
         }
         break;

      case (int)INPUT::DOWN:
         // Towards PI/2
         if(m_angle <= PI * 1.5f && m_angle > PI * 0.5f)
         {
            m_angle = normalize(m_angle + (-ROTATION_SPEED * dt));

            if(m_angle < PI * 0.5f)
            {
               m_angle = PI * 0.5f;
            }
         }
         else
         {
            m_angle = normalize(m_angle + (ROTATION_SPEED * dt));

            if(m_angle > PI * 0.5f && m_angle < PI)
            {
               m_angle = PI * 0.5f;
            }
         }
         break;

      case (int)INPUT::NONE:
      default:
         break;
   }

   xVel = (cosf(m_angle));
   yVel = (sinf(m_angle));

   m_snake[(int)INDEX::INDEX_HEAD]->setVel(xVel * m_currSpeed, yVel * m_currSpeed);

   xPos = xPos + (m_snake[(int)INDEX::INDEX_HEAD]->getXvel() * dt);
   yPos = yPos + (m_snake[(int)INDEX::INDEX_HEAD]->getYvel() * dt);

   m_snake[(int)INDEX::INDEX_HEAD]->setPos(xPos, yPos);

   /********************************************************************
   * Wrap around the world.
   * Pass back the velocity vector to the next bodypart so
   * the body doesn't follow the head during the position jump.
   * 
   * Set flag for use of velocity vector and pass back the velocity.
   *********************************************************************/
   if(m_snake[(int)INDEX::INDEX_HEAD]->getXpos() < -25.0f)
   {
      m_snake[(int)INDEX::INDEX_HEAD]->setXpos(WINDOW_WIDTH + 25.0f);

      dynamic_cast<SnakeBody*>(m_snake[(int)INDEX::INDEX_HEAD + 1])->setUseVelocityVector(true);
      m_snake[(int)INDEX::INDEX_HEAD + 1]->setVel(m_snake[(int)INDEX::INDEX_HEAD]->getXvel(), m_snake[(int)INDEX::INDEX_HEAD]->getYvel());
   }
   else if(m_snake[(int)INDEX::INDEX_HEAD]->getXpos() > WINDOW_WIDTH + 25.0f)
   {
      m_snake[(int)INDEX::INDEX_HEAD]->setXpos(-25.0f);

      dynamic_cast<SnakeBody*>(m_snake[(int)INDEX::INDEX_HEAD + 1])->setUseVelocityVector(true);
      m_snake[(int)INDEX::INDEX_HEAD + 1]->setVel(m_snake[(int)INDEX::INDEX_HEAD]->getXvel(), m_snake[(int)INDEX::INDEX_HEAD]->getYvel());
   }

   if(m_snake[(int)INDEX::INDEX_HEAD]->getYpos() < -25.0f)
   {
      m_snake[(int)INDEX::INDEX_HEAD]->setYpos(WINDOW_HEIGHT + 25.0f);

      dynamic_cast<SnakeBody*>(m_snake[(int)INDEX::INDEX_HEAD + 1])->setUseVelocityVector(true);
      m_snake[(int)INDEX::INDEX_HEAD + 1]->setVel(m_snake[(int)INDEX::INDEX_HEAD]->getXvel(), m_snake[(int)INDEX::INDEX_HEAD]->getYvel());
   }
   else if(m_snake[(int)INDEX::INDEX_HEAD]->getYpos() > WINDOW_HEIGHT + 25.0f)
   {
      m_snake[(int)INDEX::INDEX_HEAD]->setYpos(-25.0f);

      dynamic_cast<SnakeBody*>(m_snake[(int)INDEX::INDEX_HEAD + 1])->setUseVelocityVector(true);
      m_snake[(int)INDEX::INDEX_HEAD + 1]->setVel(m_snake[(int)INDEX::INDEX_HEAD]->getXvel(), m_snake[(int)INDEX::INDEX_HEAD]->getYvel());
   }

   // Update body
   for(int i = 1; i < m_snakeLenght; i++)
   {
      if(dynamic_cast<SnakeBody*>(m_snake[i])->getUseVelocityVector() == false)
      {
         float dx = m_snake[i - 1]->getXpos() - m_snake[i]->getXpos();
         float dy = m_snake[i - 1]->getYpos() - m_snake[i]->getYpos();
         float angle = atan2f(dy, dx);

         float thightnessFactor = 1.0f;
         m_snake[i]->setXpos(m_snake[i - 1]->getXpos() - cosf(angle) * m_snake[i]->getRadius() * thightnessFactor);
         m_snake[i]->setYpos(m_snake[i - 1]->getYpos() - sinf(angle) * m_snake[i]->getRadius() * thightnessFactor);
      }
      else
      {
         xPos = m_snake[i]->getXpos() + (m_snake[i]->getXvel() * dt);
         yPos = m_snake[i]->getYpos() + (m_snake[i]->getYvel() * dt);

         m_snake[i]->setPos(xPos, yPos);

         /********************************************************************
         * Wrap around the world.
         *
         * Remove the velocity flag and set next.
         * Set flag for use of velocity vector and pass back the velocity.
         *********************************************************************/
         if(m_snake[i]->getXpos() < -25.0f)
         {
            m_snake[i]->setXpos(WINDOW_WIDTH + 25.0f);

            dynamic_cast<SnakeBody*>(m_snake[i])->setUseVelocityVector(false);
            if(i < (m_snakeLenght - 1))
            {
               dynamic_cast<SnakeBody*>(m_snake[i + 1])->setUseVelocityVector(true);
               m_snake[i + 1]->setVel(m_snake[i]->getXvel(), m_snake[i]->getYvel());
            }
         }
         else if(m_snake[i]->getXpos() > WINDOW_WIDTH + 25.0f)
         {
            m_snake[i]->setXpos(-25.0f);

            dynamic_cast<SnakeBody*>(m_snake[i])->setUseVelocityVector(false);
            if(i < (m_snakeLenght - 1))
            {
               dynamic_cast<SnakeBody*>(m_snake[i + 1])->setUseVelocityVector(true);
               m_snake[i + 1]->setVel(m_snake[i]->getXvel(), m_snake[i]->getYvel());
            }
         }

         if(m_snake[i]->getYpos() < -25.0f)
         {
            m_snake[i]->setYpos(WINDOW_HEIGHT + 25.0f);

            dynamic_cast<SnakeBody*>(m_snake[i])->setUseVelocityVector(false);
            if(i < (m_snakeLenght - 1))
            {
               dynamic_cast<SnakeBody*>(m_snake[i + 1])->setUseVelocityVector(true);
               m_snake[i + 1]->setVel(m_snake[i]->getXvel(), m_snake[i]->getYvel());
            }
         }
         else if(m_snake[i]->getYpos() > WINDOW_HEIGHT + 25.0f)
         {
            m_snake[i]->setYpos(-25.0f);

            dynamic_cast<SnakeBody*>(m_snake[i])->setUseVelocityVector(false);
            if(i < (m_snakeLenght - 1))
            {
               dynamic_cast<SnakeBody*>(m_snake[i + 1])->setUseVelocityVector(true);
               m_snake[i + 1]->setVel(m_snake[i]->getXvel(), m_snake[i]->getYvel());
            }
         }
      }
   }
}

void
SnakeHandler::Draw(RenderWindow& window)
{
   for(int i = 1; i < m_snakeLenght; i++)
   {
      if(m_snake[i] != NULL)
      {
         m_snake[i]->Draw(window);
      }
   }

   m_snake[(int)INDEX::INDEX_HEAD]->Draw(window);
}

void
SnakeHandler::addSpeed(float speed)
{
   m_currSpeed += speed;
}

void
SnakeHandler::addBody()
{
   float x = m_snake[m_snakeLenght - 1]->getXpos();
   float y = m_snake[m_snakeLenght - 1]->getYpos();

   if(m_snakeLenght < m_snakeMaxLength)
   {
      m_snake[m_snakeLenght] = new SnakeBody(x, y, 0.0f, 0.0f, m_texture);
      m_snakeLenght++;
   }
   else
   {
      expandBody();
      m_snake[m_snakeLenght] = new SnakeBody(x, y, 0.0f, 0.0f, m_texture);
      m_snakeLenght++;
   }
}

void
SnakeHandler::die()
{
   resetSnake();

   m_angle = 0.0f;
   m_currSpeed = START_SPEED;
}

Snake
SnakeHandler::getSnakeHead() const
{
   return *m_snake[(int)INDEX::INDEX_HEAD];
}

Snake
SnakeHandler::getSnakeBody(int index) const
{
   return *m_snake[index];
}

float
SnakeHandler::getAngle() const
{
   return m_angle;
}

int
SnakeHandler::getLength() const
{
   return m_snakeLenght;
}

void
SnakeHandler::expandBody()
{
   // copy to a temporary array.
   Snake** temp;
   temp = new Snake * [m_snakeLenght];
   
   temp[(int)INDEX::INDEX_HEAD] = new SnakeHead(dynamic_cast<SnakeHead*>(m_snake[(int)INDEX::INDEX_HEAD]));
   for(int i = 1; i < m_snakeLenght; i++)
   {
      temp[i] = new SnakeBody(dynamic_cast<SnakeBody*>(m_snake[i]));
   }

   // Delete old array to make a new one.
   for(int i = 0; i < m_snakeLenght; i++)
   {
      if(m_snake[i] != NULL)
      {
         delete m_snake[i];
      }
   }
   delete[] m_snake;

   // Expand old array.
   m_snakeMaxLength += 10;
   m_snake = new Snake * [m_snakeMaxLength];

   // Copy from temporary array to the new 'old' one.
   m_snake[(int)INDEX::INDEX_HEAD] = new SnakeHead(dynamic_cast<SnakeHead*>(temp[(int)INDEX::INDEX_HEAD]));
   for(int i = 1; i < m_snakeLenght; i++)
   {
      m_snake[i] = new SnakeBody(dynamic_cast<SnakeBody*>(temp[i]));
   }
   for(int i = m_snakeLenght; i < m_snakeMaxLength; i++)
   {
      m_snake[i] = NULL;
   }

   // delete the temporary array.
   for(int i = 0; i < m_snakeLenght; i++)
   {
      if(temp[i] != NULL)
      {
         delete temp[i];
      }
   }
   delete[] temp;

   // Possible to expand ontil RAM is used up.
}

float
SnakeHandler::normalize(float angle)
{
   // Normalize angle between 0 and 2PI
   angle = fmodf(angle, PI2);
   if(angle < 0.0f)
   {
      angle += PI2;
   }

   return angle;
}

void
SnakeHandler::resetSnake()
{
   for(int i = 0; i < m_snakeMaxLength; i++)
   {
      if(m_snake[i] != NULL)
      {
         delete m_snake[i];
         m_snake[i] = NULL;
      }
   }

   m_snakeLenght = 0;

   m_snake[(int)INDEX::INDEX_HEAD] = new SnakeHead(DEFAULT_X_POS, DEFAULT_Y_POS, 0.0f, m_currSpeed);
   m_snakeLenght++;

   for(int i = 1; i < DEFAULT_BODY; i++)
   {
      m_snake[i] = new SnakeBody(DEFAULT_X_POS, DEFAULT_Y_POS, 0.0f, 0.0f, m_texture);
      m_snakeLenght++;
   }

   for(int i = DEFAULT_BODY; i < m_snakeMaxLength; i++)
   {
      m_snake[i] = NULL;
   }
}
