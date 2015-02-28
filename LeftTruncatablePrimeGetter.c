/* LeftTruncatablePrimeGetter.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_ARGS 2
#define PRG_NAME argv[0]
#define INPUT_PARAM argv[1]
#define PARAM_HELP "--help"
#define MAX_INPUT_NUM 2166
#define MAX_SEARCH_POW 1000000000 /* There are 2166 left-truncatable primes under 1,000,000,000. */

typedef enum {FALSE = 0, TRUE} bool;

void printHelp(char* programName)
{
	printf("How to use:\n");
	printf("%s <Nth number>\n", programName);
	printf("Then the Nth left truncatable prime number will be returned.\n");
	printf("NOTE: Valid input number ranges from 1 to %d.\n", MAX_INPUT_NUM);
	
	printf("\nExample:\n");
	printf("%s 100\n", programName);
	printf("5167\n");
}

void cpyVector(long* dst, long* src, unsigned int* dstSize, const unsigned int srcSize)
{
	unsigned int i = 0;
	for (i = 0; i < srcSize; i++)
	{
		dst[i] = src[i];
	}
	*dstSize = srcSize;
}

bool isPrime(long p)
{
    long sqrtP;
    long i;

    /* 1 is not prime by definition */
    if (p == 1) return FALSE;

    /* 2 is the only even number which is prime */
    if (p == 2) return TRUE;

	/* the remaining are not (they are divisible by 2) */
    if (p % 2 == 0) return FALSE;
    
    /* Given it is an odd number different from 1, then check primality until we get to the sqrt of p (greater checks are redundant) */
    sqrtP = (long)sqrt(p);
    for (i = 3; i <= sqrtP; i += 2)
    {
        if (p % i == 0) return FALSE;
    }       
    return TRUE;
}

long getNthTruncatablePrime(int nthTruncatable)
{
    unsigned int truncatableCounter = 0;
    long lastPrimes[520];
    long currentPrimes[520];
    long result;
    unsigned int mult, i, j;
    unsigned int lastPrimesSize, currentPrimesSize;

    lastPrimes[0] = 2;
    lastPrimes[1] = 3;
    lastPrimes[2] = 5;
    lastPrimes[3] = 7;
    lastPrimesSize = 4;
    currentPrimesSize = 0;

    /* trivial case: when asking for first 4 truncatable primes (i.e. first 4 primes) */
    if (nthTruncatable < 5) return lastPrimes[nthTruncatable-1];

    truncatableCounter = 4;    
    /* iterate in powers of 10 (10, 100, 1000, 10000, ...) */
    for (mult = 10; mult < MAX_SEARCH_POW; mult *= 10)
    {
        /* iterate over that power (10s in 100s, 100s in 1000s) */
        for (i = 1; i <= 9; ++i)
        {
            /* construct new truncatable primes from previous truncatable primes */
            for (j = 0; j < lastPrimesSize; ++j)
            {
                result = mult*i + lastPrimes[j];

                if (isPrime(result))
                {
                    if(++truncatableCounter == nthTruncatable)
                    {
                    	return result;	
                    }
                    
                    currentPrimes[currentPrimesSize++] = result;
                }
            }
        }
        cpyVector(lastPrimes, currentPrimes, &lastPrimesSize, currentPrimesSize);
        currentPrimesSize = 0;
    }
    return -1;	/* should never get here */
}

int main (int argc, char** argv)
{
	unsigned short input;
	size_t i;
	int msec;

	clock_t start = clock(), diff;

	if (argc != NUM_ARGS)
	{
		printf("Wrong use of %s\n", PRG_NAME);
		printHelp(PRG_NAME);
		return EXIT_FAILURE;
	}

	if (strcmp(INPUT_PARAM, PARAM_HELP) == 0)
	{
		printHelp(PRG_NAME);
		return EXIT_SUCCESS;
	}
		
	/* Parsing input */
	input = atoi(INPUT_PARAM);
	if (!input || input > MAX_INPUT_NUM)
	{
		printf("Invalid input argument.");
		printHelp(PRG_NAME);
	}

	/* Normal program flow (input is already a valid num) */
	printf("%li\n", getNthTruncatablePrime(input));

	diff = clock() - start;
	msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

	return EXIT_SUCCESS;
}
