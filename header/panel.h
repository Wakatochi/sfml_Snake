#pragma once
#ifndef PANEL_H
#define PANEL_H

#include <SFML/Graphics.hpp>
#include "scorehandler.h"

using namespace sf;

class Panel
{
   public:
      Panel();
      ~Panel();

      void Draw(RenderWindow& window);

      void addPoints(int points);
      void setAngle(float angle);
      void resetScore();

   private:
      Sprite m_sprite;
      Texture m_texture;

      RectangleShape m_shape;

      Font m_font;
      ScoreHandler m_scoreHandler;

      float m_xPos;
      float m_yPos;

      void loadResource();
};

#endif PANEL_H
