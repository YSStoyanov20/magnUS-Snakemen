#pragma once
#include "PvP.h"
#include "PvC.h"
#include "mainMenu.h"
#include <vector>
#include <time.h>
namespace global{
    extern bool texturesLoaded;
    extern bool gameOver;

    //Initialize the all textures
    extern Texture2D table;
    extern Texture2D cardBack;
    extern Texture2D initialBinary;
    extern Texture2D initialBinaryFlipped;
    extern Texture2D andCard0;
    extern Texture2D andCard1;
    extern Texture2D orCard0;
    extern Texture2D orCard1;
    extern Texture2D xorCard0;
    extern Texture2D xorCard1;
    extern Texture2D placeCardButton;
    extern Texture2D placeCardButtonPressed;
    extern Texture2D discardCardButton;
    extern Texture2D discardCardButtonPressed;
    extern Texture2D placeHolder;

    //Initialize deck vectors
    extern std::vector<Texture2D> andCards0;
    extern std::vector<Texture2D> andCards1;
    extern std::vector<Texture2D> orCards0;
    extern std::vector<Texture2D> orCards1;
    extern std::vector<Texture2D> xorCards0;
    extern std::vector<Texture2D> xorCards1;
    
    //Initialize player's hands
    extern std::vector<Texture2D> player1Cards;
    extern std::vector<Texture2D> player2Cards;

    //Initialize card width and height
    extern float cardWidth;
    extern float cardHeight;
    extern float buttonWidth;
    extern float buttonHeight;

    //Initialize initial binary array
    extern int initialBinaries[6];

    //Initialize players' pyramids
    extern Texture2D player1Pyramid[5][5];
    extern Texture2D player2Pyramid[5][5];

    //Initialize player turn
    extern bool playerTurn;

    //Initialize selected card
    extern int selectedCard;

    //Initialize pyramid positions
    extern int selectedPyramidPos[2];

    //Initialize all functions
    void loadTextures();
    void unloadTextures();
    void randomizeInitialBinary();
    void drawInitialBinary();
    void drawTable();
    void addPlayerCards(bool initialCardRandomization);
    void placeCard();
    void discardCard();
    void displayPlayerTurn();
    void addCardOnEachTurn();
    void hasPlayerWon();
    float scale();
};