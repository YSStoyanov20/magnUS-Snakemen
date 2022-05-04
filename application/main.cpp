#include "raylib.h"
#include "mainMenu.h"

int main()
{   
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1600, 900, "Booleo");

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