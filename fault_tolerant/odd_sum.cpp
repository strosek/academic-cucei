/* Practica 3. Computacion Tolerante A Fallos.
 *
 * Erick Daniel Corona Garcia. 210224314.
 */

#include <cstdlib>
#include <iostream>

using namespace std;

const int LIMIT_CALLS = 1000000;

struct odds
{
  int last;
  int count;
  int sum;
};

struct odds theOdds;

void sumNOddsRecursive(int oddsLimit, int stackCalls)
{
  if (theOdds.count >= oddsLimit)
  {
    return;
  }

  if (stackCalls >= LIMIT_CALLS)
  {
    return;
  }

  theOdds.last += 2;
  theOdds.sum += theOdds.last;
  theOdds.count += 1;

#ifdef DEBUG
  cout << theOdds.last << "  " << theOdds.sum << "  " << theOdds.count << endl;
#endif

  sumNOddsRecursive(oddsLimit, stackCalls + 1);
}

int sumNOdds(int n)
{
  theOdds.last = 1;
  theOdds.count = 1;
  theOdds.sum = 1;
  while (theOdds.count < n)
  {
    sumNOddsRecursive(n, 1);
  }

  return theOdds.sum;
}

int main()
{
  int n;
  int sum;
  while (true)
  {
    cout << "n: ";
    cin >> n;
    sum = sumNOdds(n);
    cout << "La suma es: " << sum << endl;
  }

  return EXIT_SUCCESS;
}

