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

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

#define N_KEYWORDS 15
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


string keywords[N_KEYWORDS] = {
  "alfabetico", "logico", "real", "entero", "imprime", "publico", "estatico",
  "sin_tipo", "principal", "clase", "no", "y", "o", "si", "sino"
};

string logic_consts[N_LOGICCONSTS] = {
  "verdadero", "falso"
};


const int STATE_ERROR        = -1;
const int STATE_RECOIL_ERROR = -2;

int automata[N_STATES][N_TRANSITIONS] {
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
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -2}, // 18
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 19*
  { -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21, -1, -1, 21}, // 20
  { -2, -2, 21, -2, -2, -2, -2, -2, -2, -2, -2, -2,  3, -2, 21, -2, -2, 21}  // 21
  // l   _   d   .  dl  si  ar   <   >   =   :   "   e   h   0   s   x   o
};


Transition_t getTransitionIndex(char character);


int main(void) { 
  string fileName;
  cout << "NanoJAVA\n"
       << "=================\n" << endl;
  cout << "Nombre del archivo a analizar: ";
  cin >> fileName;
  ifstream sourceFile;
  sourceFile.open(fileName.c_str());

  if (sourceFile.is_open()) {
    char currentChar;
    int nextState = 0, currentState = 0;
    string token, currentLexeme;
    bool isErrorFound = false, isKeywordMatched = false;
    int tokenNo = 0;

    cout << "njavac: analisis lexico:\n" << endl;
    cout << setw(5) << "N0" << setw(20) << "TOKEN" << setw(20) << "LEXEMA" <<
        endl;
    cout << "=====" << " ===================" << " ===================" << endl;
    while ((currentChar = sourceFile.get()) != EOF && !isErrorFound) {
      nextState = automata[currentState][getTransitionIndex(currentChar)];

      if (nextState == STATE_RECOIL_ERROR) {
        switch (currentState) {
          case 1 :
            token = "identificador";
            isKeywordMatched = false;
            for (int i = 0; i < N_KEYWORDS && !isKeywordMatched; ++i) {
              if (keywords[i].compare(currentLexeme) == 0) {
                isKeywordMatched = true;
                token = "pal_reservada";
              }
            }
            if (!isKeywordMatched) {
              for (int i = 0; i < N_LOGICCONSTS && !isKeywordMatched; ++i) {
                if (logic_consts[i].compare(currentLexeme) == 0) {
                  isKeywordMatched = true;
                  token = "const_logica";
                }
              }
            }
            break;
          case 2 :
            token = "entero";
            break;
          case  4 :
          case 21 :
            token = "real";
            break;
          case 6 :
            token = "octal";
            break;
          case 8 :
            token = "hexadecimal";
            break;
          case 10 :
            token = "const_alfabetica";
            break;
          case 12 :
            token = "delimitador";
            break;
          case 13 :
            token = "op_aritmetico";
            break;
          case 14 :
          case 15 :
          case 16 :
          case 17 :
            token = "op_relacional";
            break;
          case 19 :
            token = "op_asignacion";
            break;
          default :
            cerr << "njavac: error de estado" << endl;
            isErrorFound = true;
            break;
        }

        if (!isErrorFound) {
          cout << setw(4) << tokenNo << ':' << setw(20) << token <<
              setw(20) << currentLexeme << endl;
          ++tokenNo;
          token = "";
          currentLexeme = "";
          nextState = 0;
        }

        sourceFile.unget();
      }
      else if (nextState == STATE_ERROR) {
        cerr << "njavac: error en analisis lexico: lexema invalido " << 
            currentLexeme << endl;
        isErrorFound = true;
      }
      else if (!isspace(currentChar))
        currentLexeme += currentChar;

      currentState = nextState;
    }

    if (!isErrorFound)
      cout << "\nnjavac: analisis lexico exitoso!" << endl;
    else
      cerr << "njavac: error en analisis lexico" << endl;
  }
  else {
    cerr << "njavac: error al abrir archivo fuente" << endl;
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

Transition_t getTransitionIndex(char character) {
  Transition_t transitionIndex = TRANS_LETTER;
  
  if (isdigit(character)) {
    if (character == '0')
      transitionIndex = TRANS_ZERO;
    else if (character <= '7')
      transitionIndex = TRANS_OCT;
    else
      transitionIndex = TRANS_DIGIT;
  }
  else if (isalpha(character)) {
    if (tolower(character) == 'e')
      transitionIndex = TRANS_EXP;
    else if (tolower(character) == 'x')
      transitionIndex = TRANS_X;
    else if (tolower(character) <= 'f')
      transitionIndex = TRANS_HEX;
    else
      transitionIndex = TRANS_LETTER;
  }
  else if (isspace(character)) {
    transitionIndex = TRANS_SPACE;
  }
  else {
    switch (character) {
      case ';' :
      case '(' :
      case ')' :
      case '[' :
      case ']' :
      case '{' :
      case '}' :
        transitionIndex = TRANS_DELIMITER;
        break;
      case '+' :
      case '-' :
        transitionIndex = TRANS_SIGN;
        break;
      case '*' :
      case '/' :
      case '%' :
      case '^' :
        transitionIndex = TRANS_ARITHMETIC;
        break;
      case ':' :
        transitionIndex = TRANS_COLON;
        break;
      case '=' :
        transitionIndex = TRANS_EQUAL;
        break;
      case '<' :
        transitionIndex = TRANS_LESSER;
        break;
      case '>' :
        transitionIndex = TRANS_GREATER;
        break;
      case '_' :
        transitionIndex = TRANS_UNDERSCORE;
        break;
      case '"' :
        transitionIndex = TRANS_QUOTE;
        break;
      case '.' :
        transitionIndex = TRANS_DOT;
        break;
      default :
        cerr << "njavac: caracter invalido: " << "'" << character  <<
            "' " << static_cast<int>(character) << endl;
        break;
    }
  }
  
  return transitionIndex;
}
