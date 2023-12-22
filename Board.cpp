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
    paused_time = clock.getElapsedTime();

    initializeTiles();
    initializeSprites();
    calculateAdjacent();
}

void Board::run() {
    printCL();
    while (mainWindow.isOpen()) {
        handleEvents();
        update();
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

void Board::calculateAdjacent() {
/*
     * Code added to the array in this order:
     * [0, 1, 2]
     * [3, -, 4]
     * [5, 6, 7]
*/
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!boardVect[i][j].mine) {
                boardVect[i][j].numAdjacentMines = 0;
                if ((i - 1) >= 0 && (j - 1) >= 0) {  // 0
                    boardVect[i][j].adjacentTiles[0] = &boardVect[i-1][j-1];
                    if (boardVect[i-1][j-1].mine) {
                        boardVect[i][j].numAdjacentMines++;
                    }
                } else {
                    boardVect[i][j].adjacentTiles[0] = nullptr;
                }

                if ((i - 1) >= 0) {  // 1
                    boardVect[i][j].adjacentTiles[1] = &boardVect[i-1][j];
                    if (boardVect[i-1][j].mine) {
                        boardVect[i][j].numAdjacentMines++;
                    }
                } else {
                    boardVect[i][j].adjacentTiles[1] = nullptr;
                }

                if ((i - 1) >= 0 && (j + 1) < cols) {  // 2
                    boardVect[i][j].adjacentTiles[2] = &boardVect[i-1][j+1];
                    if (boardVect[i-1][j+1].mine) {
                        boardVect[i][j].numAdjacentMines++;
                    }
                } else {
                    boardVect[i][j].adjacentTiles[2] = nullptr;
                }

                if ((j - 1) >= 0) {  // 3
                    boardVect[i][j].adjacentTiles[3] = &boardVect[i][j-1];
                    if (boardVect[i][j-1].mine) {
                        boardVect[i][j].numAdjacentMines++;
                    }
                } else {
                    boardVect[i][j].adjacentTiles[3] = nullptr;
                }

                if ((j + 1) < cols) {  // 4
                    boardVect[i][j].adjacentTiles[4] = &boardVect[i][j+1];
                    if (boardVect[i][j+1].mine) {
                        boardVect[i][j].numAdjacentMines++;
                    }
                } else {
                    boardVect[i][j].adjacentTiles[4] = nullptr;
                }

                if ((i + 1) < rows && (j - 1) >= 0) {  // 5
                    boardVect[i][j].adjacentTiles[5] = &boardVect[i+1][j-1];
                    if (boardVect[i+1][j-1].mine) {
                        boardVect[i][j].numAdjacentMines++;
                    }
                } else {
                    boardVect[i][j].adjacentTiles[5] = nullptr;
                }

                if ((i + 1) < rows) {  // 6
                    boardVect[i][j].adjacentTiles[6] = &boardVect[i+1][j];
                    if (boardVect[i+1][j].mine) {
                        boardVect[i][j].numAdjacentMines++;
                    }
                } else {
                    boardVect[i][j].adjacentTiles[6] = nullptr;
                }

                if ((i + 1) < rows && (j + 1) < cols) {  // 7
                    boardVect[i][j].adjacentTiles[7] = &boardVect[i+1][j+1];
                    if (boardVect[i+1][j+1].mine) {
                        boardVect[i][j].numAdjacentMines++;
                    }
                } else {
                    boardVect[i][j].adjacentTiles[7] = nullptr;
                }
            }

        }
    }
    auto iter3 = boardVect.begin();
    for (; iter3 != boardVect.end(); ++iter3) {
        auto iter4 = iter3->begin();
        for (; iter4 != iter3->end(); ++iter4) {
            if (iter4->numAdjacentMines == 1) {
                iter4->numSprite.setTexture(num_1_texture);
            }
            if (iter4->numAdjacentMines == 2) {
                iter4->numSprite.setTexture(num_2_texture);
            }
            if (iter4->numAdjacentMines == 3) {
                iter4->numSprite.setTexture(num_3_texture);
            }
            if (iter4->numAdjacentMines == 4) {
                iter4->numSprite.setTexture(num_4_texture);
            }
            if (iter4->numAdjacentMines == 5) {
                iter4->numSprite.setTexture(num_5_texture);
            }
            if (iter4->numAdjacentMines == 6) {
                iter4->numSprite.setTexture(num_6_texture);
            }
            if (iter4->numAdjacentMines == 7) {
                iter4->numSprite.setTexture(num_7_texture);
            }
            if (iter4->numAdjacentMines == 8) {
                iter4->numSprite.setTexture(num_8_texture);
            }
        }
    }
}

void Board::revealRecursive(Tile *tile) {
    if (tile->isRevealed || tile->flag) {return;}
    if (tile->mine) {
        tile->tileSprite.setTexture(revealedTexture);
        tile->mineSprite.setTexture(mineTexture);
        tile->isRevealed = true;
        lose = true;
        paused = true;
        paused_time = paused_time + elapsed_time;
        return;
    }
    tile->tileSprite.setTexture(revealedTexture);
    tile->isRevealed = true;

    if (tile->numAdjacentMines == 0) {
        for (int i = 0; i < 8; i++) {
            if (tile->adjacentTiles[i] != nullptr) {
                revealRecursive(tile->adjacentTiles[i]);
            }
        }
    }
}

void Board::pauseGame() {
    playPauseSprite.setTexture(playTexture);
    paused_time += clock.getElapsedTime();
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

                // Debug button
                if (debugSprite.getGlobalBounds().contains(mainWindow.mapPixelToCoords(mouse)) && !lose && !win && !paused) {
                    showMines = !showMines;
                }
                // Play pause button
                if (playPauseSprite.getGlobalBounds().contains(mainWindow.mapPixelToCoords(mouse)) && !lose && !win) {
                    paused = !paused;
                    if (paused) {
                        revealTiles = true;
                        pauseGame();

                    } else {
                        playPauseSprite.setTexture(pauseTexture);
                        clock.restart();
                        revealTiles = false;
                    }

                }

                // Tiles
                auto iter1 = boardVect.begin();
                for (; iter1 != boardVect.end(); ++iter1) {
                    auto iter2 = iter1->begin();
                    for (; iter2 != iter1->end(); ++iter2) {
                        if (iter2->tileSprite.getGlobalBounds().contains(mainWindow.mapPixelToCoords(mouse)) && !lose && !win && !paused) {
                            revealRecursive(&(*iter2));
                        }
                    }
                }
            }
            if (event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2i mouse;
                mouse = sf::Mouse::getPosition(mainWindow);
                std::cout << "R mouse: (" << mouse.x << ", " << mouse.y << ')' << std::endl;

                // Place flag
                auto iter1 = boardVect.begin();
                for (; iter1 != boardVect.end(); ++iter1) {
                    auto iter2 = iter1->begin();
                    for (; iter2 != iter1->end(); ++iter2) {
                        if (iter2->tileSprite.getGlobalBounds().contains(mainWindow.mapPixelToCoords(mouse)) && !lose && !win && !paused) {
                            if (!iter2->isRevealed) {
                                iter2->flag = !iter2->flag;
                            }
                            if (iter2->flag) {
                                if (!iter2->isRevealed) {
                                    flagsPlaced++;
                                }
                            } else {
                                if (!iter2->isRevealed) {
                                    flagsPlaced--;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Board::updateCounter() {
    /*
     * Order of the counter sprites:
     * [1, 2, 3]
     */
    int counter = 0;
    bool isNeg = false;
    counter = mineCount - flagsPlaced;
    if (counter < 0) {
        isNeg = true;
        counter *= -1;
    }
    int firstDigit = counter / 10;
    int secondDigit = counter % 10;
    if (win) {
        firstDigit = 0;
        secondDigit = 0;
    }

    // Set texture rects
    if (isNeg) {
        counter_1_sprite.setTextureRect(sf::IntRect(210, 0, 21, 32));
    } else {
        counter_1_sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
    }
    // Update digits
    for (int i = 0; i < 10; i++) {
        if (firstDigit == i) {
            counter_2_sprite.setTextureRect(sf::IntRect(21 * i, 0, 21, 32));
        }
        if (secondDigit == i) {
            counter_3_sprite.setTextureRect(sf::IntRect(21 * i, 0, 21, 32));
        }
    }
}

void Board::updateTimer() {
    /*
     * Timer layout:
     * [1 2 | 3 4]
     */
    int time;

    if (!paused) {
        elapsed_time = paused_time + clock.getElapsedTime();
        time = elapsed_time.asSeconds();
    }
    if (paused) {
        time = paused_time.asSeconds();
    }

    int minutes = time / 60;
    int seconds = time % 60;

    int minutes0 = minutes / 10 % 10; //minutes index 0
    int minutes1 = minutes % 10; // minutes index 1
    int seconds0 = seconds / 10 % 10; // seconds index 0
    int seconds1 = seconds % 10; // seconds index 1

    for (int i = 0; i < 10; i++) {
        if (minutes0 == i) {
            timer_1_sprite.setTextureRect(sf::IntRect(21 * i, 0, 21, 32));
        }
        if (minutes1 == i) {
            timer_2_sprite.setTextureRect(sf::IntRect(21 * i, 0, 21, 32));
        }
        if (seconds0 == i) {
            timer_3_sprite.setTextureRect(sf::IntRect(21 * i, 0, 21, 32));
        }
        if (seconds1 == i) {
            timer_4_sprite.setTextureRect(sf::IntRect(21 * i, 0, 21, 32));
        }
    }
}

void Board::update() {
    updateCounter();
    updateTimer();
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

void Board::renderNumAdj() {
    if (win || lose || !paused) {
        auto iter7 = boardVect.begin();
        for (; iter7 != boardVect.end(); ++iter7) {
            auto iter8 = iter7->begin();
            for (; iter8 != iter7->end(); ++iter8) {
                if (iter8->isRevealed) {
                    mainWindow.draw(iter8->numSprite);
                }
            }
        }
    }
}

void Board::renderFlags() {
    if (!paused) {
        auto iter1 = boardVect.begin();
        for (; iter1 != boardVect.end(); ++iter1) {
            auto iter2 = iter1->begin();
            for (; iter2 != iter1->end(); ++iter2) {
                if (iter2->flag) {
                    mainWindow.draw(iter2->flagSprite);
                }
            }
        }
    }
}

void Board::renderUI() {
    mainWindow.draw(debugSprite);
    mainWindow.draw(faceSprite);
    mainWindow.draw(leaderboardSprite);
    mainWindow.draw(playPauseSprite);

    // Draw counter
    mainWindow.draw(counter_1_sprite);
    mainWindow.draw(counter_2_sprite);
    mainWindow.draw(counter_3_sprite);

    // Draw timer
    mainWindow.draw(timer_1_sprite);
    mainWindow.draw(timer_2_sprite);
    mainWindow.draw(timer_3_sprite);
    mainWindow.draw(timer_4_sprite);
}

void Board::renderDebug() {
    if (showMines) {
        auto iter5 = boardVect.begin();
        for (; iter5 != boardVect.end(); ++iter5) {
            auto iter6 = iter5->begin();
            for (; iter6 != iter5->end(); ++iter6) {
                if (iter6->mine) {
                    mainWindow.draw(iter6->mineSprite);
                }
            }
        }
    }
}

void Board::render() {
    mainWindow.clear(sf::Color::White);

    renderTiles();
    renderNumAdj();
    renderFlags();
    renderUI();
    renderDebug();

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