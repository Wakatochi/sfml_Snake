#pragma once
#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "snakehandler.h"
#include "panel.h"
#include "pellets.h"


using namespace sf;

/// <summary>
/// GameHandler class is responsible for managing the game state,
/// handling events, updating the game logic, and rendering the game objects.
/// </summary>
class GameHandler
{
   public:
      /// <summary>
      /// Constructor for the GameHandler class.
      /// Initializes the game state and input to default values, and sets the number of pellets to zero.
      /// Also initializes the game window pointer to NULL.
      /// </summary>
      GameHandler();

      /// <summary>
      /// Constructor for the GameHandler class that takes a pointer to a RenderWindow as an argument.
      /// </summary>
      /// <param name="window"></param>
      explicit GameHandler(RenderWindow* window);

      /// <summary>
      /// Destructor for the GameHandler class.
      /// </summary>
      ~GameHandler();

      /// <summary>
      /// Update method for the GameHandler class.
      /// </summary>
      void Update();

      /// <summary>
      /// Draw method for the GameHandler class.
      /// </summary>
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
//      Font m_font;
      Texture m_bgTexture;
      Sprite m_bgSprite;
      SoundBuffer m_pelletsBuffer;
      SoundBuffer m_gameOverBuffer;
      Sound m_sound;
      Music m_music;
      Clock m_currentClock;
      GAMESTATE m_gameState;
      SnakeHandler m_snakeHand;
//      ScoreHandler m_scoreHandler;
      Pellets* m_pellets[10];
      SnakeHandler::INPUT m_input;
      Panel m_scorePanel;

      void loadResource();

      void HandleEvent();
      void HandleKeyboardEvent(const Event& event);

      bool CheckCollition();
      bool CircleCollition(Snake head, float xPos, float yPos, float radius);
};

#endif
