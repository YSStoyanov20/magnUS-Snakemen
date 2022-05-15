#include "PvC.h"
using namespace global;
namespace PvC{
    bool isInPvC = false;
        
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

        //Set computer's cards position
        Vector2 player2CardsPos = {GetScreenWidth()/2 + cardWidth*4 + 20, GetScreenHeight()/2 - cardHeight/2};

        //Draw computer's cards
        for(size_t i = 0; i<player2Cards.size();i++)
        {
            DrawTextureEx(cardBack, player2CardsPos, 0, 1, WHITE);
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

        //Set computer's pyramid position
        Vector2 pyramidPos2 = {0, GetScreenHeight()/2 + cardHeight/2 + 5};

        //Draw computer's pyramid
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
        Vector2 placeCardButtonPos = {GetScreenWidth()-float(buttonWidth*2.1), GetScreenHeight()/2 + buttonHeight*4};
        DrawTextureEx(placeCardButton, placeCardButtonPos, 0, 1, WHITE);
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
        
        Vector2 discardCardButtonPos = {float(buttonWidth*1.2), GetScreenHeight()/2 + buttonHeight*4};
        DrawTexture(discardCardButton, discardCardButtonPos.x, discardCardButtonPos.y, WHITE);
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

            //If escape key pressed return back to Main Menu
            if(IsKeyPressed(KEY_ESCAPE))
            {
                isInPvC = false;
                mainMenu::isInMainMenu = true;
            }
        }
    }
};
