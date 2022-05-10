#include "PvP.h"
namespace PvP{
    bool texturesLoaded = false;
    bool isInPvP = false;

    Texture2D initialBinary;
    Texture2D initialBinaryFlipped;
    Texture2D andCard0;
    Texture2D andCard1;
    Texture2D orCard0;
    Texture2D orCard1;
    Texture2D xorCard0;
    Texture2D xorCard1;


    float cardWidth;
    float cardHeight;

    int initialBinaries[6];

    std::vector<Texture2D> andCards0;
    std::vector<Texture2D> andCards1;
    std::vector<Texture2D> orCards0;
    std::vector<Texture2D> orCards1;
    std::vector<Texture2D> xorCards0;
    std::vector<Texture2D> xorCards1;
    
    std::vector<Texture2D> player1Cards;
    std::vector<Texture2D> player2Cards;

    void loadTextures()
    {
        initialBinary = LoadTexture("./Sprites/Initial-Binaries-Reverse.png");
        initialBinaryFlipped = LoadTexture("./Sprites/Initial-Binaries.png");
        andCard0 = LoadTexture("./Sprites/And-Zero-Card.png");
        andCard1 = LoadTexture("./Sprites/And-One-Card.png");
        orCard0 = LoadTexture("./Sprites/Or-Zero-Card.png");
        orCard1 = LoadTexture("./Sprites/Or-One-Card.png");
        xorCard0 = LoadTexture("./Sprites/XOR-Zero-Card.png");
        xorCard1 = LoadTexture("./Sprites/XOR-One-Card.png");
        cardWidth = initialBinary.width;
        cardHeight = initialBinary.height;

        andCards0 = {andCard0, andCard0, andCard0, andCard0, andCard0, andCard0, andCard0, andCard0};
        andCards1 = {andCard1, andCard1, andCard1, andCard1, andCard1, andCard1, andCard1, andCard1};
        orCards0 = {orCard0, orCard0, orCard0, orCard0, orCard0, orCard0, orCard0, orCard0};
        orCards1 = {orCard1, orCard1, orCard1, orCard1, orCard1, orCard1, orCard1, orCard1};
        xorCards0 = {xorCard0, xorCard0, xorCard0, xorCard0, xorCard0, xorCard0, xorCard0, xorCard0};
        xorCards1 = {xorCard1, xorCard1, xorCard1, xorCard1, xorCard1, xorCard1, xorCard1, xorCard1};
        player1Cards.clear();
        player2Cards.clear();

        texturesLoaded = true;
    }
    void unloadTextures()
    {
        UnloadTexture(initialBinary);
        UnloadTexture(initialBinaryFlipped);
        UnloadTexture(andCard0);
        UnloadTexture(andCard1);
        UnloadTexture(orCard0);
        UnloadTexture(orCard1);
        UnloadTexture(xorCard0);
        UnloadTexture(xorCard1);
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
        for(int i = 0; i<6;i++)
        {
            if(initialBinaries[i]==0)
            {
                DrawTextureEx(initialBinary, initialBinaryPos, 0, 1, WHITE);
            }
            else
            {
                DrawTextureEx(initialBinaryFlipped, initialBinaryPos, 0, 1, WHITE);
            }
            initialBinaryPos.x+=cardWidth+2;
        }
    }
    void randomizePlayerCards()
    {
        SetRandomSeed(time(NULL));
        for(int i = 0;i<7;i++)
        {
            int randomNum = GetRandomValue(0,5);
            if(randomNum == 0 && andCards0.size()>0)
            {
                player1Cards.push_back(andCards0.back());
                andCards0.pop_back();
            }
            if(randomNum == 1 && andCards1.size()>0)
            {
                player1Cards.push_back(andCards1.back());
                andCards1.pop_back();
            }
            if(randomNum == 2 && orCards0.size()>0)
            {
                player1Cards.push_back(orCards0.back());
                orCards0.pop_back();
            }
            if(randomNum == 3 && orCards1.size()>0)
            {
                player1Cards.push_back(orCards1.back());
                orCards1.pop_back();
            }
            if(randomNum == 4 && xorCards0.size()>0)
            {
                player1Cards.push_back(xorCards0.back());
                xorCards0.pop_back();
            }
            if(randomNum == 5 && xorCards1.size()>0)
            {
                player1Cards.push_back(xorCards1.back());
                xorCards1.pop_back();
            }
        }
        for(int i = 0;i<7;i++)
        {
            int randomNum = GetRandomValue(0,5);
            if(randomNum == 0 && andCards0.size()>0)
            {
                player2Cards.push_back(andCards0.back());
                andCards0.pop_back();
            }
            if(randomNum == 1 && andCards1.size()>0)
            {
                player2Cards.push_back(andCards1.back());
                andCards1.pop_back();
            }
            if(randomNum == 2 && orCards0.size()>0)
            {
                player2Cards.push_back(orCards0.back());
                orCards0.pop_back();
            }
            if(randomNum == 3 && orCards1.size()>0)
            {
                player2Cards.push_back(orCards1.back());
                orCards1.pop_back();
            }
            if(randomNum == 4 && xorCards0.size()>0)
            {
                player2Cards.push_back(xorCards0.back());
                xorCards0.pop_back();
            }
            if(randomNum == 5 && xorCards1.size()>0)
            {
                player2Cards.push_back(xorCards1.back());
                xorCards1.pop_back();
            }
        }

    }
    void drawPlayerCards()
    {
        //Set player 1 cards position
        Vector2 player1CardsPos = {10, 10};
        for(int i = 0; i<7;i++)
        {
            DrawTextureEx(player1Cards[i], player1CardsPos, 0, 1, WHITE);
            player1CardsPos.x+=cardWidth+2;
        }

        //Set player 2 cards position
        Vector2 player2CardsPos = {10, 100};
        for(int i = 0; i<7;i++)
        {
            DrawTextureEx(player2Cards[i], player2CardsPos, 0, 1, WHITE);
            player2CardsPos.x+=cardWidth+2;
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
                randomizePlayerCards();
            }
            
            drawInitialBinary();
            drawPlayerCards();
            
            // Vector2 pos = {0, GetScreenHeight()/2 - cardHeight/2 - 2};
            // for(int i = 0, a = 40, row = 5;i < 5;i++)
            // {
            //     pos.x = GetScreenWidth()/2 - cardWidth - a;
            //     for(int j = 0;j < row; j++)
            //     {
            //         DrawTextureEx(andCard1, pos, 180, 1, WHITE);
            //         pos.x+=cardWidth+2;
            //     }
            //     a-=45;
            //     pos.y-=cardHeight-60;
            //     row--;
            // }
            // Vector2 pos2 = {0, GetScreenHeight()/2 + cardHeight/2 + 2};
            // for(int i = 0, a = 40, row = 5;i < 5;i++)
            // {
            //     pos2.x = GetScreenWidth()/2 - cardWidth*2 - a;
            //     for(int j = 0;j < row; j++)
            //     {
            //         DrawTextureEx(andCard0, pos2, 0, 1, WHITE);
            //         pos2.x+=cardWidth+2;
            //     }
            //     a-=45;
            //     pos2.y+=cardHeight-60;
            //     row--;
            // }

            //If escape key pressed return back to Main Menu
            if(IsKeyPressed(KEY_ESCAPE))
            {
                isInPvP = false;
                mainMenu::isInMainMenu = true;
            }
        }
    }
};
