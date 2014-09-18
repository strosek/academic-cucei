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
#include <climits>
#include <utility>

using namespace std;


class StrangeBillboard
{
public:
  StrangeBillboard() :
    m_board(NULL),
    m_sizeX(0),
    m_sizeY(0),
    m_blackTiles(0UL),
    m_taps(0UL)
  {
  }

  void solve()
  {
    while (true)
    {
      cin >> m_sizeY;
      cin >> m_sizeX;
      if (m_sizeX < 1 && m_sizeY < 1)
      {
        goto end;
      }

      m_blackTiles = 0UL;
      /////////////////////////////////////////////////////////////////////////
      // Allocate and load matrix.
      /////////////////////////////////////////////////////////////////////////
      m_board = new bool*[m_sizeY];
      for (int i = 0; i < m_sizeY; ++i)
      {
        m_board[i] = new bool[m_sizeX];
      }

      char tile = ' ';
      for (int i = 0; i < m_sizeY; ++i)
      {
        for (int j = 0; j < m_sizeX; ++j)
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
      bool hasMoves = true;
      size_t minimumBlackTiles = ULONG_MAX;
      size_t tapsNoImprove = 0UL;
      m_taps = 0UL;
      while (m_blackTiles > 0 && hasSolution && hasMoves)
      {
        hasMoves = false;
#ifdef DEBUG
        cout << "while" << endl;
        for (int i = 0; i < m_sizeY; ++i)
        {
          for (int j = 0; j < m_sizeX; ++j)
          {
            cout << m_board[i][j] << " ";
          }
          cout << endl;
        }
        cout << "m_blackTiles = " << m_blackTiles << endl;
        cout << "mininmumBlackTiles = " << minimumBlackTiles << endl;
#endif
        for (int i = 0; i < m_sizeY; ++i)
        {
#ifdef DEBUG
        cout << "for1" << endl;
#endif
          for (int j = 0; j < m_sizeX; ++j)
          {
#ifdef DEBUG
            cout << "for2" << endl;
            cout << "tap quality at: " << i << ' ' << j << ": " << getTapQuality(j, i) << endl;
#endif
            if (getTapQuality(j, i) > 0)
            {
              if (minimumBlackTiles < m_blackTiles)
              {
                minimumBlackTiles = m_blackTiles;
              }
              hasMoves = true;
              tap(j, i);
              if (minimumBlackTiles <= m_blackTiles)
              {
                ++tapsNoImprove;
                if (tapsNoImprove > 10)
                {
                  hasSolution = false;
                  // Break for loops.
                  i = m_sizeY;
                  j = m_sizeX;
                }
              }
              else
              {
                tapsNoImprove = 0UL;
              }
            }
          }
        }
#ifdef DEBUG
        cout << "blacktiles: " << m_blackTiles << endl;
        break;
#endif
      }


      /////////////////////////////////////////////////////////////////////////
      // Show results.
      /////////////////////////////////////////////////////////////////////////
      if (hasSolution)
      {
        cout << "You have to tap " << m_taps << " tiles." << endl;
      }
      else
      {
        cout << "Damaged billboard." << endl;
      }

#ifdef DEBUG
      break;
#endif


      /////////////////////////////////////////////////////////////////////////
      // Clean memory.
      /////////////////////////////////////////////////////////////////////////
      for (int i = 0; i < m_sizeY; ++i)
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
  void tap(int x, int y)
  {
    ++m_taps;

    (m_board[y][x] = !m_board[y][x]) ? ++m_blackTiles : --m_blackTiles;
    if (isInRange(x + 1, y))
    {
      (m_board[y][x + 1] = !m_board[y][x + 1]) ? ++m_blackTiles :
                                                 --m_blackTiles;
    }
    if (isInRange(x - 1, y))
    {
      (m_board[y][x - 1] = !m_board[y][x - 1]) ? ++m_blackTiles :
                                                 --m_blackTiles;
    }
    if (isInRange(x, y + 1))
    {
      (m_board[y + 1][x] = !m_board[y + 1][x]) ? ++m_blackTiles :
                                                 --m_blackTiles;
    }
    if (isInRange(x, y - 1))
    {
      (m_board[y - 1][x] = !m_board[y - 1][x]) ? ++m_blackTiles :
                                                 --m_blackTiles;
    }
  }

  bool isInRange(int x, int y)
  {
    return (x >= 0 && x < m_sizeX && y >= 0 && y < m_sizeY);
  }

  int  getTapQuality(int x, int y)
  {
    int quality = 0;

    if (isInRange(x + 1, y))
    {
      if (m_board[y][x + 1] == true)
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
      if (m_board[y][x - 1] == true)
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
      if (m_board[y + 1][x] == true)
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
      if (m_board[y - 1][x] == true)
      {
        ++quality;
      }
      else
      {
        --quality;
      }
    }
    if (m_board[y][x] == true)
    {
        ++quality;
    }
    else
    {
        --quality;
    }

    return quality;
  }

  bool **m_board;
  int    m_sizeX;
  int    m_sizeY;
  size_t m_blackTiles;
  size_t m_taps;
};


int main()
{
  StrangeBillboard board;
  board.solve();

  return EXIT_SUCCESS;
}

