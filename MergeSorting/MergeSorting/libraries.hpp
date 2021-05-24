#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

const unsigned int maxSize = 16000000;     // (8qb * 1000mb * 1000000b) 8гб в байтах  -> (/ 100% * 8%) 8% от 8гб  -> (/4) вес int  ==  160 000 000
