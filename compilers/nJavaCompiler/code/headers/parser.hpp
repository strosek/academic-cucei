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

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <utility>

#include "scanner.hpp"

class Parser
{

public:
  Parser();
  ~Parser();

  int  getErrors() const;
  int  getWarnings() const;
  void parse(const std::string& fileName);
private:
  void program();
  void variablesMain();
  void variable();
  void initializationValue();
  void mainFunction();
  void body();
  void statement();
  void command();
  void assign();
  void print();
  void expression();
  void relationalExpression();
  void arithmeticExpression();
  void multiplication();
  void exponent();
  void sign();
  void term();
  
  int         m_errors;
  int         m_warnings;
  int         m_tokenNo;
  Scanner     m_scanner;
  TokenLexeme m_currentToken;
};

#endif // PARSER_HPP
