#pragma once
#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include "snake.h"

class SnakeHead : public Snake
{
   public:
      SnakeHead();
      SnakeHead(float xPos, float yPos, float xVel, float yVel);
      SnakeHead(SnakeHead* head);

      ~SnakeHead();

      void Update();
      void Draw(RenderWindow& window);

   private:
};

#endif
