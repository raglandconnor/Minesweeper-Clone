#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "WelcomeWindow.h"
#include "Board.h"

using namespace std;

int main() {
    fstream cFile("board_config.cfg");
    string line;
    getline(cFile, line);
    int cols = stoi(line);
    getline(cFile, line);
    int rows = stoi(line);
    getline(cFile, line);
    int mineCount = stoi(line);

    WelcomeWindow welcomeWindow(cols, rows);
    welcomeWindow.run();

    if (!welcomeWindow.closed) {
        Board boardWindow(cols, rows, mineCount, welcomeWindow.nameInputString);
        boardWindow.run();
    }

//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Red);
//
//    while(window.isOpen()) {
//        sf::Event event;
//        while(window.pollEvent(event)) {
//            if(event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//    return 0;
}