#include "PvP.h"
namespace PvP{
    bool texturesLoaded = false;
    bool isInPvP = false;

    //Initialize the all textures
    Texture2D table;
    Texture2D deck;
    Texture2D initialBinary;
    Texture2D initialBinaryFlipped;
    Texture2D andCard0;
    Texture2D andCard1;
    Texture2D orCard0;
    Texture2D orCard1;
    Texture2D xorCard0;
    Texture2D xorCard1;

    //Initialize deck vectors
    std::vector<Texture2D> andCards0;
    std::vector<Texture2D> andCards1;
    std::vector<Texture2D> orCards0;
    std::vector<Texture2D> orCards1;
    std::vector<Texture2D> xorCards0;
    std::vector<Texture2D> xorCards1;
    
    //Initialize player's hands
    std::vector<Texture2D> player1Cards;
    std::vector<Texture2D> player2Cards;

    //Initialize card width and height
    float cardWidth;
    float cardHeight;

    //Initialize initial binary array
    int initialBinaries[6];

    //Initialize players' pyramids
    Texture2D player1Pyramid[5][5];
    Texture2D player2Pyramid[5][5];

    //Initialize player turn
    bool playerTurn;

    //Initialize selected card
    int selectedCard;

    //Initialize pyramid positions
    int selectedPyramidPos[2];

    void loadTextures()
    {
        //Load all textures
        deck = LoadTexture("./Sprites/Deck.png");
        table = LoadTexture("./Sprites/Table.png");
        initialBinary = LoadTexture("./Sprites/Initial-Binaries-Reverse.png");
        initialBinaryFlipped = LoadTexture("./Sprites/Initial-Binaries.png");
        andCard0 = LoadTexture("./Sprites/And-Zero-Card.png"); // ID = 7
        andCard1 = LoadTexture("./Sprites/And-One-Card.png"); // ID = 8
        orCard0 = LoadTexture("./Sprites/Or-Zero-Card.png"); // ID = 9
        orCard1 = LoadTexture("./Sprites/Or-One-Card.png"); // ID = 10
        xorCard0 = LoadTexture("./Sprites/XOR-Zero-Card.png"); // ID = 11
        xorCard1 = LoadTexture("./Sprites/XOR-One-Card.png"); // ID = 12

        //Set the card width and height
        cardWidth = initialBinary.width;
        cardHeight = initialBinary.height;

        //Define deck
        andCards0 = {andCard0, andCard0, andCard0, andCard0, andCard0, andCard0, andCard0, andCard0};
        andCards1 = {andCard1, andCard1, andCard1, andCard1, andCard1, andCard1, andCard1, andCard1};
        orCards0 = {orCard0, orCard0, orCard0, orCard0, orCard0, orCard0, orCard0, orCard0};
        orCards1 = {orCard1, orCard1, orCard1, orCard1, orCard1, orCard1, orCard1, orCard1};
        xorCards0 = {xorCard0, xorCard0, xorCard0, xorCard0, xorCard0, xorCard0, xorCard0, xorCard0};
        xorCards1 = {xorCard1, xorCard1, xorCard1, xorCard1, xorCard1, xorCard1, xorCard1, xorCard1};

        //Clear players' hands
        player1Cards.clear();
        player2Cards.clear();

        //Clear players' pyramids
        for(int i = 0; i<5;i++)
        {
            for(int j = 0; j<5;j++)
            {
                player2Pyramid[i][j].id = 0;
                player1Pyramid[i][j].id = 0;
            }
        }

        //Reset selected card
        selectedCard = -1;

        //Reset selected pyramid position
        selectedPyramidPos[0] = -1;
        selectedPyramidPos[1] = -1;

        //Reset player turn
        playerTurn = false;

        texturesLoaded = true;
    }
    void unloadTextures()
    {
        //Unload all textures
        UnloadTexture(initialBinary);
        UnloadTexture(initialBinaryFlipped);
        UnloadTexture(andCard0);
        UnloadTexture(andCard1);
        UnloadTexture(orCard0);
        UnloadTexture(orCard1);
        UnloadTexture(xorCard0);
        UnloadTexture(xorCard1);
        UnloadTexture(table);
        UnloadTexture(deck);

        texturesLoaded = false;
    }
    void randomizeInitialBinary()
    {
        //Set the random seed
        SetRandomSeed(time(NULL));

        //Randomize the initial binary
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

        //Draw the initial binary
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
            initialBinaryPos.x+=cardWidth+5;
        }
    }
    void DrawTable()
    {
        //Draw the table
        DrawTexture(table, 0, 0, WHITE);
        DrawRectangleLinesEx({GetScreenWidth()/2 - cardWidth*3 - 5, GetScreenHeight()/2 - cardHeight/2 - 5, cardWidth*6 + 35, cardHeight + 10}, 2.6, WHITE);
    }

    void DrawDeck()
    {
        //Draw the deck
        DrawTexture(deck, 144, 750, WHITE);
    }

    void randomizePlayerCards()
    {
        //Set the random seed
        SetRandomSeed(time(NULL));

        //Randomize player 1's hand
        for(int i = 0;i<4;i++)
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

        //Randomize player 2's hand
        for(int i = 0;i<4;i++)
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
        
    void drawPlayerCards(Vector2 MousePos)
    {
        //Set player 1 cards position
        Vector2 player1CardsPos = {100, 100};

        //Draw player 1's cards
        for(size_t i = 0; i<player1Cards.size();i++)
        {
            if(playerTurn)
            {
                DrawTextureEx(player1Cards[i], player1CardsPos, 0, 1, WHITE);
                //Check if mouse is over a card
                if(CheckCollisionPointRec(MousePos, {player1CardsPos.x, player1CardsPos.y, cardWidth, cardHeight}))
                {
                    DrawRectangleLinesEx({player1CardsPos.x, player1CardsPos.y, cardWidth, cardHeight}, 2.6, RED);
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        selectedCard = i;
                        std::cout<<player1Cards[i].id<<std::endl;
                    }
                }
                //Check if card is selected
                if(int(i) == selectedCard)
                {
                    //Outline selected card
                    DrawRectangleLinesEx({player1CardsPos.x, player1CardsPos.y, cardWidth, cardHeight}, 2.6, ORANGE);
                }
            }
            else
            {
                //If it is not player's turn, draw the card face down
                DrawTextureEx(deck, player1CardsPos, 0, 1, WHITE);
            }
            player1CardsPos.x+=cardWidth+5;
        }

        //Set player 2 cards position
        Vector2 player2CardsPos = {1000, 100};

        //Draw player 2's cards
        for(size_t i = 0; i<player2Cards.size();i++)
        {
            if(!playerTurn)
            {
                DrawTextureEx(player2Cards[i], player2CardsPos, 0, 1, WHITE);
                //Check if mouse is over a card
                if(CheckCollisionPointRec(MousePos, {player2CardsPos.x, player2CardsPos.y, cardWidth, cardHeight}))
                {
                    DrawRectangleLinesEx({player2CardsPos.x, player2CardsPos.y, cardWidth, cardHeight}, 2.6, RED);
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        selectedCard = i;
                        std::cout<<player2Cards[i].id<<std::endl;
                    }
                }
                //Check if card is selected
                if(int(i) == selectedCard)
                {
                    //Outline selected card
                    DrawRectangleLinesEx({player2CardsPos.x, player2CardsPos.y, cardWidth, cardHeight}, 2.6, ORANGE);
                }
            }
            else
            {
                //If it is not player's turn, draw the card face down
                DrawTextureEx(deck, player2CardsPos, 0, 1, WHITE);
            }
            player2CardsPos.x+=cardWidth+5;
        }
    }
    void drawPyramids(Vector2 MousePos)
    {
        //Set player 1 pyramids position
        Vector2 pyramidPos1 = {0, GetScreenHeight()/2 - cardHeight/2 - 5};

        //Draw player 1's pyramid
        for(int i = 0, spaceBetween = 40, row = 5;i < 5;i++)
        {
            pyramidPos1.x = GetScreenWidth()/2 - cardWidth - spaceBetween;
            for(int j = 0;j < row; j++)
            {
                if(((row == 5 && player1Pyramid[i][j].id == 0) || (player1Pyramid[i-1][j].id != 0 && player1Pyramid[i-1][j+1].id != 0)) && playerTurn)
                {
                //If card can be placed, draw a rectangle
                DrawRectangle(pyramidPos1.x - cardWidth, pyramidPos1.y - cardHeight, cardWidth, cardHeight, BLACK);

                //Check if mouse is over a rectangle
                if(CheckCollisionPointRec(MousePos, {pyramidPos1.x - cardWidth, pyramidPos1.y - cardHeight, cardWidth, cardHeight}) && player1Pyramid[i][j].id == 0)
                {
                    //Outline selected card
                    DrawRectangleLinesEx({pyramidPos1.x - cardWidth, pyramidPos1.y - cardHeight, cardWidth, cardHeight}, 2.6, RED);
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        //Set selected card
                        selectedPyramidPos[0] = i;
                        selectedPyramidPos[1] = j;
                    }
                }
            }
            //Check if card is selected
            if(selectedPyramidPos[0] == i && selectedPyramidPos[1] == j && playerTurn)
            {
                //Outline selected card
                DrawRectangleLinesEx({pyramidPos1.x - cardWidth, pyramidPos1.y - cardHeight, cardWidth, cardHeight}, 2.6, ORANGE);
            }
            if(player1Pyramid[i][j].id!=0)
                {
                    //Draw the card if placed
                    DrawTextureEx(player1Pyramid[i][j], pyramidPos1, 180, 1, WHITE);
                }
                pyramidPos1.x+=cardWidth+2;
                }
                spaceBetween-=45;
                pyramidPos1.y-=cardHeight-60;
                row--;
        }

        //Set player 2 pyramid position
        Vector2 pyramidPos2 = {0, GetScreenHeight()/2 + cardHeight/2 + 5};

        //Draw player 2 pyramid
        for(int i = 0, spaceBetween = 40, row = 5;i < 5;i++)
        {
            pyramidPos2.x = GetScreenWidth()/2 - cardWidth*2 - spaceBetween;
            for(int j = 0;j < row; j++)
            {
                if(((row == 5 && player2Pyramid[i][j].id == 0) || (player2Pyramid[i-1][j].id != 0 && player2Pyramid[i-1][j+1].id != 0)) && !playerTurn)
                {
                    //If card can be placed, draw a rectangle
                    DrawRectangle(pyramidPos2.x, pyramidPos2.y, cardWidth, cardHeight, BLACK);

                    //Check if mouse is over a rectangle
                    if(CheckCollisionPointRec(MousePos, {pyramidPos2.x, pyramidPos2.y, cardWidth, cardHeight}) && player2Pyramid[i][j].id == 0)
                    {
                        //Outline selected card
                        DrawRectangleLinesEx({pyramidPos2.x, pyramidPos2.y, cardWidth, cardHeight}, 2.6, RED);
                        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        {
                            //Set selected card
                            selectedPyramidPos[0] = i;
                            selectedPyramidPos[1] = j;
                        }
                    }
                }
                //Check if card is selected
                if(selectedPyramidPos[0] == i && selectedPyramidPos[1] == j && !playerTurn)
                {
                    //Outline selected card
                    DrawRectangleLinesEx({pyramidPos2.x, pyramidPos2.y, cardWidth, cardHeight}, 2.6, ORANGE);
                }
                if(player2Pyramid[i][j].id!=0)
                {
                    //Draw the card if placed
                    DrawTextureEx(player2Pyramid[i][j], pyramidPos2, 0, 1, WHITE);
                }
                pyramidPos2.x+=cardWidth+2;
            }
            spaceBetween-=45;
            pyramidPos2.y+=cardHeight-60;
            row--;
        }

    }
    void placeCard()
    {
        //Check if player has selected a card and a pyramid position
        if(selectedCard != -1 && selectedPyramidPos[0] != -1 && selectedPyramidPos[1] != -1)
        {
            //Check if it is player 1's turn
            if(playerTurn)
            {
                //Place card in player 1's pyramid
                player1Pyramid[selectedPyramidPos[0]][selectedPyramidPos[1]] = player1Cards[selectedCard];
                //Remove card from player 1's hand
                player1Cards.erase(player1Cards.begin()+selectedCard);
            }
            //Check if it is player 2's turn
            if(!playerTurn)
            {
            //Place card in player 2's pyramid
            player2Pyramid[selectedPyramidPos[0]][selectedPyramidPos[1]] = player2Cards[selectedCard];
            //Remove card from player 2's hand
            player2Cards.erase(player2Cards.begin()+selectedCard);
            }
            //Change player turn
            playerTurn = !playerTurn;
        }
        for(int i = 0;i<300;i++)
        {
            DrawText("Card or position not selected", GetScreenWidth()/2, GetScreenHeight()/2, 20, RED);
        }
        //Reset the selected card
        selectedCard = -1;
        //Reset the selected pyramid position
        selectedPyramidPos[0] = -1;
        selectedPyramidPos[1] = -1;
        
    }
    void setCards()
    {
        if(isInPvP)
        {
            //Get mouse position            
            Vector2 MousePos = {GetMousePosition().x, GetMousePosition().y};

            //Load the textures if not loaded
            if(!texturesLoaded)
            {
                loadTextures();
                randomizeInitialBinary();
                randomizePlayerCards();
            }

            DrawTable();
            DrawDeck();
            drawInitialBinary();
            drawPlayerCards(MousePos);
            drawPyramids(MousePos);

            //Display mouse position
            DrawText(TextFormat("%0.f, %0.f", MousePos.x, MousePos.y), 10, 10, 20, BLACK);

            DrawRectangle(10, 300, 50, 50, BLACK);

            if(CheckCollisionPointRec(MousePos, {10, 300, 50, 50}))
            {

                DrawRectangle(10, 300, 50, 50, BLUE);

                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    playerTurn = false;
                }
            }
            DrawRectangle(1100,250,100,50,BLACK);
            if(CheckCollisionPointRec(MousePos, {1100,250,100,50}))
            {
                DrawRectangle(1100,250,100,50,BLUE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    
                    
                        placeCard();
                    
                }
            }

            //If escape key pressed return back to Main Menu
            if(IsKeyPressed(KEY_ESCAPE))
            {
                isInPvP = false;
                mainMenu::isInMainMenu = true;
            }
        }
    }
};
