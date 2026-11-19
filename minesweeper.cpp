#include "minesweeper_h.h".h"
#include <cstdlib>
#include <ctime>

Tile field[SIZE][SIZE];  // Definition des Spielfelds

// Funktionsimplementierungen:
void initialize(int mineCount) {
    srand(time(0));
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            field[i][j].state = hidden;
            field[i][j].neighbourMines = 0;
        }

    int placedMines = 0;
    while (placedMines < mineCount) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (field[x][y].state != mine) {
            field[x][y].state = mine;
            ++placedMines;
        }
    }

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            field[i][j].neighbourMines = countMines(i, j);
}

void display(bool debug) {
    cout << "   ";
    for (int i = 0; i < SIZE; ++i)
        cout << i << " ";
    cout << "\n";

    for (int i = 0; i < SIZE; ++i) {
        cout << i << " ";
        if (i < 10) cout << " ";
        for (int j = 0; j < SIZE; ++j) {
            if (debug) {
                if (field[i][j].state == mine)
                    cout << "* ";
                else
                    cout << field[i][j].neighbourMines << " ";
            } else {
                if (field[i][j].state == hidden)
                    cout << "# ";
                else if (field[i][j].state == mine)
                    cout << "# ";
                else
                    cout << field[i][j].neighbourMines << " ";
            }
        }
        cout << "\n";
    }
}

int countMines(int x, int y) {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE)
                if (field[nx][ny].state == mine)
                    ++count;
        }
    return count;
}

bool input(int &remainingCovered) {
    int x, y;
    cout << "Geben Sie die Koordinaten zum Aufdecken ein (x y): ";
    cin >> x >> y;

    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        cout << "Ungültige Koordinaten.\n";
        return true;
    }

    if (field[x][y].state == revealed) {
        cout << "Dieses Feld ist bereits aufgedeckt.\n";
        return true;
    }

    if (field[x][y].state == mine) {
        return false;
    }

    field[x][y].state = revealed;
    --remainingCovered;

    if (field[x][y].neighbourMines == 0)
        revealedEmptyNeighbour(x, y);

    return true;
}

bool revealedEmptyNeighbour(int x, int y) {
    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                if (field[nx][ny].state == hidden) {
                    field[nx][ny].state = revealed;
                }
            }
        }
    return true;
}

bool checkNeighbours(int &remainingCovered) {
    bool updated = false;
    for (int x = 0; x < SIZE; ++x)
        for (int y = 0; y < SIZE; ++y)
            if (field[x][y].state == revealed && field[x][y].neighbourMines == 0)
                updated |= revealedEmptyNeighbour(x, y);
    return updated;
}
