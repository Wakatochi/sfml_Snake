#pragma once
#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "snakehandler.h"
#include "pellets.h"
#include "scorehandler.h"

using namespace sf;

class GameHandler
{
   public:
      GameHandler();
      explicit GameHandler(RenderWindow* window);
      ~GameHandler();

      void Update();
      void Draw();

   private:
      enum class GAMESTATE
      {
         GAME_INIT  = 0,
         GAME_MENU  = 1,
         GAME_RUN   = 2,
         GAME_PAUS  = 3,
         GAME_DYING = 4,
         GAME_QUIT  = 5
      };

      int m_nrOfPellets;

      RenderWindow* m_gameWindow;
      Font m_font;
      Texture m_bgTexture;
      Sprite m_bgSprite;
      SoundBuffer m_pelletsBuffer;
      SoundBuffer m_gameOverBuffer;
      Sound m_sound;
      Music m_music;
      Clock m_currentClock;
      GAMESTATE m_gameState;
      SnakeHandler m_snakeHand;
      ScoreHandler m_scoreHandler;
      Pellets* m_pellets[10];
      SnakeHandler::INPUT m_input;

      void loadResource();

      void HandleEvent();
      void HandleKeyboardEvent(const Event& event);

      bool CheckCollition();
      bool CircleCollition(Snake head, float xPos, float yPos, float radius);
};

#endif
