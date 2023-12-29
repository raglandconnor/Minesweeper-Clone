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
}