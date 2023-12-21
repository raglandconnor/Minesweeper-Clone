//
// Created by Connor Ragland on 12/20/23.
//

#include "Board.h"

Board::Board(int cols, int rows, int mineCount, std::string username) : mainWindow(sf::VideoMode(cols * 32, (rows * 32) + 100), "Main Window") {
    this->cols = cols;
    this->rows = rows;
    this->mineCount = mineCount;
    this->username = username;

    newScoreIdx = 99;
    minesPlaced = 0;
    flagsPlaced = 0;
    win = false;
    paused = false;
//    paused_time = clock.getElapsedTime();

    initializeTiles();
    initializeSprites();
//    calculateAdjacent();
}

void Board::run() {
    printCL();
    while (mainWindow.isOpen()) {
        handleEvents();
//        update();
        render();
    }
}

void Board::initializeSprites() {
    faceSprite.setTexture(happyFaceTexture);
    faceSprite.setPosition((cols / 2.0 * 32) - 32, 32 * (rows + 0.5));

    debugSprite.setTexture(debugTexture);
    debugSprite.setPosition((cols * 32) - 304, 32 * (rows + 0.5));

    playPauseSprite.setTexture(pauseTexture);
    playPauseSprite.setPosition((cols * 32) - 240, 32 * (rows + 0.5));

    leaderboardSprite.setTexture(leaderboardTexture);
    leaderboardSprite.setPosition((cols * 32) - 176, 32 * (rows + 0.5));

    counter_1_sprite.setTexture(digitsTexture);
    counter_2_sprite.setTexture(digitsTexture);
    counter_3_sprite.setTexture(digitsTexture);
    counter_1_sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
    counter_2_sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
    counter_3_sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
    counter_1_sprite.setPosition(33, 32 * (rows + 0.5) + 16);
    counter_2_sprite.setPosition(54, 32 * (rows + 0.5) + 16);
    counter_3_sprite.setPosition(75, 32 * (rows + 0.5) + 16);

    timer_1_sprite.setTexture(digitsTexture);
    timer_2_sprite.setTexture(digitsTexture);
    timer_3_sprite.setTexture(digitsTexture);
    timer_4_sprite.setTexture(digitsTexture);
    timer_1_sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
    timer_2_sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
    timer_3_sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
    timer_4_sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
    timer_1_sprite.setPosition((cols * 32) - 97, 32 * (rows + 0.5) + 16);
    timer_2_sprite.setPosition((cols * 32) - 76, 32 * (rows + 0.5) + 16);
    timer_3_sprite.setPosition((cols * 32) - 54, 32 * (rows + 0.5) + 16);
    timer_4_sprite.setPosition((cols * 32) - 33, 32 * (rows + 0.5) + 16);
}

void Board::setMines() {
    std::srand(static_cast<unsigned>(std::time(0)));

    while (minesPlaced < mineCount) {
        unsigned int y = (std::rand() % rows);
        unsigned int x = (std::rand() % cols);

        if (!boardVect[y][x].mine) {
            boardVect[y][x].mine = true;
            minesPlaced++;
        }
    }
}

void Board::initializeTiles() {
    boardVect.resize(rows);

    for (int i = 0; i < rows; i++) {
        vector<Tile> temp;
        temp.resize(cols);

        for (int j = 0; j < cols; j++) {
            Tile tileObject;
            // Initialize tile object
            tileObject.setPos(i, j, cols, rows);
            tileObject.tileSprite.setTexture(hiddenTexture);
            tileObject.isRevealed = false;
            tileObject.flagSprite.setTexture(flagTexture);
            tileObject.flag = false;
            tileObject.mineSprite.setTexture(mineTexture);
            tileObject.allRevealedSprite.setTexture(revealedTexture);
            temp[j] = tileObject;
        }
        boardVect[i] = temp;
    }
    setMines();
}

void Board::handleEvents() {
    sf::Event event;
    while(mainWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            boardVect.clear();
            mainWindow.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mouse;
                mouse = sf::Mouse::getPosition(mainWindow);
                std::cout << "L mouse: (" << mouse.x << ", " << mouse.y << ')' << std::endl;

                auto iter1 = boardVect.begin();
                for (; iter1 != boardVect.end(); ++iter1) {
                    auto iter2 = iter1->begin();
                    for (; iter2 != iter1->end(); ++iter2) {
                        if (iter2->tileSprite.getGlobalBounds().contains(mainWindow.mapPixelToCoords(mouse)) && !lose && !win && !paused) {
                            iter2->isRevealed = true;
                            iter2->tileSprite.setTexture(revealedTexture);
                            // TODO: implement recursive reveal function.
                        }
                    }
                }
            }
        }
    }
}

void Board::renderTiles() {
    if (!revealTiles) {
        auto iter1 = boardVect.begin();
        for (; iter1 != boardVect.end(); ++iter1) {
            auto iter2 = iter1->begin();
            for (; iter2 != iter1->end(); ++iter2) {
                mainWindow.draw(iter2->tileSprite);
                if (iter2->isRevealed && iter2->mine) {
                    mainWindow.draw(iter2->mineSprite);
                }
            }
        }
    }
    else {
        auto iter1 = boardVect.begin();
        for (; iter1 != boardVect.end(); ++iter1) {
            auto iter2 = iter1->begin();
            for (; iter2 != iter1->end(); ++iter2) {
                mainWindow.draw(iter2->allRevealedSprite);
            }
        }
    }
}

void Board::render() {
    mainWindow.clear(sf::Color::White);

    renderTiles();

    mainWindow.display();
}

void Board::printCL() {  // For debugging
    for (int i = 0; i < rows; i++) {
        std::cout << '[';
        for (int j = 0; j < cols; j++) {
            std::cout << boardVect[i][j].mine;
            if (j != cols-1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
}