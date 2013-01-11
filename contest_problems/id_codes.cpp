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

// Solution to http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=82

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

const int k_wordSize = 50 + 1;

int compare(const void* char1, const void* char2);

int main(void) {
    char word[k_wordSize] = {0};
    int wordLength;
    bool isThereSuccessor;
    char auxChar;

    while (word[0] != '#') {
        cin >> word;
        if (word[0] != '#') {
            wordLength = strlen(word);
            isThereSuccessor = false;

            for (int i = 0; i < wordLength - 1 && !isThereSuccessor; ++i) {
                if (word[(wordLength - 1) - (i + 1)] < word[(wordLength - 1) - i]) {
                    auxChar = word[(wordLength - 1) - (i + 1)];
                    word[(wordLength - 1) - (i + 1)] = word[wordLength - 1];
                    word[wordLength - 1] = auxChar;

                    qsort(word + (wordLength - 1) - i, i + 1, sizeof(char), compare);

                    cout << word << endl;
                    isThereSuccessor = true;
                }
            }
            
            if (!isThereSuccessor) {
                cout << "No Successor" << endl;
            }
        }
    }

    return EXIT_SUCCESS;
}

int compare(const void* a, const void* b) {
    return *(char*)a - *(char*)b;
}
