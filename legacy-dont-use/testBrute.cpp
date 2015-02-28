#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include <vector>

#define MAX_INPUT_NUM 2166
#define MAX_SEARCH_NUM 1000000000 // There are 2166 left-truncatable primes under 1,000,000,000.
#define INPUT_PARAM argv[1]

bool isPrime(long p)
{
    // 1 is not prime by definition
    if (p == 1) return false;

    // 2 is the only even number which is prime
    if (p == 2) return true;

    // the remaining are not (they are divisible by 2)
    if (p % 2 == 0) return false;
    
    // Given it is an odd number different from 1, then check primality until we get to the sqrt of p (greater checks are redundant)
    long sqrtP = long(sqrt(p));
    for (long i = 3; i <= sqrtP; i += 2)
    {
        if (p % i == 0) return false;
    }       
    return true;
}

long getNthTruncatablePrimeByBruteForce(int nthTruncatable)
{
	if (nthTruncatable <= 0 || nthTruncatable > MAX_INPUT_NUM)
	{
		return -1;
	}

	size_t truncatableCounter = 0;
	// iterate over every possible number in range
	for (size_t j = 0; j < MAX_SEARCH_NUM; j++)
	{
		size_t testNum = j;

		// Will test if i is prime. If it is, then the same will be asked for the truncated version of i.
		// This will eventually conclude that i is a left truncatable prime number. Then the truncatableCounter
		// will be incremented until we get to the number we are looking for.
		while (isPrime(testNum))
		{
			int mult = 10;
			while (testNum/mult != 0) mult *= 10;
			mult /= 10;

			if (mult == 1)
			{
				if (nthTruncatable == ++truncatableCounter)
				{
					return j;
				}
			}

			testNum -= testNum/mult*mult;
		}		
	}

	return -1; // should never get here
}
/*
long getNthTruncatablePrime(long nthTruncatable)
{
    if(nthTruncatable <= 0)
        return -1;

    size_t initial_size = 200;

    long lastPrimes;
    lastPrimes.reserve( initial_size );

    lastPrimes.push_back(2);
    lastPrimes.push_back(3);
    lastPrimes.push_back(5);
    lastPrimes.push_back(7);

    // trivial case: when asking for first 4 truncatable primes (i.e. first 4 primes)
    if(nthTruncatable < 5) return lastPrimes[nthTruncatable -1];

    int truncatable_primes = 4;
    const int max_power = 9;

    ///iterate through powers (10s, 100s, 1000s, etc.)
    for(int power = 1, mult_factor = 10; power <= max_power; ++power, mult_factor *= 10)
    {
        std::vector< long > current_primes;
        current_primes.reserve( initial_size );

        ///iterate through smaller powers inside the outer power (10s in 100s, 100s in 1000s)
        for(int i = 1; i <= max_power; ++i)
        {
            ///construct a new truncatable prime from previous truncatable primes 
            std::vector<long>::const_iterator itEnd = lastPrimes.end();
            for(std::vector<long>::const_iterator itBegin = lastPrimes.begin(); itBegin != itEnd ; ++itBegin)
            {
                const long result = mult_factor * (i) + *itBegin;

                if(isPrime( result ) )
                {
                    ++truncatable_primes;
                    if(truncatable_primes == nthTruncatable)
                        return result;
                    
                    current_primes.push_back( result );
                }
            }
        }
        lastPrimes = current_primes;
    }
    return -1;
}
*/
int main(int argc, char **argv)
{
	int msec;

	// Will try brute force version
	clock_t start = clock(), diff;

	printf("%li\n", getNthTruncatablePrimeByBruteForce(atoi(INPUT_PARAM)));

	diff = clock() - start;
	msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Brute Force: Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

	// Will try optimized version
/*	start = clock();

	printf("%li\n", getNthTruncatablePrime(atoi(INPUT_PARAM)));

	diff = clock() - start;
	msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Optimized: Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);*/

	return EXIT_SUCCESS;
}