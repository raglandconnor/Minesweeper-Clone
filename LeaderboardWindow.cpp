//
// Created by Connor Ragland on 12/27/23.
//

#include "LeaderboardWindow.h"

LeaderboardWindow::LeaderboardWindow(int cols, int rows, int newIdx) : leaderboardWindow(sf::VideoMode((cols * 16), (rows * 16) + 50), "Leaderboard", sf::Style::Close) {
    this->cols = cols;
    this->rows = rows;
    this->newIdx = newIdx;
    initializeText();
}

void LeaderboardWindow::run() {
    while(leaderboardWindow.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void LeaderboardWindow::initializeText() {
    font.loadFromFile("font.ttf");
    if (!font.loadFromFile("font.ttf")) {
        std::cout << "Font not loaded" << std::endl;
    }

    leaderboardTitleText.setString("LEADERBOARD");
    leaderboardTitleText.setFont(font);
    leaderboardTitleText.setCharacterSize(20);
    leaderboardTitleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    leaderboardTitleText.setFillColor(sf::Color::White);

    leaderboardTitleTextRect = leaderboardTitleText.getLocalBounds();
    leaderboardTitleText.setOrigin(leaderboardTitleTextRect.left = leaderboardTitleTextRect.width / 2.0f, leaderboardTitleTextRect.top = leaderboardTitleTextRect.height / 2.0f);
    leaderboardTitleText.setPosition((cols * 16)/2.0f, ((rows * 16) + 50) /2.0f - 120);

    leaderboardListText.setFont(font);
    leaderboardListText.setCharacterSize(18);
    leaderboardListText.setStyle(sf::Text::Bold);
    leaderboardListText.setFillColor(sf::Color::White);

    leaderboardListTextRect = leaderboardListText.getLocalBounds();
    leaderboardListText.setOrigin(leaderboardListTextRect.left = (leaderboardListTextRect.width / 2.0f), leaderboardListTextRect.top = (leaderboardListTextRect.height / 2.0f));
    leaderboardListText.setPosition((cols * 16)/2.0f, ((rows * 16) + 50) /2.0f + 20);

    std::vector<std::string> names;
    std::vector<std::string> times;

    std::fstream file("leaderboard.txt");
    if (file.is_open()) {
        for (int i = 0; i < 5; i++) {
            std::string str1;
            getline(file, str1, ',');
            times.push_back(str1);
            std::string str2;
            getline(file, str2);
            names.push_back(str2);
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }

    std::string result;
    for (int j = 0; j < 5; j++) {
        std::string stringNum = std::to_string(j + 1);

        result += stringNum + ". \t" + times[j] + "\t" + names[j];
        if (j == newIdx) {
            result += '*';
        }
        if (j != 4) {
            result += "\n\n";
        }
    }
    leaderboardListText.setString(result);
}

void LeaderboardWindow::handleEvents() {
    sf::Event event;
    while (leaderboardWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            leaderboardWindow.close();
        }
    }
}

void LeaderboardWindow::renderText() {
    leaderboardWindow.draw(leaderboardTitleText);
    leaderboardWindow.draw(leaderboardListText);
}

void LeaderboardWindow::update() {
    leaderboardListTextRect = leaderboardListText.getLocalBounds();
    leaderboardListText.setOrigin(leaderboardListTextRect.left = (leaderboardListTextRect.width / 2.0f), leaderboardListTextRect.top = (leaderboardListTextRect.height / 2.0f));
}

void LeaderboardWindow::render() {
    leaderboardWindow.clear(sf::Color::Blue);

    renderText();

    leaderboardWindow.display();
}