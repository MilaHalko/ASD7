#include "mainFunctions.hpp"

void Generating(string filename, long allNums)
{
    clock_t startTime = clock();
    ofstream foutText ("OriginalStandart.txt");
    ofstream fout(filename, ios::binary);
    
    if (!fout)  cout << "Error (" << filename << "- fout)!" << endl;
    else
    {
        srand((time(0)));
        for (int i = 0; i < allNums; i++) {
            int number = rand() % 1000;
            fout.write((char*) &(number), 4);
            foutText << number << " ";
        }
    }
    foutText.close();
    fout.close();
    
    clock_t endTime = clock();
    cout << "Generating files time = " << ((endTime - startTime) / CLOCKS_PER_SEC) << " seconds"<< endl;
}


void MakingFiles (string originalF, int filesQuantity, long fileSize)
{
    ifstream finOriginal (originalF, ios::binary);
    string fileName;
    long size = maxSize;
    
    for (int i = 1; i <= filesQuantity; i++) {
        fileName = to_string(i) + ".txt";
        ofstream foutCurrent (fileName, ios::binary);
        
        if (i == filesQuantity  &&  fileSize % maxSize)
            size = fileSize % maxSize;
        
        char* buffer = new char [size];
        buffer[size - 1] = 0;
        finOriginal.read(buffer, size);
        foutCurrent.write(buffer, size);
        foutCurrent.close();
        delete [] buffer;
        SortOneFile(fileName);
    }
    finOriginal.close();
}


void SortOneFile(string filename)
{
    ifstream fin (filename, ios::binary);
    vector<int> nums;
    nums.resize(0);
    int number;
    
    while (fin.read((char*)&number, 4))
        nums.push_back(number);
    
    fin.close();
    
    MergeSorting(nums, 0, nums.size() - 1);
    
    ofstream fout (filename, ios::binary);
    
    for (int i = 0; i < nums.size(); i++)
        fout.write((char*)&nums[i], 4);
    
    fout.close();
    nums.clear();
}


void MergeSorting(vector<int> &nums, int l, int r)
{
    int m = (l + r) / 2;
    
    if (l < r)
    {
        MergeSorting(nums, l, m);
        MergeSorting(nums, m + 1, r);
    }
    
    int currentL = l;
    int currentR = m + 1;
    vector<int> subVec;
    subVec.resize(0);
    
    for (int i = l; i <= r; i++)  // Sorting (merging process)
    {
        if (currentL <= m  &&  (currentR > r  ||  (nums[currentL] < nums[currentR])))
        {
            subVec.push_back(nums[currentL]);
            currentL++;
        }
        else
        {
            subVec.push_back(nums[currentR]);
            currentR++;
        }
    }
    
    int counter = 0;
    for (int i = l; i <= r; i++)
    {
        nums[i] = subVec[counter];
        counter++;
    }
    subVec.clear();
}


void MergeAllFiles(int filesNums, long filesize)
{
    long maxsize = filesize % maxSize;
    for (int i = filesNums - 1; i > 0; i--)
    {
        string first = to_string(i) + ".txt";
        string second = to_string(i + 1) + ".txt";
        MergeTwoFiles(first, second, maxsize);
        maxsize = maxSize;
    }
    
    ofstream finalF ("final.txt");
    ifstream fin ("1.txt", ios::binary);
    int number;
    
    while (fin.read((char*)&number, 4))
        finalF << number << " ";
    
    fin.close();
    finalF.close();
    __fs::filesystem::remove("1.txt");
    
}


void MergeTwoFiles(string firstSTR, string secondSTR, long maxsize)
{
    string subSTR = "Sub.txt";

    ifstream fin (firstSTR, ios::binary);
    ifstream fin2 (secondSTR, ios::binary);
    ofstream sub (subSTR, ios::binary);
    
    if (!fin  ||  !fin2  ||  !sub)
        cout << "Error!" << endl;
    else {
        int currentFirst;
        int currentSec;
        
        bool newFirst = true;
        bool newSec = true;
        
        bool stopFirst = false;
        bool stopSec = false;
        
        while (true)
        {
            if (newFirst)
            {
                if (fin.read((char*)&currentFirst, 4))
                    newFirst = false;
                else {
                    stopFirst = true;
                    newFirst = false;
                }
            }
                
            if (newSec)
            {
                if (fin2.read((char*)&currentSec, 4))
                    newSec = false;
                else {
                    stopSec = true;
                    newSec = false;
                }
            }
            
            
            if (stopFirst  &&  stopSec)
                break;
            else
            {
                if (!stopFirst  &&  (stopSec  ||  currentFirst < currentSec))
                {
                    sub.write((char*)&currentFirst, 4);
                    newFirst = true;
                }
                else
                {
                    sub.write((char*)&currentSec, 4);
                    newSec = true;
                }
            }
        }
        
        fin.close();
        fin2.close();
        sub.close();
        __fs::filesystem::remove(secondSTR);
        
        ofstream fout (firstSTR, ios::binary);
        ifstream sub2 (subSTR,ios::binary);
        int number;
        
        while (sub2.read((char*)&number, 4))
            fout.write((char*)&number, 4);
        
        fout.close();
        sub2.close();
        __fs::filesystem::remove(subSTR);
    }
}
