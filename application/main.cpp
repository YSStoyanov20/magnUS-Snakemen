#include "mainMenu.h"
int main()
{   

    //Window initialization
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Booleo");
    ToggleFullscreen();
    //Sets icon for window
    Image icon = LoadImage("./res/icon.png");
    SetWindowIcon(icon);

    //Removes exit key
    SetExitKey(KEY_NULL);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Loads the main menu
        mainMenu::loadMainMenu();
        EndDrawing();
    }
    CloseWindow();
}