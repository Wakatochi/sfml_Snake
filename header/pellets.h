#pragma once
#ifndef PELLETS_H
#define PELLETS_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Pellets
{
   public:
      Pellets();
      Pellets(Texture& texture);
      ~Pellets();

      virtual void Update();
      virtual void Draw(RenderWindow& window);

      int getValue();
      float getRadius();
      float getXpos();
      float getYpos();

      void setPos(float x, float y);

   protected:
      Sprite m_sprite;
      Texture m_texture;
      float m_size;

   private:
      CircleShape m_shape;
      int m_value;

      float m_xPos;
      float m_yPos;
};

#endif
