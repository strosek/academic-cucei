/* Practica 2. Computacion Tolerante A Fallos.
 *
 * Erick Daniel Corona Garcia. 210224314.
 */

#include <iostream>

using namespace std;

int sumNOdds(int n)
{
  if (n <= 0)
    return 0;
  if (n == 1)
    return 1;
  return sumNOdds(n - 1) + 2;
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
}

