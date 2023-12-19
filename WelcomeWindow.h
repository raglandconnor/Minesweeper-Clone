//
// Created by Connor Ragland on 12/18/23.
//

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

#ifndef MINESWEEPER_CLONE_WELCOMEWINDOW_H
#define MINESWEEPER_CLONE_WELCOMEWINDOW_H


class WelcomeWindow {
public:
    WelcomeWindow(int cols, int rows);
    bool closed;
    void run();
    string nameInputString;

private:
    sf::RenderWindow welcomeWindow;
    sf::Font font;
    sf::Text welcomeText;
    sf::FloatRect welcomeTextRect;
    sf::Text enterName;
    sf::FloatRect enterNameRect;
    sf::Text nameInput;

    unsigned int name_count;

    void initializeText();
    void handleEvents();
    void update();
    void render();
};


#endif //MINESWEEPER_CLONE_WELCOMEWINDOW_H
