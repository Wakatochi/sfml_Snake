#pragma once
#ifndef MAINHANDLER_H
#define MAINHANDLER_H

#include <SFML/Graphics.hpp>
#include "gamehandler.h"

using namespace sf;

class MainHandler
{
   public:
      MainHandler();
      ~MainHandler();

      int Run();

   private:
      enum class MAINSTATE
      {
         MAIN_INIT = 0,
         MAIN_MENU = 1,
         MAIN_GAME = 2,
      };

      MAINSTATE m_state;
      RenderWindow* m_MainWindow;

      GameHandler* m_game;

      void initWindow();
      void updateMenu();
      void updateGame();
};

#endif
