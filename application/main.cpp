#include "mainMenu.h"

int main()
{   

    //Window initialization
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "Booleo");

    //Remove exit key
    SetExitKey(KEY_NULL);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //Load the main menu
        mainMenu::loadMainMenu();
        EndDrawing();
    }
    CloseWindow();
}