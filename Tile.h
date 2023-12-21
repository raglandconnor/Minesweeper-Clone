//
// Created by Connor Ragland on 12/20/23.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#ifndef MINESWEEPER_CLONE_TILE_H
#define MINESWEEPER_CLONE_TILE_H


class Tile {
public:
    sf::Sprite tileSprite;
    sf::Sprite mineSprite;
    sf::Sprite flagSprite;
    sf::Sprite numSprite;
    sf::Sprite allRevealedSprite;

    int x;
    int y;
    void setPos(int height, int width, int cols, int rows);

    bool isRevealed;
    bool mine;
    bool flag;

    int numAdjacentMines;
    Tile* adjacentTiles[8];
};


#endif //MINESWEEPER_CLONE_TILE_H
