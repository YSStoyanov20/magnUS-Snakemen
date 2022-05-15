#include "PvP.h"
using namespace global;
namespace PvP{
    bool isInPvP = false;
    
    void drawPlayerCards(Vector2 MousePos)
    {
        //Set player 1 cards position
        Vector2 player1CardsPos = {130, GetScreenHeight()/2 - cardHeight/2};

        //Draw player 1's cards
        for(size_t i = 0; i<player1Cards.size();i++)
        {
            if(playerTurn)
            {
                DrawTextureEx(player1Cards[i], player1CardsPos, 0, 1, WHITE);
                //Check if mouse is over a card
                if(CheckCollisionPointRec(MousePos, {player1CardsPos.x, player1CardsPos.y, cardWidth, cardHeight}) && !gameOver)
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
            }
            else
            {
                //If it is not player's turn, draw the card face down
                DrawTextureEx(cardBack, player1CardsPos, 0, 1, WHITE);
            }
            player1CardsPos.x+=cardWidth+5;
        }

        //Set player 2 cards position
        Vector2 player2CardsPos = {GetScreenWidth()/2 + cardWidth*4 + 20, GetScreenHeight()/2 - cardHeight/2};

        //Draw player 2's cards
        for(size_t i = 0; i<player2Cards.size();i++)
        {
            if(!playerTurn)
            {
                DrawTextureEx(player2Cards[i], player2CardsPos, 0, 1, WHITE);
                //Check if mouse is over a card
                if(CheckCollisionPointRec(MousePos, {player2CardsPos.x, player2CardsPos.y, cardWidth, cardHeight}) && !gameOver)
                {
                    SetMouseCursor(4);
                    DrawRectangleLinesEx({player2CardsPos.x, player2CardsPos.y, cardWidth, cardHeight}, 2.6, RED);
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        selectedCard = i;
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
                DrawTextureEx(cardBack, player2CardsPos, 0, 1, WHITE);
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
                DrawTexture(placeHolder, pyramidPos1.x - cardWidth, pyramidPos1.y - cardHeight, WHITE);

                //Check if mouse is over a rectangle
                if(CheckCollisionPointRec(MousePos, {pyramidPos1.x - cardWidth, pyramidPos1.y - cardHeight, cardWidth, cardHeight}) && player1Pyramid[i][j].id == 0 && !gameOver)
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
                if(((row == 5 && player2Pyramid[i][j].id == 0) || (player2Pyramid[i-1][j].id != 0 && player2Pyramid[i-1][j+1].id != 0)) && !playerTurn)
                {
                    DrawTexture(placeHolder, pyramidPos2.x, pyramidPos2.y, WHITE);

                    //Check if mouse is over a rectangle
                    if(CheckCollisionPointRec(MousePos, {pyramidPos2.x, pyramidPos2.y, cardWidth, cardHeight}) && player2Pyramid[i][j].id == 0 && !gameOver)
                    {
                        SetMouseCursor(4);
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
    void drawButtons(Vector2 MousePos)
    {
        Vector2 placeCardButtonPos = {GetScreenWidth()-float(buttonWidth*2.1), GetScreenHeight()/2 + buttonHeight*4};
        DrawTextureEx(placeCardButton, placeCardButtonPos, 0, 1, WHITE);
        if(CheckCollisionPointRec(MousePos, {placeCardButtonPos.x, placeCardButtonPos.y + 4, buttonWidth, buttonHeight}) && !gameOver)
        {
            SetMouseCursor(4);
            DrawRectangle(placeCardButtonPos.x, placeCardButtonPos.y, buttonWidth, buttonHeight, {55, 148, 110, 255});
            DrawTexture(placeCardButtonPressed, placeCardButtonPos.x, placeCardButtonPos.y + 4, WHITE);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                placeCard();
            }     
        }
        
        Vector2 discardCardButtonPos = {float(buttonWidth*1.2), GetScreenHeight()/2 + buttonHeight*4};
        DrawTexture(discardCardButton, discardCardButtonPos.x, discardCardButtonPos.y, WHITE);
        if(CheckCollisionPointRec(MousePos, {discardCardButtonPos.x, discardCardButtonPos.y + 4, buttonWidth, buttonHeight}) && !gameOver)
        {
            SetMouseCursor(4);
            DrawRectangle(discardCardButtonPos.x, discardCardButtonPos.y, buttonWidth, buttonHeight, {55, 148, 110, 255});
            DrawTexture(discardCardButtonPressed, discardCardButtonPos.x, placeCardButtonPos.y + 4, WHITE);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                discardCard();
            }     
        }
    }
    void startGame()
    {

        if(isInPvP)
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
            drawPlayerCards(MousePos);
            drawPyramids(MousePos);
            displayPlayerTurn();
            drawButtons(MousePos);
            addCardOnEachTurn();
            hasPlayerWon();

            //If escape key pressed return back to Main Menu
            if(IsKeyPressed(KEY_ESCAPE))
            {
                isInPvP = false;
                mainMenu::isInMainMenu = true;
            }
        }
    }
};
