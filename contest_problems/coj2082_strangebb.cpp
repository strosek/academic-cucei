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
#include <cmath>
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
      size_t minimumBlackTiles = ULONG_MAX;
      size_t passesNoImprove = 0UL;
      m_taps = 0UL;
      int bestTapX = 0;
      int bestTapY = 0;
      int bestTapQuality;
      while (m_blackTiles > 0 && hasSolution)
      {
        bestTapQuality = INT_MIN;
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
          for (int j = 0; j < m_sizeX; ++j)
          {
            int tapQuality = getTapQuality(j, i);
            if (tapQuality > bestTapQuality)
            {
              bestTapX = j;
              bestTapY = i;
              bestTapQuality = tapQuality;
            }
            else if (tapQuality == bestTapQuality)
            {
              int centerX = m_sizeX / 2;
              int centerY = m_sizeY / 2;
              float distanceToCenterBest = sqrt(pow(bestTapX - centerX, 2.0f) +
                                                pow(bestTapY - centerY, 2.0f));
              float distanceToCenterNew = sqrt(pow(j - centerX, 2.0f) +
                                               pow(i - centerY, 2.0f));
              if (distanceToCenterNew < distanceToCenterBest)
              {
                bestTapX = j;
                bestTapY = i;
                bestTapQuality = tapQuality;
              }
            }
          }
        }

        if (bestTapQuality > 0)
        {
#ifdef DEBUG
          cout << "best tap quality: " << bestTapQuality << endl;
#endif
          tap(bestTapX, bestTapY);
        }

        if (m_blackTiles < minimumBlackTiles)
        {
          minimumBlackTiles = m_blackTiles;
          passesNoImprove = 0UL;
        }
        else
        {
          ++passesNoImprove;
          if (passesNoImprove > 10)
          {
            hasSolution = false;
            goto results;
          }
        }

#ifdef DEBUG
        cout << "blacktiles: " << m_blackTiles << endl;
#endif
      }


      /////////////////////////////////////////////////////////////////////////
      // Show results.
      /////////////////////////////////////////////////////////////////////////
results:
      if (hasSolution)
      {
        cout << "You have to tap " << m_taps << " tiles." << endl;
      }
      else
      {
        cout << "Damaged billboard." << endl;
      }


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
#ifdef DEBUG
    cout << "tapping " << x << " " << y << endl;
#endif
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

