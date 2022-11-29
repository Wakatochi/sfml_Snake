#pragma once
#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include "snake.h"

class SnakeBody : public Snake
{
public:
   SnakeBody();
   SnakeBody(float xPos, float yPos, float xVel, float yVel, Texture& texture);
   SnakeBody(SnakeBody* body);
   ~SnakeBody();

   void Update();
   void Draw(RenderWindow& window);

   void setUseVelocityVector(bool speedVector);
   bool getUseVelocityVector();

private:
   bool m_useVelocity;

};

#endif
