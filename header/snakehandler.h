#pragma once
#ifndef SNAKEHANDLER_H
#define SNAKEHANDLER_H

#include <SFML/Graphics.hpp>
#include "snake.h"

using namespace sf;

class SnakeHandler
{
   public:
      SnakeHandler();
      ~SnakeHandler();

      void Update(float dt, int input);
      void Draw(RenderWindow& window);

      void addSpeed(float speed);
      void addBody();
      void die();

      Snake getSnakeHead() const;
      Snake getSnakeBody(int index) const;
      
      float getAngle() const;

      int getLength() const;

      enum class INPUT
      {
         NONE = 0,
         LEFT = 1,
         RIGHT = 2,
         UP = 3,
         DOWN = 4
      };

      enum class INDEX
      {
         INDEX_HEAD = 0,
         INDEX_COLISION = 4
      };

   private:
      void expandBody();

      const int DEFAULT_BODY = 3;
      const float DEFAULT_X_POS = 400.0f;
      const float DEFAULT_Y_POS = 300.0f;

      float m_angle;
      float m_currSpeed;

      int m_snakeLenght;
      int m_snakeMaxLength;
      Snake** m_snake;

      Texture m_texture;

      float normalize(float angle);

      void resetSnake();
};

#endif
