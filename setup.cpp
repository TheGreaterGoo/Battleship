/**
 * Setup handles the beginning of the game when the board needs
 * to be setup. It handles invalid input, such as illogical entries
 * for battleships.
 */

#include <iostream>
#include <string>
#include "globals.h"

using namespace std;

bool isNumeric(string str) {
  for (int i = 0; i < str.length(); i++) {
    if (isdigit(str[i]) == false) {
      return false;
    }
  }
  return true;
}

void setupShip(int num, int ships[5][5], string player) {
  int x1, y1, x2, y2, orientation;
  string coords;
  bool valid = false;
  do {
    cout << "\n[PLAYER " + player + "] Place the " 
    + to_string(num) + "-long ship in the format x1y1x2y2:\n " << endl;
    cin >> coords;

    // Convert input to integers.
    x1 = coords[0] - '0';
    y1 = coords[1] - '0';
    x2 = coords[2] - '0';
    y2 = coords[3] - '0';

    // Check for existing ships that might be in the way.
    orientation = (x1 == x2) ? 1 : 0;
    switch(orientation) {
      // Horizontal ship, check vertically.
      case 0:
        if (x1 > x2) {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }
        for (int i = x1; i <= x2; i++) {
            valid = (ships[y1][i] != 0) ? false : true;
            if (!valid) continue;
        }

      // Vertical ship, check horizontally.
      case 1:
        if (y1 > y2) {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }
        for (int i = y1; i <= y2; i++) {
            valid = (ships[i][x1] != 0) ? false : true;
            if (!valid) continue;
        }

    }


  }  while (!(coords.length() == 4 && isNumeric(coords) && valid && x1 < 5 && y1 < 5 && 
  x2 < 5 && y2 < 5 && ((abs(x2 - x1) == num - 1 && y1 == y2) || (abs(y2 - y1) == num - 1 && x1 == x2))));

  (x1 == x2) ? orientation = 1 : orientation = 0;
  switch(orientation) {
    // horizontal
    case 0:
        for (int i = x1; i <= x2; i++) {
            ships[y1][i] = num;
        }

    // vertical
    case 1:
        for (int i = y1; i <= y2; i++) {
            ships[i][x1] = num;
        }

  }

  cout << "\n";
  printBoard(ships);
}

void setup() {
    // PLAYER ONE
    printReferenceBoard();

    cout << "----------------------------------------" << endl;
    cout << "\nPLAYER ONE, place your ships!\n " << endl;

    setupShip(4, p1Ships, "ONE");
    setupShip(3, p1Ships, "ONE");
    setupShip(2, p1Ships, "ONE");
    setupShip(1, p1Ships, "ONE");
    cout << "----------------------------------------" << endl;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    // PLAYER TWO
    printReferenceBoard();

    cout << "----------------------------------------" << endl;
    cout << "\nPLAYER TWO, place your ships!\n " << endl;

    setupShip(4, p2Ships, "TWO");
    setupShip(3, p2Ships, "TWO");
    setupShip(2, p2Ships, "TWO");
    setupShip(1, p2Ships, "TWO");
    cout << "----------------------------------------" << endl;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}