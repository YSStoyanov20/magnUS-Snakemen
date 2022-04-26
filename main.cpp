#include "raylib.h"

int main()
{   
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "Booleo");

    SetTargetFPS(60);

    // Texture2D AndZeroCard = LoadTexture("./Sprites/AndZeroCard.png");
    Texture2D MenuButtonUnpressed = LoadTexture("./Sprites/Begin-Button-Unpressed.png");
    Texture2D MenuButtonPressed = LoadTexture("./Sprites/Begin-Button-Pressed.png");
    Texture2D RuleButtonUnpressed = LoadTexture("./Sprites/Rules-Button-Unpressed.png");
    Texture2D RuleButtonPressed = LoadTexture("./Sprites/Rules-Button-Pressed.png");
    float width = MenuButtonPressed.width;
    float height = MenuButtonPressed.height;
    float ruleWidth = RuleButtonPressed.width;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 MousePosition = GetMousePosition();
        Vector2 mousePoint = {MousePosition.x, MousePosition.y};
        
        //Display the values of the mouse position
        DrawText(TextFormat("Mouse X: %f", mousePoint.x), 10, 10, 20, BLACK);
        DrawText(TextFormat("Mouse Y: %f", mousePoint.y), 10, 30, 20, BLACK);

        
        DrawTexture(MenuButtonUnpressed, 1600/2 - width/2, 900/2 - height/2, WHITE);
        //detect if the mouse is over the menu button
        if(CheckCollisionPointRec(mousePoint, {1600/2 - width/2, 900/2 - height/2 + 4, width, height}))
        {
            DrawRectangle(1600/2 - width/2, 900/2 - height/2, width, height, RAYWHITE);
            DrawTexture(MenuButtonPressed, 1600/2 - width/2, 900/2 - height/2 + 4, WHITE);
            // if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            // {
            //     UnloadTexture(MenuButtonUnpressed);
            //     UnloadTexture(MenuButtonPressed);
            // }     
        }

        DrawTexture(RuleButtonUnpressed, 1600/2 - ruleWidth/2, 900/2 - height/2 + 100, WHITE);
        //detect if the mouse is over the rule button
        if(CheckCollisionPointRec(mousePoint, {1600/2 - ruleWidth/2, 900/2 - height/2 + 104, ruleWidth, height}))
        {
            DrawRectangle(1600/2 - ruleWidth/2, 900/2 - height/2 + 100, ruleWidth, height, RAYWHITE);
            DrawTexture(RuleButtonPressed, 1600/2 - ruleWidth/2, 900/2 - height/2 + 104, WHITE);
            // if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            // {
            //     UnloadTexture(RulesButtonUnpressed);
            //     UnloadTexture(RulesButtonPressed);
            // }     
        }

        
        EndDrawing();
    }
    CloseWindow();
}