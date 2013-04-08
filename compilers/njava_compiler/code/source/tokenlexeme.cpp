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

#include "../headers/tokenlexeme.hpp"

#include <string>

using namespace std;

TokenLexeme::TokenLexeme() :
  m_token(),
  m_lexeme(),
  m_line(1),
  m_row(1)
{
}

TokenLexeme::TokenLexeme(const string& token, const string& lexeme, unsigned int line, unsigned int row) :
  m_token(token),
  m_lexeme(lexeme),
  m_line(line),
  m_row(row)
{
}

void TokenLexeme::setToken(const string& token) {
  m_token = token;
}

void TokenLexeme::setLexeme(const string& lexeme) {
  m_lexeme = lexeme;
}

void TokenLexeme::setLine(unsigned int line) {
  m_line = line;
}

void TokenLexeme::setRow(unsigned int row) {
  m_row = row;
}

string TokenLexeme::getToken() const {
  return m_token;
}

string TokenLexeme::getLexeme() const {
  return m_lexeme;
}

unsigned int TokenLexeme::getLine() const {
  return m_line;
}

unsigned int TokenLexeme::getRow() const {
  return m_row;
}

