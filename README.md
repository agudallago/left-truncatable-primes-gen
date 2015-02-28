# left-truncatable-primes-gen
A quite simple generator of left truncatable primes (http://en.wikipedia.org/wiki/Truncatable_prime). This was made as part of an exercise / job interview. It was written in old style ANSI C.

It can be compiled with GCC by simply executing:
gcc -o outputFile LeftTruncatablePrimeGetter.c -ansi -pedantic

The usage of the program is pretty simple and can be reminded by calling the program without arguments or with '--help'.

A simple example calling would be:
outputFile 100

And it would return:
5167

The output for test purposes is returned along with the time elapsed in program execution.
