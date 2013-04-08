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

#ifndef TOKENLEXEME_HPP
#define TOKENLEXEME_HPP

#include <string>

class TokenLexeme
{
public:
  TokenLexeme();
  TokenLexeme(const std::string& token, const std::string& lexeme, 
              unsigned int line, unsigned int row);
  
  void setToken(const std::string& token);
  void setLexeme(const std::string& lexeme);
  void setLine(unsigned int line);
  void setRow(unsigned int row);
  
  std::string  getToken() const;
  std::string  getLexeme() const;
  unsigned int getLine() const;
  unsigned int getRow() const;
private:
  std::string  m_token;
  std::string  m_lexeme;
  unsigned int m_line;
  unsigned int m_row;
};

#endif // TOKENLEXEME_HPP
