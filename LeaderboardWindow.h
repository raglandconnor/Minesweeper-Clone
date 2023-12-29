//
// Created by Connor Ragland on 12/27/23.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

#ifndef MINESWEEPER_CLONE_LEADERBOARDWINDOW_H
#define MINESWEEPER_CLONE_LEADERBOARDWINDOW_H


class LeaderboardWindow {
public:
    LeaderboardWindow(int cols, int rows, int newIdx);
    void run();

    int cols;
    int rows;
    int newIdx;

    sf::RenderWindow leaderboardWindow;

private:
    sf::Font font;
    sf::Text leaderboardTitleText;
    sf::FloatRect leaderboardTitleTextRect;
    sf::Text leaderboardListText;
    sf::FloatRect leaderboardListTextRect;

    void initializeText();

    void handleEvents();

    void update();

    // Render
    void renderText();
    void render();
};


#endif //MINESWEEPER_CLONE_LEADERBOARDWINDOW_H
