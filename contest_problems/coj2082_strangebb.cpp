//  Copyright (c) 2014 Erick Daniel Corona <edcoronag@gmail.com>
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


#include <iostream>
#include <cstdlib>

using namespace std;


int main()
{
  size_t sizeX = 1UL;
  size_t sizeY = 1UL;
  size_t i = 0UL;
  size_t j = 0UL;
  char tile = 'A';
  bool isPossible = true;
  size_t taps = 0UL;
  int **board = NULL;

  while (sizeX > 0 && sizeY > 0)
  {
    cin >> sizeX;
    cin >> sizeY;
    if (sizeX < 1 && sizeY < 1)
    {
      goto end;
    }

    taps = 0;

    //////////////////////////////////////////////////////////////////////////
    // Allocate and load matrix.
    //////////////////////////////////////////////////////////////////////////
    board = new int*[sizeY];
    for (i = 0; i < sizeY; ++i)
    {
      board[i] = new int[sizeX];
    }

    for (i = 0; i < sizeY; ++i)
    {
      for (j = 0; j < sizeX; ++j)
      {
        // X is white tile, . is white tile.
        cin >> tile;
        if (tile == '.')
        {
          board[i][j] = 0;
        }
        else
        {
          board[i][j] = 1;
        }
      }
    }

    //////////////////////////////////////////////////////////////////////////
    // Count minimal taps.
    //////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////
    // Show results.
    //////////////////////////////////////////////////////////////////////////
    if (isPossible)
    {
      cout << "You have to tap " << taps << " tiles." << endl;
    }
    else
    {
      cout << "Damaged billboard." << endl;
    }


    //////////////////////////////////////////////////////////////////////////
    // Clean memory.
    //////////////////////////////////////////////////////////////////////////
    for (i = 0; i < sizeY; ++i)
    {
      delete[] board[i];
    }
    delete[] board;
    board = NULL;
  }

end:
  return EXIT_SUCCESS;
}

