#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

const unsigned int maxNums = 160000000;  //160000000;     // (8qb * 1000mb * 1000000b) 8гб в байтах  -> (/ 100% * 8%) 8% от 8гб  ==  640 000 000  / 4(int)
const unsigned int maxSize = 640000000;
