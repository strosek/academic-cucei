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


#include "../headers/scanner.hpp"

#include <utility>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


Scanner::Scanner() :
  m_currentLine(1),
  m_currentLineCharacter(1),
  m_errors(0),
  m_sourceFile(),
  m_currentToken(0),
  m_nTokens(0),
  m_tokensLexemes()
{
}

void Scanner::scan(const string& fileName) { 
  m_sourceFile.open(fileName.c_str());

  if (m_sourceFile.is_open()) {
    char currentChar;
    int nextState = 0, currentState = 0;
    string token, lexeme;
    bool isErrorFound = false, isKeywordMatched = false;

    while ((currentChar = m_sourceFile.get()) != EOF && !isErrorFound) {
      nextState = automata[currentState][getTransitionIndex(currentChar)];
      
      if (nextState != STATE_RECOIL_ERROR) {
      if (currentChar == '\n') {
        ++m_currentLine;
        m_currentLineCharacter = 0;
      }
      else
        ++m_currentLineCharacter;
      }

      if (nextState == STATE_RECOIL_ERROR) {
        switch (currentState) {
          case 1 :
            token = "identificador";
            isKeywordMatched = false;
            for (int i = 0; i < N_KEYWORDS && !isKeywordMatched; ++i) {
              if (keywords[i].compare(lexeme) == 0) {
                isKeywordMatched = true;
                token = "pal_reservada";
              }
            }
            if (!isKeywordMatched) {
              for (int i = 0; i < N_LOGICCONSTS && !isKeywordMatched; ++i) {
                if (logic_consts[i].compare(lexeme) == 0) {
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
          m_tokensLexemes.push(TokenLexeme(token, lexeme, m_currentLine, 
                                           m_currentLineCharacter -
                                           lexeme.length()));
          ++m_nTokens;
          token = "";
          lexeme = "";
          nextState = 0;
        }

        m_sourceFile.unget();
      }
      else if (nextState == STATE_ERROR) {
        cerr << "njavac: error: " << m_currentLine << ", " <<
            m_currentLineCharacter << 
            ": lexema invalido \"" << 
            lexeme << currentChar << "\"" << endl;
        isErrorFound = true;
        ++m_errors;
      }
      else if (isspace(currentChar) && currentState == 9)
        lexeme += currentChar;
      else if (!isspace(currentChar))
        lexeme += currentChar;

      currentState = nextState;
    }
  }
  else {
    cerr << "njavac: error al abrir archivo fuente" << endl;
    ++m_errors;
  }
}

TokenLexeme Scanner::getNextTokenLexeme() {
  TokenLexeme temporal;
  if (!m_tokensLexemes.empty()) {
    temporal = m_tokensLexemes.front();
    m_tokensLexemes.pop();
  }
  return temporal;
}

Transition_t Scanner::getTransitionIndex(char character) {
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
      case ',' :
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
        cerr << "njavac: error: " << m_currentLine << ", " << 
            m_currentLineCharacter << ": caracter invalido: " << "'" << 
            character  << "' " << endl;
        ++m_errors;
        break;
    }
  }
  
  return transitionIndex;
}

int Scanner::getMaxTokens() const {
  return m_nTokens;
}

int Scanner::getErrors() const {
  return m_errors;
}