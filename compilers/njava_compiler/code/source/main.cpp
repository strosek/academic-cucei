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
#include <cstdlib>
#include <string>
#include <utility>
#include <iomanip>

#include "../headers/main.hpp"
#include "../headers/scanner.hpp"
#include "../headers/parser.hpp"

using namespace std;


int main() {
  string fileName("test.njava");

  Parser parser;  
  parser.parse(fileName);
  int errors = parser.getErrors(), warnings = parser.getWarnings();

  if (errors > 0 || warnings > 0)
    cout << "\nCompilacion terminada con " << errors << 
        " errores, " << warnings << " advertencias" << endl;

  return errors == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
