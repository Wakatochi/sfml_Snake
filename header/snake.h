#pragma once
#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include "globals.h"
using namespace sf;

class Snake
{
   public:
      Snake();
      Snake(float xPos, float yPos, float xVel, float yVel);
      virtual ~Snake();

      virtual void Update();
      virtual void Draw(RenderWindow& window);

      void setXpos(float x);
      void setYpos(float y);
      void setXvel(float xVel);
      void setYvel(float yVel);

      void setPos(float x, float y);
      void setVel(float x, float y);

      float getXpos();
      float getYpos();
      float getXvel();
      float getYvel();

      float getRadius();
      Texture* getTexture();

      float getLengthFromPrev(Snake body);
      float getTotalRadiusFromPrev(Snake body);

   protected:
      Sprite m_sprite;
      Texture m_texture;
      float m_size;

   private:
      float m_xVel;
      float m_yVel;
      float m_xPos;
      float m_yPos;

      bool checkWallCollition();
      bool checkBodyCollition(Snake body);
};

#endif
