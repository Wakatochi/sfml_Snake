#pragma once
#ifndef PANEL_H
#define PANEL_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Panel
{
   public:
      Panel();
      Panel(Texture& texture);
      ~Panel();

      void Update();
      void Draw(RenderWindow& window);

   private:
      Sprite m_sprite;
      Texture* m_texture;

      RectangleShape m_shape;

      float m_xPos;
      float m_yPos;
};

#endif PANEL_H
