#include "include/raylib.h"

int main()
{   
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1600, 900, "Booleo");
    
    // Texture2D AndZeroCard = LoadTexture("./Sprites/AndZeroCard.png");
    Texture2D MenuButtonUnpressed = LoadTexture("./Sprites/Begin-Button-Unpressed.png");
    Texture2D MenuButtonPressed = LoadTexture("./Sprites/Begin-Button-Pressed.png");
    Texture2D RuleButtonUnpressed = LoadTexture("./Sprites/Rules-Button-Unpressed.png");
    Texture2D RuleButtonPressed = LoadTexture("./Sprites/Rules-Button-Pressed.png");
    Texture2D QuitButtonUnpressed = LoadTexture("./Sprites/Quit-Button-Unpressed.png");
    Texture2D QuitButtonPressed = LoadTexture("./Sprites/Quit-Button-Pressed.png");

    float width = MenuButtonPressed.width;
    float height = MenuButtonPressed.height;
    float ruleWidth = RuleButtonPressed.width;
    float quitWidth = QuitButtonPressed.width;

    bool isInMainMenu = true;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 MousePosition = GetMousePosition();
        Vector2 mousePoint = {MousePosition.x, MousePosition.y};
        
        //Display the values of the mouse position
        DrawText(TextFormat("%0.f, %0.f", mousePoint.x,mousePoint.y), 10, 10, 20, BLACK);

        if(isInMainMenu)
        {
        DrawTexture(MenuButtonUnpressed, 1600/2 - width/2, 900/2 - height/2, WHITE);
        //detect if the mouse is over the menu button
        if(CheckCollisionPointRec(mousePoint, {1600/2 - width/2, 900/2 - height/2 + 4, width, height}))
        {
            DrawRectangle(1600/2 - width/2, 900/2 - height/2, width, height, RAYWHITE);
            DrawTexture(MenuButtonPressed, 1600/2 - width/2, 900/2 - height/2 + 4, WHITE);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                isInMainMenu = false;
            }     
        }}

        if(isInMainMenu)
        {
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
        }}

        if(isInMainMenu)
        {
        DrawTexture(QuitButtonUnpressed, 1600/2 - quitWidth/2, 900/2 - height/2 + 200, WHITE);
        if(CheckCollisionPointRec(mousePoint, {1600/2 - quitWidth/2, 900/2 - height/2 + 204, quitWidth, height}))
        {
            DrawRectangle(1600/2 - quitWidth/2, 900/2 - height/2 + 200, quitWidth, height, RAYWHITE);
            DrawTexture(QuitButtonPressed, 1600/2 - quitWidth/2, 900/2 - height/2 + 204, WHITE);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                //Close application
                CloseWindow();
            }    
        }
        }

        
        EndDrawing();
    }
    CloseWindow();
}