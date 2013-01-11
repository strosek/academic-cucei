// ACM ICPC Problem Set I - 100 from UVa

#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

int main()
{
    register int integer1, integer2;
    register int n;
    register int cycleLength;
    register int maxCycleLength;
    register int i;
    while (true)
    {
        maxCycleLength = 0;
        cin >> integer1 >> integer2;
        for (i = integer2 > integer1 ? integer1 : integer2; 
				i <= (integer2 > integer1 ? integer2 : integer1);
				++i)
        {
            cycleLength = 1;
            n = i;
            while ( n > 1 )
            {
                ++cycleLength;
                if ( n == 1 )
                    break;
                if ( ( n & 1 ) == 1 )
                    n = n + n + n + 1;
                else
                    n /= 2;
            }
            if ( cycleLength > maxCycleLength )
                maxCycleLength = cycleLength;
        }
        if ( cin.good() )
            printf("%d %d %d\n", integer1, integer2, maxCycleLength);
        else
            break;
    }

    return EXIT_SUCCESS;
}

