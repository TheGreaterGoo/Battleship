/**
 * This program is a console IO version of battleship. The rules
 * are the same as normal battleship, except there are only
 * battleships of length 1, 2, 3, and 4. The board is 5x5.
 */

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "globals.h"
using namespace std;

// Method declarations.
void turn(int player);
bool markHits(int (*hits)[5], string coords, int x, int y);
bool gameOverCheck();
void printBoard(int ships[5][5]);
void printReferenceBoard();

// 2D arrays to represent player boards and hits.
int p1Ships[5][5], p2Ships[5][5], p1Hits[5][5], p2Hits[5][5];

int main() { 
    // Setup player boards with no ships.
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            p1Ships[row][col] = 0;
            p2Ships[row][col] = 0;
            p1Hits[row][col] = 0;
            p2Hits[row][col] = 0;
        }
    }
    
    // Set up the game.
    setup();

    // Play the game.
    bool n = false;
    bool gameOver = false;
    while (!gameOver) {
        // Alternate between player 1 and player 2 turns.
        turn(n + 1);
        n = !n;

        gameOver = gameOverCheck();
    }

    string winner = "PLAYER 2";
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            if (p1Ships[row][col] != 0) {
                winner = "PLAYER 1";
            }
        }
    }
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"  << "GAME OVER!!!";
    cout << "The winner is: " + winner;
}

/**
 * Plays out a turn of a specified player.
 * 
 * @param player The player whose turn it is.
 */
void turn(int player) {
    string playerStr = (player == 1) ? "ONE" : "TWO";

    int (*hits)[5], (*ships)[5];
    hits = (player == 1) ? p1Hits : p2Hits;
    ships = (player == 1) ? p1Ships : p2Ships;

    cout << "PLAYER " << playerStr << ", it is your turn!\n " << endl;
    cout << "Here is your board:\n " << endl;
    printBoard(ships);
    cout << "\nHere is your opponent's board:" << endl;
    cout << "Ones indicate hits and nines indicate misses\n" << endl;
    printBoard(hits);

    cout << endl;
    printReferenceBoard();

    bool miss = false;
    string coords;
    while (!miss) {
        if (gameOverCheck()) break;
        cout << "----------------------------------------" << endl;
        cout << "[PLAYER " << playerStr << "] Place a hit in the format xy." << endl;
        cin >> coords;

        int x = coords[0] - '0';
        int y = coords[1] - '0';

        // Mark hits.
        bool successfulHit = markHits(hits, coords, x, y);
        while (!successfulHit) {
            cout << "\nThis coordinate has already been hit or is invalid.\n" << endl;
            cout << "----------------------------------------" << endl;
            cout << "[PLAYER " << playerStr << "] Place a hit in the format xy.\n" << endl;
            cin >> coords;

            x = coords[0] - '0';
            y = coords[1] - '0';

            // Mark hits.
            successfulHit = markHits(hits, coords, x, y);
        }

        (player == 1) ? ships = p2Ships : ships = p1Ships;
        if (hits[y][x] == 1 && ships[y][x] != 0) {
            ships[y][x] = 0;
            cout << "\nSUCCESFUL HIT!\n" << endl;
        } else {
            miss = true;
            cout << "\nMISS!\n" << endl;
            
            // Mark hits with a miss (9)
            hits[y][x] = 9;

            cout << "Switching players...";
            this_thread::sleep_for(chrono::seconds(2));
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        }
    } 
}

bool markHits(int (*hits)[5], string coords, int x, int y) {
    // Return false, already hit.
    if (x < 0 || x > 4 || y < 0 || y > 4 || hits[y][x] == 1) return false;
    
    // Register hit.
    hits[y][x] = 1;
    return true;
}

bool gameOverCheck() {
    bool p1ShipsExist, p2ShipsExist;
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            if (p1Ships[row][col] != 0) {
                p1ShipsExist = true;
            }
            if (p2Ships[row][col] != 0) {
                p2ShipsExist = true;
            }
            if (p1ShipsExist && p2ShipsExist) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Prints the battleship board.
 * 
 * @param ships The board to be printed
 */
void printBoard(int ships[5][5]) {
  for (int row = 0; row < 5; row++) {
    for (int col = 0; col < 5; col++) {
      cout << ships[row][col] << " ";
    }
    cout << "\n";
  }
}

// Prints a reference board for players to know the board locations.
void printReferenceBoard() {
  cout << "Here is a reference board:\n " << endl;
  cout << "(00) (10) (20) (30) (40)\n" << endl;
  cout << "(01) (11) (21) (31) (41)\n" << endl;
  cout << "(02) (12) (22) (32) (42)\n" << endl;
  cout << "(03) (13) (23) (33) (43)\n" << endl;
  cout << "(04) (14) (24) (34) (44)\n" << endl;
}

