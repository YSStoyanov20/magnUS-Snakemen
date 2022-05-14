#include "PvC.h"
namespace PvC{
    bool texturesLoaded = false;
    bool isInPvC = false;

    //Initialize the all textures
    Texture2D table;
    Texture2D cardBack;
    Texture2D initialBinary;
    Texture2D initialBinaryFlipped;
    Texture2D andCard0;
    Texture2D andCard1;
    Texture2D orCard0;
    Texture2D orCard1;
    Texture2D xorCard0;
    Texture2D xorCard1;
    Texture2D placeCardButton;
    Texture2D placeCardButtonPressed;
    Texture2D discardCardButton;
    Texture2D discardCardButtonPressed;
    Texture2D placeHolder;

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
    float buttonWidth;
    float buttonHeight;

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
        cardBack = LoadTexture("./Sprites/Deck.png");
        table = LoadTexture("./Sprites/Table.png");
        initialBinary = LoadTexture("./Sprites/Initial-Binaries-Reverse.png");
        initialBinaryFlipped = LoadTexture("./Sprites/Initial-Binaries.png");
        andCard0 = LoadTexture("./Sprites/And-Zero-Card.png"); // ID = 7
        andCard1 = LoadTexture("./Sprites/And-One-Card.png"); // ID = 8
        orCard0 = LoadTexture("./Sprites/Or-Zero-Card.png"); // ID = 9
        orCard1 = LoadTexture("./Sprites/Or-One-Card.png"); // ID = 10
        xorCard0 = LoadTexture("./Sprites/XOR-Zero-Card.png"); // ID = 11
        xorCard1 = LoadTexture("./Sprites/XOR-One-Card.png"); // ID = 12
        placeHolder = LoadTexture("./Sprites/placeHolder-Card.png");
        placeCardButton = LoadTexture("./Sprites/Place-Button-Unpressed.png");
        placeCardButtonPressed = LoadTexture("./Sprites/Place-Button-Pressed.png");
        discardCardButton = LoadTexture("./Sprites/Discard-Button-Unpressed.png");
        discardCardButtonPressed = LoadTexture("./Sprites/Discard-Button-Pressed.png");

        //Set the card width and height
        cardWidth = initialBinary.width;
        cardHeight = initialBinary.height;

        //Set the button width and height
        buttonWidth = discardCardButton.width;
        buttonHeight = discardCardButton.height;

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
        playerTurn = true;

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
        UnloadTexture(cardBack);

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
    void drawTable()
    {
        //Draw the table
        DrawTexture(table, 0, 0, WHITE);
        DrawRectangleLinesEx({GetScreenWidth()/2 - cardWidth*3 - 5, GetScreenHeight()/2 - cardHeight/2 - 5, cardWidth*6 + 35, cardHeight + 10}, 2.6, WHITE);
    }

    void addPlayerCards(bool initialCardRandomization)
    {
        //Set the random seed
        SetRandomSeed(time(NULL));
        if(initialCardRandomization)
        {
            //Randomize player 1's hand
            while(player1Cards.size()<4)
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
            while(player2Cards.size()<4)
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
        else
        {
            int randomNum = GetRandomValue(0,5);
            if(playerTurn)
            {
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
            else
            {
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
    }
        
    void drawPlayerCards(Vector2 MousePos)
    {
        //Set player 1 cards position
        Vector2 player1CardsPos = {130, GetScreenHeight()/2 - cardHeight/2};

        //Draw player 1's cards
        for(size_t i = 0; i<player1Cards.size();i++)
        {
            DrawTextureEx(player1Cards[i], player1CardsPos, 0, 1, WHITE);
            //Check if mouse is over a card
            if(CheckCollisionPointRec(MousePos, {player1CardsPos.x, player1CardsPos.y, cardWidth, cardHeight}))
            {
                SetMouseCursor(4);
                DrawRectangleLinesEx({player1CardsPos.x, player1CardsPos.y, cardWidth, cardHeight}, 2.6, RED);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    selectedCard = i;
                }
            }
            //Check if card is selected
            if(int(i) == selectedCard)
            {
                //Outline selected card
                DrawRectangleLinesEx({player1CardsPos.x, player1CardsPos.y, cardWidth, cardHeight}, 2.6, ORANGE);
            }

            player1CardsPos.x+=cardWidth+5;
        }

        //Set player 2 cards position
        Vector2 player2CardsPos = {GetScreenWidth()/2 + cardWidth*4 + 20, GetScreenHeight()/2 - cardHeight/2};

        //Draw player 2's cards
        for(size_t i = 0; i<player2Cards.size();i++)
        {
            //If it is not player's turn, draw the card face down
            DrawTextureEx(cardBack, player2CardsPos, 0, 1, WHITE);
            DrawTextureEx(player2Cards[i], player2CardsPos, 0, 1, WHITE);
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
                DrawTexture(placeHolder, pyramidPos1.x - cardWidth, pyramidPos1.y - cardHeight, WHITE);

                //Check if mouse is over a rectangle
                if(CheckCollisionPointRec(MousePos, {pyramidPos1.x - cardWidth, pyramidPos1.y - cardHeight, cardWidth, cardHeight}) && player1Pyramid[i][j].id == 0)
                {
                    SetMouseCursor(4);
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
            //Initialize card values
            bool card1Value = false;
            bool card2Value = false;
            bool validCard = false;
            


            //Check if it is player 1's turn
            if(playerTurn)
            {
                int id = player1Cards[selectedCard].id;;
                if(selectedPyramidPos[0] == 0)
                {
                    card1Value = bool(!initialBinaries[selectedPyramidPos[1]]);
                    card2Value = bool(!initialBinaries[selectedPyramidPos[1]+1]);
                }
                if(selectedPyramidPos[0] != 0)
                {
                    int card1ID = player1Pyramid[selectedPyramidPos[0]-1][selectedPyramidPos[1]].id;
                    int card2ID = player1Pyramid[selectedPyramidPos[0]-1][selectedPyramidPos[1]+1].id;
                    if(card1ID%2==0)
                    {
                        card1Value = 1;
                    }
                    else if(card1ID%2!=0)
                    {
                        card1Value = 0;
                    }
                    if(card2ID%2==0)
                    {
                        card2Value = 1;
                    }
                    else if(card2ID%2!=0)
                    {
                        card2Value = 0;
                    }
                }
                if((id == 7) && !(card1Value && card2Value))
                {
                    validCard = true;
                }
                if((id == 8) && (card1Value && card2Value))
                {
                    validCard = true;
                }
                if((id == 9) && !(card1Value || card2Value))
                {
                    validCard = true;
                }
                if((id == 10) && (card1Value || card2Value))
                {
                    validCard = true;
                }
                if((id == 11) && !(card1Value ^ card2Value))
                {
                    validCard = true;
                }
                if((id == 12) && (card1Value ^ card2Value))
                {
                    validCard = true;
                }

                
                if(validCard)
                {
                    //Place card in player 1's pyramid
                    player1Pyramid[selectedPyramidPos[0]][selectedPyramidPos[1]] = player1Cards[selectedCard];
                    //Remove card from player 1's hand
                    player1Cards.erase(player1Cards.begin()+selectedCard);
                }
            }
            //Check if it is player 2's turn
            if(!playerTurn)
            {
                int id = player2Cards[selectedCard].id;
                if(selectedPyramidPos[0] == 0)
                {
                    card1Value = bool(initialBinaries[selectedPyramidPos[1]]);
                    card2Value = bool(initialBinaries[selectedPyramidPos[1]+1]);
                }

                if(selectedPyramidPos[0] != 0)
                {
                    int card1ID = player2Pyramid[selectedPyramidPos[0]-1][selectedPyramidPos[1]].id;
                    int card2ID = player2Pyramid[selectedPyramidPos[0]-1][selectedPyramidPos[1]+1].id;
                    if(card1ID%2==0)
                    {
                        card1Value = 1;
                    }
                    else if(card1ID%2!=0)
                    {
                        card1Value = 0;
                    }
                    if(card2ID%2==0)
                    {
                        card2Value = 1;
                    }
                    else if(card2ID%2!=0)
                    {
                        card2Value = 0;
                    }
                }

                if((id == 7) && !(card1Value && card2Value))
                {
                    validCard = true;
                }
                if((id == 8) && (card1Value && card2Value))
                {
                    validCard = true;
                }
                if((id == 9) && !(card1Value || card2Value))
                {
                    validCard = true;
                }
                if((id == 10) && (card1Value || card2Value))
                {
                    validCard = true;
                }
                if((id == 11) && !(card1Value ^ card2Value))
                {
                    validCard = true;
                }
                if((id == 12) && (card1Value ^ card2Value))
                {
                    validCard = true;
                }

                
                if(validCard)
                {
                    //Place card in player 1's pyramid
                    player2Pyramid[selectedPyramidPos[0]][selectedPyramidPos[1]] = player2Cards[selectedCard];
                    //Remove card from player 1's hand
                    player2Cards.erase(player2Cards.begin()+selectedCard);
                }
            }
            //Change player turn
            if(validCard)
            {
                playerTurn = !playerTurn;
            }
        }

        //Reset the selected card
        selectedCard = -1;
        //Reset the selected pyramid position
        selectedPyramidPos[0] = -1;
        selectedPyramidPos[1] = -1;
        
    }
    void discardCard()
    {
        //Check if player has selected a card
        if(selectedCard != -1)
        {
            //Check if it is player 1's turn
            if(playerTurn)
            {
                switch(player1Cards[selectedCard].id)
                {
                    case 7:
                        andCards0.push_back(player1Cards[selectedCard]);
                        break;
                    case 8:
                        andCards1.push_back(player1Cards[selectedCard]);
                        break;
                    case 9:
                        orCards0.push_back(player1Cards[selectedCard]);
                        break;
                    case 10:
                        orCards1.push_back(player1Cards[selectedCard]);
                        break;
                    case 11:
                        xorCards0.push_back(player1Cards[selectedCard]);
                        break;
                    case 12:
                        xorCards1.push_back(player1Cards[selectedCard]);
                        break;
                    default:
                        break;
                }
                player1Cards.erase(player1Cards.begin()+selectedCard);
            }
            //Check if it is player 2's turn
            if(!playerTurn)
            {
                switch(player2Cards[selectedCard].id)
                {
                    case 7:
                        andCards0.push_back(player2Cards[selectedCard]);
                        break;
                    case 8:
                        andCards1.push_back(player2Cards[selectedCard]);
                        break;
                    case 9:
                        orCards0.push_back(player2Cards[selectedCard]);
                        break;
                    case 10:
                        orCards1.push_back(player2Cards[selectedCard]);
                        break;
                    case 11:
                        xorCards0.push_back(player2Cards[selectedCard]);
                        break;
                    case 12:
                        xorCards1.push_back(player2Cards[selectedCard]);
                        break;
                    default:
                        break;
                }
                player2Cards.erase(player2Cards.begin()+selectedCard);
            }
            //Change player turn
            playerTurn = !playerTurn;
        }
        //Reset the selected card
        selectedCard = -1;
    }
    void computerTurn()
    {
        Vector2 pyramidPos2 = {0, GetScreenHeight()/2 + cardHeight/2 + 5};
        for(size_t i = 0; i<player2Cards.size();i++)
        {
            selectedCard = i;
            for(int j = 0, spaceBetween = 40, row = 5;j<5;j++)
            {
                pyramidPos2.x = GetScreenWidth()/2 - cardWidth*2 - spaceBetween;
                for(int k = 0; k < row; k++)
                {
                    if(((row == 5 && player2Pyramid[j][k].id == 0) || (player2Pyramid[j-1][k].id != 0 && player2Pyramid[j-1][k+1].id != 0)) && !playerTurn)
                    {
                        if(player2Pyramid[j][k].id == 0)
                        {
                            selectedPyramidPos[0] = j;
                            selectedPyramidPos[1] = k;
                            placeCard();
                        }
                    }
                    pyramidPos2.x+=cardWidth+2;
                }
                spaceBetween-=45;
                pyramidPos2.y+=cardHeight-60;
                row--;
            }
        }
        if(!playerTurn)
        {
            selectedCard = GetRandomValue(0,player2Cards.size()-1);
            discardCard();
        }
    }
    void drawButtons(Vector2 MousePos)
    {
        Vector2 placeCardButtonPos = {float(buttonWidth*1.2), GetScreenHeight()/2 + buttonHeight*4};
        DrawTextureEx(placeCardButton, placeCardButtonPos, 0, 1, WHITE);
        //Detect if the mouse is over the menu button
        if(CheckCollisionPointRec(MousePos, {placeCardButtonPos.x, placeCardButtonPos.y + 4, buttonWidth, buttonHeight}))
        {
            SetMouseCursor(4);
            DrawRectangle(placeCardButtonPos.x, placeCardButtonPos.y, buttonWidth, buttonHeight, {55, 148, 110, 255});
            DrawTexture(placeCardButtonPressed, placeCardButtonPos.x, placeCardButtonPos.y + 4, WHITE);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && playerTurn)
            {
                placeCard();
            }     
        }
        
        Vector2 discardCardButtonPos = {GetScreenWidth()-float(buttonWidth*2.1), GetScreenHeight()/2 + buttonHeight*4};
        DrawTexture(discardCardButton, discardCardButtonPos.x, discardCardButtonPos.y, WHITE);
        //Detect if the mouse is over the menu button
        if(CheckCollisionPointRec(MousePos, {discardCardButtonPos.x, discardCardButtonPos.y + 4, buttonWidth, buttonHeight}))
        {
            SetMouseCursor(4);
            DrawRectangle(discardCardButtonPos.x, discardCardButtonPos.y, buttonWidth, buttonHeight, {55, 148, 110, 255});
            DrawTexture(discardCardButtonPressed, discardCardButtonPos.x, placeCardButtonPos.y + 4, WHITE);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && playerTurn)
            {
                discardCard();
            }    
        }
    }
    void displayPlayerTurn()
    {
        if(playerTurn)
        {
            DrawText("Player 1's turn", GetScreenWidth() - 300, 60, 30, BLACK);
        }
        else
        {
            DrawText("Player 2's turn", GetScreenWidth() - 300, 60, 30, BLACK);
        }
    }
    void addCardOnEachTurn()
    {
        if(playerTurn && player1Cards.size()<5)
        {
            addPlayerCards(false);
        }
        if(!playerTurn && player2Cards.size()<5)
        {
            addPlayerCards(false);
        }
    }
    void hasPlayerWon()
    {
        if(player1Pyramid[4][0].id!=0)
        {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), { 0, 0, 0, 220 });
            DrawText("Player 1 wins!", GetScreenWidth()/2 - 330, GetScreenHeight()/2 - 300, 100, WHITE);
            DrawText("Press ESC to exit", GetScreenWidth()/2 - 200, GetScreenHeight()/2 - 180, 40, WHITE);
        }
        if(player2Pyramid[4][0].id!=0)
        {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), { 0, 0, 0, 220 });
            DrawText("Player 2 wins", GetScreenWidth()/2 - 330, GetScreenHeight()/2 - 300, 100, WHITE);
            DrawText("Press ESC to exit", GetScreenWidth()/2 - 200, GetScreenHeight()/2 - 180, 40, WHITE);
        }
    }
    void startGame()
    {

        if(isInPvC)
        {
            SetMouseCursor(0);
            //Get mouse position            
            Vector2 MousePos = {GetMousePosition().x, GetMousePosition().y};

            //Load the textures if not loaded
            if(!texturesLoaded)
            {
                loadTextures();
                randomizeInitialBinary();
                addPlayerCards(true);
            }

            drawTable();
            drawInitialBinary();
            drawPyramids(MousePos);
            drawPlayerCards(MousePos);
            displayPlayerTurn();
            drawButtons(MousePos);
            addCardOnEachTurn();
            hasPlayerWon();
            if(!playerTurn)
            {
                computerTurn();
            }

            //Display mouse position
            DrawText(TextFormat("%0.f, %0.f", MousePos.x, MousePos.y), 10, 10, 20, BLACK);

            //If escape key pressed return back to Main Menu
            if(IsKeyPressed(KEY_ESCAPE))
            {
                isInPvC = false;
                mainMenu::isInMainMenu = true;
            }
        }
    }
};
