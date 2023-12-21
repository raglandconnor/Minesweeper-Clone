//
// Created by Connor Ragland on 12/20/23.
//

#include "Tile.h"

void Tile::setPos(int height, int width, int cols, int rows) {
    this->x = width * 32;
    this->y = height * 32;

    tileSprite.setPosition(x, y);
    mineSprite.setPosition(x, y);
    flagSprite.setPosition(x, y);
    numSprite.setPosition(x, y);
    allRevealedSprite.setPosition(x, y);
}