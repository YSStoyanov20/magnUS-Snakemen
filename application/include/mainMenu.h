#pragma once
#include "raylib.h"
#include "PvP.h"
#include "PvC.h"
namespace mainMenu{
    void loadTextures();
    void unloadTextures();
    void loadMainMenu();
    extern bool isInMainMenu;
};