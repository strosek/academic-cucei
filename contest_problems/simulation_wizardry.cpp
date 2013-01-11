//  Copyright (c) 2012 Erick Daniel Corona <edcoronag@gmail.com>
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation
//  files (the "Software"), to deal in the Software without
//  restriction, including without limitation the rights to use,
//  copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following
//  conditions:
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.

// Solution to
// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=50

// #define DEBUG

#include <iostream>
#include <cstdlib>

#ifdef DEBUG
#include <iomanip>
#include <unistd.h>
#endif

using namespace std;

enum Direction_t {DIRECTION_RIGHT = 0, DIRECTION_UP, DIRECTION_LEFT, DIRECTION_DOWN};

typedef struct bumper {
    bumper() :
        value(0),
        cost(0)
    {}
    int value;
    int cost;
} Bumper_t;

int main(void) {
    int xSize, ySize;
    cin >> xSize >> ySize;
    int wallCost;
    cin >> wallCost;

    int** table = (int**)malloc(sizeof(int*) * ySize);
    for (int i = 0; i < ySize; ++i) {
        table[i] = (int*)malloc(sizeof(int) * xSize);
    }

    for (int i = 0; i < ySize; ++i) {
        for (int j = 0; j < xSize; ++j) {
            table[i][j] = -1;
        }
    }

    int nBumpers;
    cin >> nBumpers;

    Bumper_t* bumpers = (Bumper_t*)malloc(sizeof(Bumper_t) * nBumpers);

    int bumperX, bumperY, bumperValue, bumperCost;
    for (int bumperNo = 0; bumperNo < nBumpers; ++bumperNo) {
        cin >> bumperX >> bumperY >> bumperValue >> bumperCost;
        table[ySize - 1 - bumperY][bumperX] = bumperNo;
        bumpers[bumperNo].value = bumperValue;
        bumpers[bumperNo].cost = bumperCost;
    }

#ifdef DEBUG
    for (int i = 0; i < ySize; ++i) {
        for (int j = 0; j < xSize; ++j) {
            cout << setw(3) << table[i][j];
        }
        cout << endl;
    }
    
    for (int i = 0; i < nBumpers; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << bumpers[i].value << ' ';
        }
        cout << endl;
    }
#endif
    
    int ballX, ballY, direction, lifetime;
    int tableValue;
    int points, totalPoints = 0;
    while (cin >> ballX >> ballY >> direction >> lifetime) {
        ballY = ySize - 1 - ballY;
        points = 0;
        while (lifetime > 1) {
#ifdef DEBUG
            system("clear");
            cout << "postition: " << ballX << ',' << ySize - 1 - ballY << "\ndirection: " << direction << " lifetime: " << lifetime << " points: " << points  << endl << endl;
            for (int i = 0; i < ySize; ++i) {
                for (int j = 0; j < xSize; ++j) {
                    if (ballX == j && ballY == i) {
                        cout << '0';
                    }
                    else if (table[i][j] >= 0) {
                        cout << '+';
                    }
                    else {
                        cout << ' ';
                    }
                }
                cout << endl;
            }
            usleep(900000);
#endif
            switch (direction) {
                case DIRECTION_RIGHT :
                    ++ballX;
                    if (ballX > xSize - 1) {
                        lifetime -= wallCost;
                        direction = DIRECTION_DOWN;
                        --ballX;
                    }
                    else if ((tableValue = table[ballY][ballX]) >= 0) {
                        points += bumpers[tableValue].value;
                        lifetime -= bumpers[tableValue].cost;
                        direction = DIRECTION_DOWN;
                        --ballX;
                    }
                    break;
                case DIRECTION_UP :
                    --ballY;
                    if (ballY < 0 ) {
                        lifetime -= wallCost;
                        direction = DIRECTION_RIGHT;
                        ++ballY;
                    }
                    else if ((tableValue = table[ballY][ballX]) >= 0) {
                        points += bumpers[tableValue].value;
                        lifetime -= bumpers[tableValue].cost;
                        direction = DIRECTION_RIGHT;
                        ++ballY;
                    }
                    break;
                case DIRECTION_LEFT :
                    --ballX;
                    if (ballX < 0 ) {
                        lifetime -= wallCost;
                        direction = DIRECTION_UP;
                        ++ballX;
                    }
                    else if ((tableValue = table[ballY][ballX]) >= 0) {
                        points += bumpers[tableValue].value;
                        lifetime -= bumpers[tableValue].cost;
                        direction = DIRECTION_UP;
                        ++ballX;
                    }
                    break;
                case DIRECTION_DOWN :
                    ++ballY;
                    if (ballY >= ySize ) {
                        lifetime -= wallCost;
                        direction = DIRECTION_LEFT;
                        --ballY;
                    }
                    else if ((tableValue = table[ballY][ballX]) >= 0) {
                        points += bumpers[tableValue].value;
                        lifetime -= bumpers[tableValue].cost;
                        direction = DIRECTION_LEFT;
                        --ballY;
                    }
                    break;
                default :
                    cerr << "simulation_wizardry: bad direction" << endl;
                    break;
            }
            --lifetime;
        }
        cout << points << endl;
        totalPoints += points;
    }
    cout << totalPoints << endl;

    return EXIT_SUCCESS;
}

