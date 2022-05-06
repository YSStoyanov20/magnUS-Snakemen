#include "PvP.h"
#include <time.h>

namespace PvP{
    bool texturesLoaded = false;
    bool isInPvP = false;

    Texture2D initialBinary;
    Texture2D initialBinaryFlipped;
    Texture2D andCard_0;
    Texture2D andCard_1;
    Texture2D orCard_0;
    Texture2D orCard_1;
    Texture2D xorCard_0;
    Texture2D xorCard_1;

    float cardWidth;
    float cardHeight;

    int initialBinaries[6];

    void loadTextures()
    {
        initialBinary = LoadTexture("./Sprites/Initial-Binaries-Reverse.png");
        initialBinaryFlipped = LoadTexture("./Sprites/Initial-Binaries.png");
        andCard_0 = LoadTexture("./Sprites/And-Zero-Card.png");
        andCard_1 = LoadTexture("./Sprites/And-One-Card.png");
        orCard_0 = LoadTexture("./Sprites/Or-Zero-Card.png");
        orCard_1 = LoadTexture("./Sprites/Or-One-Card.png");
        xorCard_0 = LoadTexture("./Sprites/XOR-Zero-Card.png");
        xorCard_1 = LoadTexture("./Sprites/XOR-One-Card.png");
        cardWidth = initialBinary.width;
        cardHeight = initialBinary.height;
        texturesLoaded = true;
    }
    void unloadTextures()
    {
        UnloadTexture(initialBinary);
        UnloadTexture(initialBinaryFlipped);
        UnloadTexture(andCard_0);
        UnloadTexture(andCard_1);
        UnloadTexture(orCard_0);
        UnloadTexture(orCard_1);
        UnloadTexture(xorCard_0);
        UnloadTexture(xorCard_1);
        texturesLoaded = false;
    }
    void randomizeInitialBinary()
    {
        SetRandomSeed(time(NULL));
        for(int i = 0;i<6;i++)
        {
            if(GetRandomValue(0,1) == 0)
            {
                initialBinaries[i] = 0;
            }
            else
            {
                initialBinaries[i] = 1;
            }
        }
    }
    void drawInitialBinary()
    {
        //Set initial binary position
        Vector2 initialBinaryPos = {GetScreenWidth()/2 - cardWidth*3, GetScreenHeight()/2 - cardHeight/2};
        for(int i = 0, spaceBetween = 0; i<6;i++)
        {
            if(initialBinaries[i]==0)
            {
                DrawTexture(initialBinary, initialBinaryPos.x  + spaceBetween, initialBinaryPos.y, WHITE);
            }
            else
            {
                DrawTexture(initialBinaryFlipped, initialBinaryPos.x  + spaceBetween, initialBinaryPos.y, WHITE);
            }
            spaceBetween+=cardWidth+10;
        }
    }
    void setCards()
    {
        if(isInPvP)
        {
            //Get mouse position            
            Vector2 MousePos = {GetMousePosition().x, GetMousePosition().y};

            //Display mouse position
            DrawText(TextFormat("%0.f, %0.f", MousePos.x, MousePos.y), 10, 10, 20, BLACK);

            //Load the textures if not loaded
            if(!texturesLoaded)
            {
                loadTextures();
                randomizeInitialBinary();
            }
            
            drawInitialBinary();

            //If escape key pressed return back to Main Menu
            if(IsKeyPressed(KEY_ESCAPE))
            {
                isInPvP = false;
                mainMenu::isInMainMenu = true;
            }
        }
    }
};
