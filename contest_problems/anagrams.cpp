//  Copyright (c) 2012 Erick Daniel Corona <edcoronag@gmail.com>
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

// Solution to: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=92
#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <iomanip>

#include <string.h>

using namespace std;

// #define DEBUG

const int k_maxWords = 1000;
const int k_maxLetters = 80;
const int k_lettersInAlphabet = 256;

bool isAnagram(const int* const wordLetters1, const int* const wordLetters2);

int main(void) {
    set<string> dictionary;

    int wordNo = 0;
    string word;
    while (word != "#" && wordNo < k_maxWords) {
        cin >> word;
#ifdef DEBUG
        cout << word << endl;
#endif
        if (word != "#") {
            dictionary.insert(word);
            ++wordNo;
        }
    }
    const int nWordsRead = wordNo;

    int lettersCount[k_maxWords][k_lettersInAlphabet] = {{0}};

    wordNo = 0;
    for (set<string>::iterator wordIt = dictionary.begin(); wordIt != dictionary.end(); ++wordIt) {
        for (string::const_iterator letterIt = wordIt->begin(); letterIt != wordIt->end(); ++letterIt) {
            if (*letterIt >= 'a' && *letterIt <= 'z') {
                ++lettersCount[wordNo][*letterIt-('a'-'A')];
            }
            else {
                ++lettersCount[wordNo][static_cast<int>(*letterIt)];
            }
        }
        ++wordNo;
    }

#ifdef DEBUG
    for (int i = 0; i < nWordsRead; ++i) {
        cout << setw(4) << i + 1 << ": ";
        for (int j = 0; j < k_lettersInAlphabet; ++j) {
            cout << lettersCount[i][j] << ' ';
        }
        cout << endl;
    }
#endif

    int relations[k_maxWords] = {0};
    bool anagramFound;
    int nextAnagram = 1;

    for (int iWord = 0; iWord < nWordsRead; ++iWord) {
        anagramFound = false;
        if (relations[iWord] == 0) { // if current word is not already catalogued as anagram
            for (int jWord = iWord + 1; jWord < nWordsRead; ++jWord) {
                if (isAnagram(lettersCount[iWord], lettersCount[jWord])) {
                    relations[iWord] = nextAnagram;
                    relations[jWord] = nextAnagram;
                    anagramFound = true;
                }
            }
            if (anagramFound) {
                ++nextAnagram;
            }
        }
    }
#ifdef DEBUG
    for (int i = 0; i < nWordsRead; ++i) {
        cout << setw(4) << i + 1 << ": " << relations[i] << endl;
    }

    for (set<string>::iterator wordIt = dictionary.begin(); wordIt != dictionary.end(); ++wordIt) {
        cout << *wordIt << endl;
    }
    cout << endl;
#endif

    wordNo = 0;
    nextAnagram = 1;
    for (set<string>::iterator wordIt = dictionary.begin(); wordIt != dictionary.end(); ++wordIt) {
        if (relations[wordNo] == nextAnagram) {
            cout << *wordIt << endl;
            ++nextAnagram;
        }
        ++wordNo;
    }
    
    return EXIT_SUCCESS;
}

bool isAnagram(const int* const wordLetters1, const int* const wordLetters2) {
    for (int i = 0; i < k_lettersInAlphabet; ++i) {
        if (wordLetters1[i] != wordLetters2[i]) {
            return false;
        }
    }
    return true;
}
