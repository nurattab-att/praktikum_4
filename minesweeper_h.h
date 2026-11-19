#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <iostream>
using namespace std;

const int SIZE = 12;
const int MINES = 20;

enum Allocation { hidden, revealed, mine };

struct Tile {
    Allocation state;
    int neighbourMines;
};

extern Tile field[SIZE][SIZE];

// Funktionsprototypen
void initialize(int mineCount);
void display(bool debug = false);
int countMines(int x, int y);
bool input(int &remainingCovered);
bool revealedEmptyNeighbour(int x, int y);
bool checkNeighbours(int &remainingCovered);

#endif // MINESWEEPER_H
