/* Practica 1. Programacion tolerante a fallas.
 *
 * Erick Daniel Corona Garcia. 210224314.
 */

#include <cstdlib>
#include <iostream>
#include <limits>
#include <list>
#include <sstream>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;


int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getwchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != 'q')
  {
    ungetc(ch, stdin);
    return EXIT_FAILURE;
  }
 
  return EXIT_SUCCESS;
}


typedef long int Unit_t;
const long int UNIT_MAX = LONG_MAX;

int main()
{
  cout << "UNIT_MAX: " << UNIT_MAX << endl;

  while (cin.good())
  {
    string bigNumberString;
    cout << "Numerote a revisar: ";
    cin >> bigNumberString;

    if (bigNumberString.compare("q") == 0)
    {
      exit(EXIT_SUCCESS);
    }

    if (bigNumberString.find_first_not_of("-0123456789") != string::npos)
    {
      cerr << "error: entrada con caracteres invalidos." << endl;
      continue;
    }

    Unit_t digit;
    cout << "Digito a buscar: ";
    cin >> digit;

    unsigned int maxDigitsPerUnit;
    ostringstream unitStream;
    unitStream << UNIT_MAX;
    maxDigitsPerUnit = unitStream.str().size();

    list<Unit_t> bigNumber;
    istringstream * bigNumberStream;
    string subNumberString;
    Unit_t subNumber;
    size_t lastIndex = 0;
    size_t bigNumberSize = bigNumberString.size();
    while (lastIndex < bigNumberSize)
    {
      subNumberString = bigNumberString.substr(lastIndex, maxDigitsPerUnit - 1);

      bigNumberStream = new istringstream();
      bigNumberStream->str(subNumberString);
      (*bigNumberStream) >> subNumber;
      delete bigNumberStream;

      bigNumber.push_back(subNumber);

      lastIndex += maxDigitsPerUnit + 1;
    }

    Unit_t maxDivisor = 1L;
    for (unsigned int i = 0; i < maxDigitsPerUnit - 1U; ++i)
    {
      maxDivisor *= 10L;
    }

    Unit_t digitCount = 0UL;
    Unit_t divisor;
    for (list<Unit_t>::iterator it = bigNumber.begin(); it != bigNumber.end();
         ++it)
    {
      kbhit();
      divisor = 1;
      while (divisor <= (*it) && divisor < maxDivisor)
      {
        divisor *= 10;
      }
      divisor /= 10;

      while (divisor >= 1)
      {
        if (((*it) / divisor) % 10 == digit)
        {
          ++digitCount;
        }

        divisor /= 10;
      }
    }

    cout << "Veces que aparece el digito: " << digitCount << endl;
  }

  return EXIT_SUCCESS;
}

