#include "mainMenu.h"

int main()
{   

    //Window initialization
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Booleo");
    ToggleFullscreen();

    //Set icon for window
    Image icon = LoadImage("./res/icon.png");
    SetWindowIcon(icon);

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