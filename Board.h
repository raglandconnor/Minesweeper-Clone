//
// Created by Connor Ragland on 12/20/23.
//
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "TextureManager.h"
#include "Tile.h"

using namespace std;

#ifndef MINESWEEPER_CLONE_BOARD_H
#define MINESWEEPER_CLONE_BOARD_H


class Board {
public:
    Board(int cols, int rows, int mineCount, string username);
    void run();
    vector<vector<Tile>> boardVect;
    string username;
    int newScoreIdx;

    int cols;
    int rows;
    int mineCount;

private:
    sf::RenderWindow mainWindow;

    // Textures
    // For tiles
    sf::Texture& hiddenTexture = TextureManager::getTexture("tile_hidden");
    sf::Texture& revealedTexture = TextureManager::getTexture("tile_revealed");
    sf::Texture& flagTexture = TextureManager::getTexture("flag");
    sf::Texture& mineTexture = TextureManager::getTexture("mine");
    // For board
    sf::Texture& num_1_texture = TextureManager::getTexture("number_1");
    sf::Texture& num_2_texture = TextureManager::getTexture("number_2");
    sf::Texture& num_3_texture = TextureManager::getTexture("number_3");
    sf::Texture& num_4_texture = TextureManager::getTexture("number_4");
    sf::Texture& num_5_texture = TextureManager::getTexture("number_5");
    sf::Texture& num_6_texture = TextureManager::getTexture("number_6");
    sf::Texture& num_7_texture = TextureManager::getTexture("number_7");
    sf::Texture& num_8_texture = TextureManager::getTexture("number_8");
    // For UI
    sf::Texture& winFaceTexture = TextureManager::getTexture("face_win");
    sf::Texture& happyFaceTexture = TextureManager::getTexture("face_happy");
    sf::Texture& sadFaceTexture = TextureManager::getTexture("face_lose");
    sf::Texture& debugTexture = TextureManager::getTexture("debug");
    sf::Texture& pauseTexture = TextureManager::getTexture("pause");
    sf::Texture& playTexture = TextureManager::getTexture("play");
    sf::Texture& leaderboardTexture = TextureManager::getTexture("leaderboard");
    // For timer
    sf::Texture& digitsTexture = TextureManager::getTexture("digits");

    // UI Sprites
    sf::Sprite faceSprite;
    sf::Sprite debugSprite;
    sf::Sprite playPauseSprite;
    sf::Sprite leaderboardSprite;
    // For Counter
    sf::Sprite counter_1_sprite;
    sf::Sprite counter_2_sprite;
    sf::Sprite counter_3_sprite;
    // For Timer
    sf::Sprite timer_1_sprite;
    sf::Sprite timer_2_sprite;
    sf::Sprite timer_3_sprite;
    sf::Sprite timer_4_sprite;

    // Leaderboard

    sf::Clock clock;
    sf::Time paused_time;
    sf::Time elapsed_time;


    bool win;
    bool lose;
    int minesPlaced;
    int flagsPlaced;

    bool paused;
    bool revealTiles;
    bool showMines;  // Debug button

    // Initialize
    void initializeSprites();
    void setMines();
    void initializeTiles();
    void calculateAdjacent();

    // Event handler
    void revealRecursive(Tile* tile);
    void revealNumber(Tile* tile);  // Reveal the 3x3 around a number that the user clicks
    void pauseGame();
    void resetGame();
    void eventDebug();
    void eventPlayPause();
    void eventRevealTiles(sf::Vector2i mouse);
    void eventRevealTilesNum(sf::Vector2i mouse);
    void eventPlaceFlag(sf::Vector2i mouse);
    void eventLeaderboard();
    void handleEvents();

    // Update
    void updateCounter();
    void updateTimer();
    void updateLeaderboard(int winningTimeSeconds, string winningName);
    void checkWin();
    void checkLose();
    void update();

    // Render
    void renderTiles();
    void renderNumAdj();
    void renderFlags();
    void renderUI();
    void renderMines();
    void render();

    void printCL();  // Debug
};


#endif //MINESWEEPER_CLONE_BOARD_H
