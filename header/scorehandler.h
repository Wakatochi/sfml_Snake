#pragma once
#ifndef FONTHANDLER_H
#define FONTHANDLER_H

#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;
using namespace std;

class ScoreHandler
{
   public:
      ScoreHandler();
      ScoreHandler(Font& font);
      ~ScoreHandler();

      void initText(Font& fotn);
      void addScore(int points);
      void resetScore();
      int totalScore();

      void Draw(RenderWindow& window);

      void setAngle(float angle);

   private:
      Text m_scoreText;
      int m_score;
      int m_multiplier;

      float m_xPos;
      float m_yPos;

      Text m_angle;

      String toString(int val);
      String toStringf(float val);
};

#endif