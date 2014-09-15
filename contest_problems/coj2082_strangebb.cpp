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


// This file implements solution to problem 2082 (Strange Billboard) from
// Caribbean Online Judge.


#include <cstdlib>
#include <iostream>
#include <utility>

using namespace std;


class StrangeBillboard
{
public:
  StrangeBillboard() :
    m_board(NULL),
    m_sizeX(0UL),
    m_sizeY(0UL),
    m_blackTiles(0UL),
    m_taps(0UL)
  {
  }

  void solve()
  {
    while (true)
    {
      cin >> m_sizeX;
      cin >> m_sizeY;
      if (m_sizeX < 1 && m_sizeY < 1)
      {
        goto end;
      }

      m_blackTiles = 0UL;
      /////////////////////////////////////////////////////////////////////////
      // Allocate and load matrix.
      /////////////////////////////////////////////////////////////////////////
      m_board = new bool*[m_sizeY];
      for (size_t i = 0; i < m_sizeY; ++i)
      {
        m_board[i] = new bool[m_sizeX];
      }

      char tile = ' ';
      for (size_t i = 0; i < m_sizeY; ++i)
      {
        for (size_t j = 0; j < m_sizeX; ++j)
        {
          // X is white tile, . is white tile.
          cin >> tile;
          if (tile == '.')
          {
            m_board[i][j] = false;
          }
          else
          {
            m_board[i][j] = true;
            ++m_blackTiles;
          }
        }
      }

      /////////////////////////////////////////////////////////////////////////
      // Count minimal taps.
      /////////////////////////////////////////////////////////////////////////
      bool hasSolution = true;
      size_t taps = 0UL;
      while (m_blackTiles > 0 && hasSolution)
      {
        for (size_t i = 0UL; i < m_sizeY; ++i)
        {
          for (size_t j = 0UL; j < m_sizeX; ++j)
          {
            if (getTapQuality(j, i) > 0)
            {
              tap(j, i);
            }
          }
        }
      }


      /////////////////////////////////////////////////////////////////////////
      // Show results.
      /////////////////////////////////////////////////////////////////////////
      if (hasSolution)
      {
        cout << "You have to tap " << taps << " tiles." << endl;
      }
      else
      {
        cout << "Damaged billboard." << endl;
      }


      /////////////////////////////////////////////////////////////////////////
      // Clean memory.
      /////////////////////////////////////////////////////////////////////////
      for (size_t i = 0; i < m_sizeY; ++i)
      {
        delete[] m_board[i];
      }
      delete[] m_board;
      m_board = NULL;
    }

end:
    return;
  }

private:
  void tap(size_t x, size_t y)
  {
    ++m_taps;
    m_board[x][y] = !m_board[x][y];
    if (isInRange(x + 1, y))
    {
      (m_board[x + 1][y] = !m_board[x + 1][y]) ? ++m_blackTiles :
                                                 --m_blackTiles;
    }
    if (isInRange(x - 1, y))
    {
      (m_board[x - 1][y] = !m_board[x - 1][y]) ? ++m_blackTiles :
                                                 --m_blackTiles;
    }
    if (isInRange(x, y + 1))
    {
      (m_board[x][y + 1] = !m_board[x][y + 1]) ? ++m_blackTiles :
                                                 --m_blackTiles;
    }
    if (isInRange(x, y - 1))
    {
      (m_board[x][y - 1] = !m_board[x][y - 1]) ? ++m_blackTiles :
                                                 --m_blackTiles;
    }
  }

  bool isInRange(size_t x, size_t y)
  {
    return (x > 0 && x < m_sizeX && y > 0 && y < m_sizeY);
  }

  int  getTapQuality(size_t x, size_t y)
  {
    int quality = 0;

    if (isInRange(x + 1, y))
    {
      if (m_board[x + 1][y] == true)
      {
        ++quality;
      }
      else
      {
        --quality;
      }
    }
    if (isInRange(x - 1, y))
    {
      if (m_board[x - 1][y] == true)
      {
        ++quality;
      }
      else
      {
        --quality;
      }
    }
    if (isInRange(x, y + 1))
    {
      if (m_board[x][y + 1] == true)
      {
        ++quality;
      }
      else
      {
        --quality;
      }
    }
    if (isInRange(x, y - 1))
    {
      if (m_board[x][y - 1] == true)
      {
        ++quality;
      }
      else
      {
        --quality;
      }
    }

    return quality;
  }

  bool **m_board;
  size_t m_sizeX;
  size_t m_sizeY;
  size_t m_blackTiles;
  size_t m_taps;
};


int main()
{
  StrangeBillboard board;
  board.solve();

  return EXIT_SUCCESS;
}

