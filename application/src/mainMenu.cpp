#include "raylib.h"
#include "mainMenu.h"
namespace mainMenu{
    bool isInMainMenu = true;
    bool texturesLoaded = false;

    Texture2D MenuButtonUnpressed;
    Texture2D MenuButtonPressed;
    Texture2D RuleButtonUnpressed;
    Texture2D RuleButtonPressed;
    Texture2D QuitButtonUnpressed;
    Texture2D QuitButtonPressed;

    float width;
    float height;
    float ruleWidth;
    float quitWidth;
    
    void loadTextures()
    {
        MenuButtonUnpressed = LoadTexture("./Sprites/Begin-Button-Unpressed.png");
        MenuButtonPressed = LoadTexture("./Sprites/Begin-Button-Pressed.png");
        RuleButtonUnpressed = LoadTexture("./Sprites/Rules-Button-Unpressed.png");
        RuleButtonPressed = LoadTexture("./Sprites/Rules-Button-Pressed.png");
        QuitButtonUnpressed = LoadTexture("./Sprites/Quit-Button-Unpressed.png");
        QuitButtonPressed = LoadTexture("./Sprites/Quit-Button-Pressed.png");
        width = MenuButtonPressed.width;
        height = MenuButtonPressed.height;
        ruleWidth = RuleButtonPressed.width;
        quitWidth = QuitButtonPressed.width;
        texturesLoaded = true;
    }
    void unloadTextures()
    {
        UnloadTexture(MenuButtonUnpressed);
        UnloadTexture(MenuButtonPressed);
        UnloadTexture(RuleButtonUnpressed);
        UnloadTexture(RuleButtonPressed);
        UnloadTexture(QuitButtonUnpressed);
        UnloadTexture(QuitButtonPressed);
    }
    void loadMainMenu()
    {
        if(isInMainMenu)
        {
            if(!texturesLoaded)
            {
                loadTextures();
            }

            //Get mouse position
            Vector2 MousePosition = GetMousePosition();
            Vector2 mousePoint = {MousePosition.x, MousePosition.y};
            
            //Display the values of the mouse position
            DrawText(TextFormat("%0.f, %0.f", mousePoint.x,mousePoint.y), 10, 10, 20, BLACK);

            //Draw the menu button
            DrawTexture(MenuButtonUnpressed, 1600/2 - width/2, 900/2 - height/2, WHITE);
            //Detect if the mouse is over the menu button
            if(CheckCollisionPointRec(mousePoint, {1600/2 - width/2, 900/2 - height/2 + 4, width, height}))
            {
                DrawRectangle(1600/2 - width/2, 900/2 - height/2, width, height, RAYWHITE);
                DrawTexture(MenuButtonPressed, 1600/2 - width/2, 900/2 - height/2 + 4, WHITE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    unloadTextures();
                    isInMainMenu = false;
                }     
            }

            //Draw the rules button
            DrawTexture(RuleButtonUnpressed, 1600/2 - ruleWidth/2, 900/2 - height/2 + 100, WHITE);
            //Detect if the mouse is over the rules button
            if(CheckCollisionPointRec(mousePoint, {1600/2 - ruleWidth/2, 900/2 - height/2 + 104, ruleWidth, height}))
            {
                DrawRectangle(1600/2 - ruleWidth/2, 900/2 - height/2 + 100, ruleWidth, height, RAYWHITE);
                DrawTexture(RuleButtonPressed, 1600/2 - ruleWidth/2, 900/2 - height/2 + 104, WHITE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    unloadTextures();
                    isInMainMenu = false;
                }     
            }

            //Draw the quit button
            DrawTexture(QuitButtonUnpressed, 1600/2 - quitWidth/2, 900/2 - height/2 + 200, WHITE);
            //Detect if the mouse is over the quit button
            if(CheckCollisionPointRec(mousePoint, {1600/2 - quitWidth/2, 900/2 - height/2 + 204, quitWidth, height}))
            {
                DrawRectangle(1600/2 - quitWidth/2, 900/2 - height/2 + 200, quitWidth, height, RAYWHITE);
                DrawTexture(QuitButtonPressed, 1600/2 - quitWidth/2, 900/2 - height/2 + 204, WHITE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    //Close the application
                    CloseWindow();
                }    
            }
        }

    }
};