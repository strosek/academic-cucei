//  Copyright (c) 2013 Erick Daniel Corona <edcoronag@gmail.com>
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation
//  files (the Software), to deal in the Software without
//  restriction, including without limitation the rights to use,
//  copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following
//  conditions:
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR                                                                                                    
//  OTHER DEALINGS IN THE SOFTWARE.


#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <utility>
#include <fstream>
#include <queue>

#include "tokenlexeme.hpp"

#define N_KEYWORDS    15
#define N_LOGICCONSTS 2

#define N_TRANSITIONS 18
#define N_STATES      22

typedef enum {
  TRANS_LETTER = 0,
  TRANS_UNDERSCORE, 
  TRANS_DIGIT,
  TRANS_DOT,
  TRANS_DELIMITER,
  TRANS_SIGN,
  TRANS_ARITHMETIC,
  TRANS_LESSER,
  TRANS_GREATER,
  TRANS_EQUAL,
  TRANS_COLON,
  TRANS_QUOTE,
  TRANS_EXP,
  TRANS_HEX,
  TRANS_ZERO,
  TRANS_SPACE,
  TRANS_X,
  TRANS_OCT
} Transition_t;

static const int automata[N_STATES][N_TRANSITIONS] {
  // 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17
  // l   _   d   .  dl  si  ar   <   >   =   :   "   e   h   0   s   x   o
  {  1,  1,  2, 20, 12, 13, 13, 17, 16, 14, 18, 11,  1,  1,  6,  0,  1,  2}, // 0
  {  1,  1,  1, -1, -2, -2, -2, -2, -2, -2, -2, -2,  1,  1,  1, -2,  1,  1}, // 1*
  { -2, -2,  2, 20, -2, -2, -2, -2, -2, -2, -2, -2,  3, -2,  2, -2, -2,  2}, // 2*
  { -1, -1,  4, -1, -1,  5, -1, -1, -1, -1, -1, -1, -1, -1,  4, -1, -1,  4}, // 3
  { -2, -2,  4, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,  4, -2, -2,  4}, // 4*
  { -1, -1,  4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4, -1, -1,  4}, // 5
  { -2, -2, -2, 20, -2, -2, -2, -2, -2, -2, -2, -2,  3, -2,  6, -2,  7,  6}, // 6*
  { -1, -1,  8, -1, -1, -1, -1, -1, -1, -1, -1, -1,  8,  8,  8, -1, -1,  8}, // 7
  { -2, -2,  8, -2, -2, -2, -2, -2, -2, -2, -2, -2,  8,  8,  8, -2, -2,  8}, // 8*
  {  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 10,  9,  9,  9,  9,  9,  9}, // 9
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 10*
  {  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 10,  9,  9,  9,  9,  9,  9}, // 11
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 12*
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 13*
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 14*
  { -2, -2, -2, -2, -2,  2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 15*
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, 15, -2, -2, -2, -2, -2, -2, -2, -2}, // 16*
  { -2, -2, -2, -2, -2, -2, -2, -2, 15, 15, -2, -2, -2, -2, -2, -2, -2, -2}, // 17*
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1}, // 18
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 19*
  { -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21, -1, -1, 21}, // 20
  { -2, -2, 21, -2, -2, -2, -2, -2, -2, -2, -2, -2,  3, -2, 21, -2, -2, 21}  // 21
  // l   _   d   .  dl  si  ar   <   >   =   :   "   e   h   0   s   x   o
};

static const std::string keywords[N_KEYWORDS] = {
  "alfabetico", "logico", "real", "entero", "imprime", "publico", "estatico",
  "sin_tipo", "principal", "clase", "no", "y", "o", "si", "sino"
};
static const std::string logic_consts[N_LOGICCONSTS] = {
  "verdadero", "falso"
};
static const int STATE_ERROR        = -1;
static const int STATE_RECOIL_ERROR = -2;


class Scanner
{
public:
  Scanner();
  ~Scanner();

  void        scan(const std::string& fileName);
  int         getMaxTokens() const;
  int         getErrors() const;
  TokenLexeme getNextTokenLexeme();

private:
  Transition_t getTransitionIndex(char character) const;
  
  int                                               m_currentLine;
  int                                               m_currentLineCharacter;
  int                                               m_errors;
  std::ifstream                                     m_sourceFile;
  int                                               m_currentToken;
  int                                               m_nTokens;
  std::queue<TokenLexeme>                           m_tokensLexemes;
};

#endif // SCANNER_HPP
