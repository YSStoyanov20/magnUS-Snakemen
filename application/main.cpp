#include "raylib.h"
#include "mainMenu.h"

int main()
{   
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1600, 900, "Booleo");

    //Load the main menu
    loadMainMenu(true);
}