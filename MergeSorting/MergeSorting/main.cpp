#include "mainFunctions.hpp"

int main() {
    
    string originalF = "originalF.txt";
    
    unsigned long filesize;
    cout << "Filesize is (megabytes) "; cin >> filesize;
    cout << endl;
    
    filesize *= 1000000;
    
    int fileNums = Generating(originalF, filesize);
    
    clock_t startTime = clock();
    for (int i = 1; i <= fileNums; i++)
    {
        string filename = to_string(i) + ".txt";
        SortOneFile(filename);
    }
    
    MergeAllFiles(fileNums);
    clock_t endTime = clock();
    cout << "Merge sorting time = " << (endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    
    return 0;
}
