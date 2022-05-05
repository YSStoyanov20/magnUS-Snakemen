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

    float buttonWidth;
    float buttonHeight;
    
    void loadTextures()
    {
        MenuButtonUnpressed = LoadTexture("./Sprites/Begin-Button-Unpressed.png");
        MenuButtonPressed = LoadTexture("./Sprites/Begin-Button-Pressed.png");
        RuleButtonUnpressed = LoadTexture("./Sprites/Rules-Button-Unpressed.png");
        RuleButtonPressed = LoadTexture("./Sprites/Rules-Button-Pressed.png");
        QuitButtonUnpressed = LoadTexture("./Sprites/Quit-Button-Unpressed.png");
        QuitButtonPressed = LoadTexture("./Sprites/Quit-Button-Pressed.png");
        buttonWidth = MenuButtonPressed.width;
        buttonHeight = MenuButtonPressed.height;
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
        texturesLoaded = false;
    }

    void loadMainMenu()
    {
        if(isInMainMenu)
        {
            if(!texturesLoaded)
            {
                PvP::unloadTextures();
                loadTextures();
            }

            //Set button position
            Vector2 buttonPos = {GetScreenWidth()/2 - buttonWidth/2, GetScreenHeight()/2 - buttonHeight};

            //Get mouse position            
            Vector2 MousePos = {GetMousePosition().x, GetMousePosition().y};

            //Display mouse position
            DrawText(TextFormat("%0.f, %0.f", MousePos.x, MousePos.y), 10, 10, 20, BLACK);

            //Draw the menu button
            DrawTexture(MenuButtonUnpressed, buttonPos.x, buttonPos.y, WHITE);
            //Detect if the mouse is over the menu button
            if(CheckCollisionPointRec(MousePos, {buttonPos.x, buttonPos.y + 4, buttonWidth, buttonHeight}))
            {
                DrawRectangle(buttonPos.x, buttonPos.y, buttonWidth, buttonHeight, RAYWHITE);
                DrawTexture(MenuButtonPressed, buttonPos.x, buttonPos.y + 4, WHITE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    unloadTextures();
                    isInMainMenu = false;
                    PvP::isInPvP = true;
                }     
            }

            //Draw the rules button
            DrawTexture(RuleButtonUnpressed, buttonPos.x, buttonPos.y + 100, WHITE);
            //Detect if the mouse is over the rules button
            if(CheckCollisionPointRec(MousePos, {buttonPos.x, buttonPos.y + 104, buttonWidth, buttonHeight}))
            {
                DrawRectangle(buttonPos.x, buttonPos.y + 100, buttonWidth, buttonHeight, RAYWHITE);
                DrawTexture(RuleButtonPressed, buttonPos.x, buttonPos.y + 104, WHITE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    unloadTextures();
                    isInMainMenu = false;
                }     
            }

            //Draw the quit button
            DrawTexture(QuitButtonUnpressed, buttonPos.x, buttonPos.y + 200, WHITE);
            //Detect if the mouse is over the quit button
            if(CheckCollisionPointRec(MousePos, {buttonPos.x, buttonPos.y + 204, buttonWidth, buttonHeight}))
            {
                DrawRectangle(buttonPos.x, buttonPos.y + 200, buttonWidth, buttonHeight, RAYWHITE);
                DrawTexture(QuitButtonPressed, buttonPos.x, buttonPos.y + 204, WHITE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    //Close the application
                    CloseWindow();
                }    
            }
        }
        if(PvP::isInPvP)
        {
            PvP::setCards();
        }
    }
};