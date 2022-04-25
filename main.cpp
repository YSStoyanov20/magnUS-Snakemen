#include "raylib.h"

int main(void)
{   
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "Booleo");

    SetTargetFPS(60);

    // Texture2D AndZeroCard = LoadTexture("./Sprites/AndZeroCard.png");
    Texture2D MenuButtonUnpressed = LoadTexture("./Sprites/Begin-Button-Unpressed.png");
    Texture2D MenuButtonPressed = LoadTexture("./Sprites/Begin-Button-Pressed.png");
    float width = MenuButtonPressed.width;
    float height = MenuButtonPressed.height;
    // float Mwidth = MenuButtonUnpressed.width;
    // float Mheight = MenuButtonUnpressed.height;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 MousePosition = GetMousePosition();
        Vector2 mousePoint = {MousePosition.x, MousePosition.y};
        
        //Display the values of the mouse position
        DrawText(TextFormat("Mouse X: %f", mousePoint.x), 10, 10, 20, BLACK);
        DrawText(TextFormat("Mouse Y: %f", mousePoint.y), 10, 30, 20, BLACK);

        //Draw the menu button
        DrawTexture(MenuButtonUnpressed, 1600/2 - width/2, 900/2 - height/2, WHITE);

        //detect if the mouse is over the menu button
        if(CheckCollisionPointRec(mousePoint, {1600/2 - width/2, 900/2 - height/2, width, height}))
        {
            DrawTexture(MenuButtonPressed, 1600/2 - width/2, 900/2 - height/2, WHITE);
            //remove the menu button
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                //remove the menu button
                UnloadTexture(MenuButtonUnpressed);
                UnloadTexture(MenuButtonPressed);
            }
            
        }


        
            

        EndDrawing();
    }
    CloseWindow();
}