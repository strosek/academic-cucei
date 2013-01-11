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

// Solution to http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=38

#include <iostream>
#include <cstdlib>

using namespace std;

enum Order_t {ORDER_BCG = 0, ORDER_BGC, ORDER_GBC, ORDER_GCB, ORDER_CBG, ORDER_CGB};

int main(void) {
	int bin1Brown, bin1Green, bin1Clear;
    int bin2Brown, bin2Green, bin2Clear;
    int bin3Brown, bin3Green, bin3Clear;
	int moves, minMoves;
	Order_t arrangement;
    
    char readChar;
    bool isCinGood = true;
	while (isCinGood) {
		cin >> bin1Brown >> bin1Green >> bin1Clear >>
			   bin2Brown >> bin2Green >> bin2Clear >>
			   bin3Brown >> bin3Green >> bin3Clear;
        readChar = cin.get();
        while (!isdigit(readChar) && cin.good()) {
            readChar = cin.get();
        }
        cin.unget();
        isCinGood = cin.good();

        // BCG
        moves = bin2Brown + bin3Brown + bin1Clear + bin3Clear + bin1Green + bin2Green;
        minMoves = moves;
        arrangement = ORDER_BCG;
        // BGC
        moves = bin2Brown + bin3Brown + bin1Green + bin3Green + bin1Clear + bin2Clear;
        if (moves < minMoves) {
            minMoves = moves;
            arrangement = ORDER_BGC;
        }
        // GBC
        moves = bin2Green + bin3Green + bin1Brown + bin3Brown + bin1Clear + bin2Clear;
        if (moves < minMoves) {
            minMoves = moves;
            arrangement = ORDER_GBC;
        }
        // GCB
        moves = bin2Green + bin3Green + bin1Clear + bin3Clear + bin1Brown + bin2Brown;
        if (moves < minMoves) {
            minMoves = moves;
            arrangement = ORDER_GCB;
        }
        // CBG
        moves = bin2Clear + bin3Clear + bin1Brown + bin3Brown + bin1Green + bin2Green;
        if (moves < minMoves) {
            minMoves = moves;
            arrangement = ORDER_CBG;
        }
        // CGB
        moves = bin2Clear + bin3Clear + bin1Green + bin3Green + bin1Brown + bin2Brown;
        if (moves < minMoves) {
            minMoves = moves;
            arrangement = ORDER_CGB;
        }

        switch (arrangement) {
            case ORDER_BCG :
                cout << "BCG";
                break;
            case ORDER_BGC :
                cout << "BGC";
                break;
            case ORDER_GBC :
                cout << "GBC";
                break;
            case ORDER_GCB :
                cout << "GCB";
                break;
            case ORDER_CBG :
                cout << "CBG";
                break;
            case ORDER_CGB :
                cout << "CGB";
                break;
        }
        cout << ' ' << minMoves << endl;
	}

    return EXIT_SUCCESS;
}
