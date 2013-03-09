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
#include <stdexcept>
#include <iomanip>
using namespace std;


bool isValidWord();
void M();
void N();
void R();

bool         g_isErrorFound;
size_t       g_characterIndex;
string       g_word;

const int K_LOOKAHEAD =          1;
const int ERROR_MESSAGE_WIDTH = 40;


int main(void) {
  const string exitString = ".";
  while (g_word.compare(exitString) != 0) {
    g_isErrorFound = false;
    g_characterIndex = 0;

    cout << "Enter word to parse (" << exitString << " to exit): ";
    cin >> g_word;

    if (g_word.compare(exitString) != 0) {
      try {
        if (isValidWord())
          cout << "Word accepted by grammar\n" << endl;
        else
          cout << "Word  \"" << g_word <<
              "\"  is not accepted by grammar\n" << endl;
      }
      catch (out_of_range outOfRangeException) {
        cerr << "error: word length is invalid" << endl;
        cout << "Word  \"" << g_word << 
            "\"  is not accepted by grammar\n" << endl;
      }
    }
  }

  return EXIT_SUCCESS;
}

bool isValidWord() {
  bool isValidWord = false;

  M();
  if (!g_isErrorFound)
    N();

  if (!g_isErrorFound) {
    if (g_characterIndex == g_word.length() - 1)
      isValidWord = true;
    else {
      cerr << "error: word length is invalid" << endl;
      isValidWord = false;
    }
  }
  
  return isValidWord;
}

void M() {
  if (g_word.at(g_characterIndex) == 'a') {
    ++g_characterIndex;
      
    M();
      
    if (g_word.at(g_characterIndex) == 'a')
      ++g_characterIndex;
    else {
      cerr << "error: " << setw(ERROR_MESSAGE_WIDTH) << 
          "'a' was expected at character: " << g_characterIndex << endl;
      g_isErrorFound = true;
    }
  }
  else if (g_word.at(g_characterIndex) == 'r') {
    ++g_characterIndex;
    
    R();
    
    if (g_word.at(g_characterIndex) == 'r')
      ++g_characterIndex;
    else {
      cerr << "error: " << setw(ERROR_MESSAGE_WIDTH) << 
          "'r' was expected at character: " << g_characterIndex << endl;
      g_isErrorFound = true;
    }
  }
  else {
    cerr << "error: " << setw(ERROR_MESSAGE_WIDTH) << 
        "'a' or 'r' were expected at character: " << g_characterIndex << endl;
    g_isErrorFound = true;
  }
}

void N() {
  if (g_word.at(g_characterIndex) == 'b') {
    if (g_word.at(g_characterIndex + K_LOOKAHEAD) == 'b') {
      ++g_characterIndex;
      
      N();
      
      if (g_word.at(g_characterIndex) == 'b')
        ++g_characterIndex;
      else {
        cerr << "error: " << setw(ERROR_MESSAGE_WIDTH) << 
            "'b' was expected at character: " << g_characterIndex << endl;
        g_isErrorFound = true;
      }
    }
    else if (g_word.at(g_characterIndex + K_LOOKAHEAD) == 'x') {
      ++g_characterIndex;
      R();
    }
    else {
      cerr << "error: " << setw(ERROR_MESSAGE_WIDTH) << 
          "'b' or 'x' were expected at character: " << g_characterIndex << endl;
      g_isErrorFound = true;
    }
  }
  else {
    cerr << "error: " << setw(ERROR_MESSAGE_WIDTH) <<
        "'b' was expected at character: " << g_characterIndex << endl;
    g_isErrorFound = true;
  }
}

void R() {
  if (g_word.at(g_characterIndex) == 'x')
    ++g_characterIndex;
  else {
    cerr << "error: " << setw(ERROR_MESSAGE_WIDTH) <<
        "'x' was expected at character: " << g_characterIndex << endl;
    g_isErrorFound = true;
  }
}

