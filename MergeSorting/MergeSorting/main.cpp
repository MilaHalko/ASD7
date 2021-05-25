#include "mainFunctions.hpp"

int main() {
    
    //GENERATING_FILES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    string originalF = "originalF.txt";
    
    long filesize;
    cout << "Filesize is (megabytes) "; cin >> filesize; cout << endl;
    filesize *= 1000000;
    long allNums = filesize / 4;
    int filesQuantity;
    
    if (allNums % maxNums != 0) {filesQuantity = int(allNums / maxNums) + 1;}
    else { filesQuantity = int(allNums / maxNums);}
    
    Generating(originalF, allNums);
    
    //SORTING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    clock_t startTime = clock();
    
    MakingFiles(originalF, filesQuantity, filesize);
        
    MergeAllFiles(filesQuantity, filesize);
    
    clock_t endTime = clock();
    cout << "Merge sorting time = " << (endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    
    return 0;
}
