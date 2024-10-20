#include <iostream>
#include <iomanip>
using namespace std;
#include <unistd.h>					// getpid
#include "PRNG.h"

PRNG prng1, prng2, prng3;				// global, normally one generator for entire program
extern PRNG prng1;					// declaration to use prng1 in another translation unit
