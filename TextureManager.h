//
// Created by Connor Ragland on 12/20/23.
//
#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
using namespace std;

#ifndef MINESWEEPER_CLONE_TEXTUREMANAGER_H
#define MINESWEEPER_CLONE_TEXTUREMANAGER_H

class TextureManager {
    static unordered_map<string, sf::Texture> textures;

public:
    static sf::Texture& getTexture(string textureName);
};



#endif //MINESWEEPER_CLONE_TEXTUREMANAGER_H
