//
// Created by Connor Ragland on 12/18/23.
//

#include "WelcomeWindow.h"

WelcomeWindow::WelcomeWindow(int cols, int rows) : welcomeWindow(sf::VideoMode(cols * 32, (rows * 32) + 100), "Minesweeper", sf::Style::Close) {
    initializeText();
    name_count = 0;
    closed = false;
}

void WelcomeWindow::run() {
    while (welcomeWindow.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void WelcomeWindow::initializeText() {
    font.loadFromFile("font.ttf");
    if (!font.loadFromFile("font.ttf")) {
        std::cout << "Font not loaded" << std::endl;
    }

    welcomeText.setString("WELCOME TO MINESWEEPER!");
    welcomeText.setFont(font);
    welcomeText.setCharacterSize(24);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setFillColor(sf::Color::White);

    welcomeTextRect = welcomeText.getLocalBounds();
    welcomeText.setOrigin(welcomeTextRect.left = welcomeTextRect.width / 2.0f, welcomeTextRect.top = welcomeTextRect.height / 2.0f);
    welcomeText.setPosition(sf::Vector2f(800 / 2.0f, 600 / 2.0f - 150));

    enterName.setString("Enter your name:");
    enterName.setFont(font);
    enterName.setCharacterSize(20);
    enterName.setStyle(sf::Text::Bold);
    enterName.setFillColor(sf::Color::White);

    enterNameRect = enterName.getLocalBounds();
    enterName.setOrigin(enterNameRect.left = enterNameRect.width / 2.0f, enterNameRect.top = enterNameRect.height / 2.0f);
    enterName.setPosition(800 / 2.0f, 600 / 2.0f - 75);

    nameInput.setString(nameInputString + '|');
    nameInput.setFont(font);
    nameInput.setCharacterSize(18);
    nameInput.setStyle(sf::Text::Bold);
    nameInput.setFillColor(sf::Color::Yellow);

    nameInput.setPosition(800 / 2.0f, 600 / 2.0f - 45);
}

void WelcomeWindow::handleEvents() {
    sf::Event event;
    while(welcomeWindow.pollEvent(event)) {  // User presses X
        if (event.type == sf::Event::Closed) {
            closed = true;
            welcomeWindow.close();
        }

        if (event.type == sf::Event::KeyPressed) {  // User presses Enter
            if (event.key.code == sf::Keyboard::Enter) {
                if (name_count > 0) {
                    welcomeWindow.close();
                }
            }
        }

        if (event.type == sf::Event::TextEntered) {  // User inputs name
            if (event.text.unicode == '\b') {
                if (name_count > 0) {
                    nameInputString.erase(nameInputString.size() - 1, 1);
                    nameInput.setString(nameInputString + '|');
                    name_count = name_count - 1;
                } else {
                    name_count = 0;
                }
            } else {
                if (isalpha((char)event.text.unicode)) {
                    if (name_count < 1) {
                        nameInputString += toupper((char)event.text.unicode);
                        nameInput.setString(nameInputString + '|');
                    } else  {
                        if (name_count < 10) {
                            nameInputString += tolower((char)event.text.unicode);
                            nameInput.setString(nameInputString + '|');
                        } else {
                            name_count = 9;
                        }
                    }
                    name_count++;
                }
            }
        }
    }
}

void WelcomeWindow::update() {
    sf::FloatRect nameInputRect = nameInput.getLocalBounds();
    nameInput.setOrigin(nameInputRect.left = nameInputRect.width / 2.0f, nameInputRect.top = nameInputRect.height / 2.0f);
}

void WelcomeWindow::render() {
    welcomeWindow.clear(sf::Color::Blue);

    welcomeWindow.draw(welcomeText);
    welcomeWindow.draw(enterName);
    welcomeWindow.draw(nameInput);

    welcomeWindow.display();
}