#include "minesweeper_h.h"

int main() {
    int remainingCovered = SIZE * SIZE - MINES;

    initialize(MINES);
    display(false);



    bool running = true;
    while (running && remainingCovered > 0) {
        cout << "\nVerbleibende verdeckte Felder: " << remainingCovered << "\n";
        running = input(remainingCovered);
        while (checkNeighbours(remainingCovered));
        display(false);
    }

    if (!running) {
        cout << "\n**** BOOOOM ****\nLeider verloren.\n";
        display(true);
    } else {
        cout << "Herzlichen Glückwunsch! Sie haben gewonnen!\n";
    }

    return 0;
}

