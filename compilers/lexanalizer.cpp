// Erick Daniel Corona García. 210224314. Compiladores 2013A.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

#define N_KEYWORDS 17

#define N_TRANSITIONS 28
#define N_STATES      22



typedef enum {
  TRANS_LETTER = 0, // 0
  TRANS_UNDERSCORE, // 1
  TRANS_DIGIT,      // 2
  TRANS_DOT,        // 3
  TRANS_SEMICOLON,  // 4
  TRANS_OPARENT,    // 5
  TRANS_CPARENT,    // 6
  TRANS_OBRACKET,   // 7
  TRANS_CBRACKET,   // 8
  TRANS_OCURLY,     // 9
  TRANS_CCURLY,     // 10
  TRANS_PLUS,       // 11
  TRANS_MINUS,      // 12
  TRANS_ASTERISK,   // 13
  TRANS_SLASH,      // 14
  TRANS_PERCENT,    // 15
  TRANS_TILDE,      // 16
  TRANS_LESSER,     // 17
  TRANS_GREATER,    // 18
  TRANS_EQUAL,      // 19
  TRANS_COLON,      // 20
  TRANS_QUOTE,      // 21
  TRANS_EXP,        // 22
  TRANS_HEX,        // 23
  TRANS_ZERO,       // 24
  TRANS_SPACE,      // 25
  TRANS_X,          // 26
  TRANS_OCT         // 27
} Transition_t;


string keywords[N_KEYWORDS] = {
  "alfabetico", "logico", "real", "entero", "imprime", "publico", "estatico",
  "sin_tipo", "principal", "clase", "verdadero", "false", "no", "y", "o",
  "si", "sino"
};


const int STATE_ERROR        = -1;
const int STATE_RECOIL_ERROR = -2;

int automata[N_STATES][N_TRANSITIONS] {
  // 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27
  // l   _   d   .   ;   (   )   [   ]   {   }   +   -   *   /   %   ^   <   >   =   :   "   e   h   0   s   x   o
  {  1,  1,  2, 20, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 17, 16, 14, 18, 11,  1,  1,  6,  0,  1,  2}, // 0
  {  1,  1,  1, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,  1,  1,  1, -2,  1,  1}, // 1*
  { -2, -2,  2, 20, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,  3, -2,  2, -2, -2,  2}, // 2*
  { -1, -1,  4, -1, -1, -1, -1, -1, -1, -1, -1,  5,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4, -1, -1,  4}, // 3
  { -2, -2,  4, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,  4, -2, -2,  4}, // 4*
  { -1, -1,  4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4, -1, -1,  4}, // 5
  { -2, -2, -2, 20, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,  3, -2,  6, -2,  7,  6}, // 6*
  { -1, -1,  8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  8,  8,  8, -1, -1,  8}, // 7
  { -2, -2,  8, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,  8,  8,  8, -2, -2,  8}, // 8*
  {  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 10,  9,  9,  9,  9,  9,  9}, // 9
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 10*
  {  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 10,  9,  9,  9,  9,  9,  9}, // 11
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 12*
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 13*
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 14*
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 15*
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 15, -2, -2, -2, -2, -2, -2, -2, -2}, // 16*
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 15, 15, -2, -2, -2, -2, -2, -2, -2, -2}, // 17*
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -2}, // 18
  { -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}, // 19*
  { -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21, -1, -1, 21}, // 20
  { -2, -2, 21, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,  3, -2, 21, -2, -2, 21}, // 21
  // l   _   d   .   ;   (   )   [   ]   {   }   +   -   *   /   %   ^   <   >   =   :   "   e   h   0   s   x   o
};


Transition_t getTransitionIndex(char character);


int main(void) { 
  string fileName;
  cout << "NanoJAVA Compiler\n"
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
                token = "palabra_reservada";
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
            token = "alfabetico";
            break;
          case 12 :
            token = "delimitador";
            break;
          case 13 :
            token = "operador_aritmetico";
            break;
          case 14 :
          case 15 :
          case 16 :
          case 17 :
            token = "operador_relacional";
            break;
          case 19 :
            token = "operador_asignacion";
            break;
          default :
            cerr << "njavac: error" << endl;
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
        
        // Actual recoil
        sourceFile.unget();
      }
      else if (nextState == STATE_ERROR) {
        cerr << "njavac: error en analisis lexico: lexema invalido" << 
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
    cerr << "njavac: error al abrir archivo de codigo fuente" << endl;
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

Transition_t getTransitionIndex(char character) {
  Transition_t transitionIndex;
  
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
        transitionIndex = TRANS_SEMICOLON;
        break;
      case '(' :
        transitionIndex = TRANS_OPARENT;
        break;
      case ')' :
        transitionIndex = TRANS_CPARENT;
        break;
      case '[' :
        transitionIndex = TRANS_OBRACKET;
        break;
      case ']' :
        transitionIndex = TRANS_CBRACKET;
        break;
      case '{' :
        transitionIndex = TRANS_OCURLY;
        break;
      case '}' :
        transitionIndex = TRANS_CCURLY;
        break;
      case '+' :
        transitionIndex = TRANS_PLUS;
        break;
      case '-' :
        transitionIndex = TRANS_MINUS;
        break;
      case '*' :
        transitionIndex = TRANS_ASTERISK;
        break;
      case '/' :
        transitionIndex = TRANS_SLASH;
        break;
      case '%' :
        transitionIndex = TRANS_PERCENT;
        break;
      case '^' :
        transitionIndex = TRANS_TILDE;
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
        cerr << "njavac: caracter no valido: " << "'" << character  <<
            "' " << static_cast<int>(character) << endl;
        break;
    }
  }
  
  return transitionIndex;
}
