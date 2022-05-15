#include "mainMenu.h"
namespace mainMenu{
    bool isInMainMenu = true;
    bool texturesLoaded = false;

    Texture2D RuleButtonUnpressed;
    Texture2D RuleButtonPressed;
    Texture2D QuitButtonUnpressed;
    Texture2D QuitButtonPressed;
    Texture2D PVPButtonUnpressed;
    Texture2D PVPButtonPressed;
    Texture2D PVCButtonUnpressed;
    Texture2D PVCButtonPressed;
    Texture2D Background;

    float buttonWidth;
    float buttonHeight;
    
    void loadTextures()
    {
        Background = LoadTexture("./res/Title-screen.png");
        RuleButtonUnpressed = LoadTexture("./res/Rules-Button-Unpressed.png");
        RuleButtonPressed = LoadTexture("./res/Rules-Button-Pressed.png");
        QuitButtonUnpressed = LoadTexture("./res/Quit-Button-Unpressed.png");
        QuitButtonPressed = LoadTexture("./res/Quit-Button-Pressed.png");
        PVPButtonUnpressed = LoadTexture("./res/PVP-button-Unpressed.png");
        PVPButtonPressed = LoadTexture("./res/PVP-button-Pressed.png");
        PVCButtonPressed = LoadTexture("./res/PVC-button-Pressed.png");
        PVCButtonUnpressed = LoadTexture("./res/PVC-button-Unpressed.png");
        buttonWidth = PVPButtonPressed.width;
        buttonHeight = PVPButtonPressed.height;
        texturesLoaded = true;
    }
    void unloadTextures()
    {
        UnloadTexture(Background);
        UnloadTexture(PVCButtonPressed);
        UnloadTexture(PVCButtonUnpressed);
        UnloadTexture(PVPButtonPressed);
        UnloadTexture(PVPButtonUnpressed);
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
                global::unloadTextures();
                loadTextures();
            }
            //Sets button position
            Vector2 buttonPos = {GetScreenWidth()/2 - buttonWidth/2, float(GetScreenHeight()/2)};

            //Gets the mouse position            
            Vector2 MousePos = {GetMousePosition().x, GetMousePosition().y};
            DrawTexture(Background, 0, 0, WHITE);
            //Detects if the mouse is over the menu button
            if(CheckCollisionPointRec(MousePos, {buttonPos.x, buttonPos.y + 4, buttonWidth, buttonHeight}))
            {
                SetMouseCursor(4);
                DrawTexture(PVPButtonPressed, buttonPos.x, buttonPos.y + 4, WHITE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    unloadTextures();
                    isInMainMenu = false;
                    PvP::isInPvP = true;
                }     
            }
            else
            {
                //Draws the menu button
                DrawTexture(PVPButtonUnpressed, buttonPos.x, buttonPos.y, WHITE);
            }

            
            //Detects if the mouse is over the rules button
            if(CheckCollisionPointRec(MousePos, {buttonPos.x, buttonPos.y + 104, buttonWidth, buttonHeight}))
            {
                SetMouseCursor(4);
                DrawTexture(PVCButtonPressed, buttonPos.x, buttonPos.y + 104, WHITE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    unloadTextures();
                    isInMainMenu = false;
                    PvC::isInPvC = true;
                }     
            }
            else
            {
                //Draws the rules button
                DrawTexture(PVCButtonUnpressed, buttonPos.x, buttonPos.y + 100, WHITE);
            }


            
            //Detects if the mouse is over the quit button
            if(CheckCollisionPointRec(MousePos, {buttonPos.x, buttonPos.y + 204, buttonWidth, buttonHeight}))
            {
                SetMouseCursor(4);
                DrawTexture(QuitButtonPressed, buttonPos.x, buttonPos.y + 204, WHITE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    //Closes the application
                    CloseWindow();
                }    
            }
            else
            {
                //Draws the quit button
                DrawTexture(QuitButtonUnpressed, buttonPos.x, buttonPos.y + 200, WHITE);
            }
            
        }
        if(PvP::isInPvP)
        {
            PvP::startGame();
        }
        if(PvC::isInPvC)
        {
            PvC::startGame();
        }
    }
};