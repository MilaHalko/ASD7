#include "mainFunctions.hpp"

int Generating(string filename, int bitesSize)
{
    clock_t startTime = clock();
    
    unsigned long size = 0;
    int fileNum = 1;
    ofstream fout(filename);
    
    if (!fout)  cout << "Error (" << filename << "- fout)!" << endl;
    else
    {
        srand((time(0)));
        string filename;
        
        while (size <= bitesSize)
        {
            int subsize = 0;
            
            filename = to_string(fileNum) + ".txt";
            ofstream foutSmall (filename);
            
            while (foutSmall.is_open())
            {
                int number = rand() % 1000;
                fout << number <<  " ";
                foutSmall << number << endl;
                
                size += to_string(number).size() + 1;
                subsize += to_string(number).size() + 1;
                
                if (subsize >= maxSize  ||  size >= bitesSize)
                {
                    foutSmall.close();
                    fileNum++;
                }
            }
        }
    }
    fout.close();
    
    clock_t endTime = clock();
    cout << "Generating files time = " << ((endTime - startTime) / CLOCKS_PER_SEC) << " seconds"<< endl;
    
    cout << "The size (bytes) is " << size << "." << endl;
    
    return --fileNum;
}

void SortOneFile(string filename)
{
    ifstream fin (filename);
    
    if (!fin)  cout << "Error (" << filename << "- fin)!" << endl;
    else
    {
        string str = "1";
        vector<int> nums;
        nums.resize(0);
        
        while (str != "")
        {
            str = "";
            getline(fin, str);
            
            if (str != "")  nums.push_back(stoi(str));
        }
        fin.close();
        
        MergeSorting(nums, 0, nums.size() - 1);
        
        ofstream fout (filename);
        
        for (int i = 0; i < nums.size(); i++)
            fout << nums[i] << endl;
        
        nums.clear();
    }
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

void MergeAllFiles(int filesNums)
{
    int counter;
    int gap = 1;
    do
    {
        counter = 0;
        
        for (int i = 1; i + gap <= filesNums; i += 2 * gap)
        {
            counter++;
            string first = to_string(i) + ".txt";
            string second = to_string(i + gap) + ".txt";
            MergeTwoFiles(first, second);
        }
        gap *= 2;
    } while (counter != 0);
    
    ofstream fout ("final.txt");
    ifstream fin ("1.txt");
    
    string str = "1";
    
    while (str != "")
    {
        str = "";
        getline(fin, str);
        fout << str << " ";
    }
    
    fout.close();
    fin.close();
    __fs::filesystem::remove("1.txt");
    
}


void MergeTwoFiles(string firstSTR, string secondSTR)
{
    string subSTR = "Sub.txt";

    ifstream fin (firstSTR);
    ifstream fin2 (secondSTR);
    ofstream sub (subSTR);
    
    if (!fin  ||  !fin2  ||  !sub)
        cout << "Error!" << endl;
    
    string currentFirst;
    string currentSec;
    
    bool newFirst = true;
    bool newSec = true;
    
    while (true)
    {
        if (newFirst)
        {
            currentFirst = "";
            getline(fin, currentFirst);
            newFirst = false;
        }
            
        if (newSec)
        {
            currentSec = "";
            getline(fin2, currentSec);
            newSec = false;
        }
        
        
        if (currentFirst == ""  &&  currentSec == "")  break;
        else
        {
            if (currentFirst != ""  &&  (currentSec == ""  ||  stoi(currentFirst) < stoi(currentSec)))
            {
                sub << currentFirst << endl;
                newFirst = true;
            }
            else
            {
                sub << currentSec << endl;
                newSec = true;
            }
        }
    }
    
    fin.close();
    fin2.close();
    sub.close();
    __fs::filesystem::remove(secondSTR);
    
    ofstream fout (firstSTR);
    ifstream sub2 (subSTR);
    
    string str = "1";
    
    while (str != "")
    {
        str = "";
        getline(sub2, str);
        fout << str << endl;
    }
    
    fout.close();
    sub2.close();
    __fs::filesystem::remove(subSTR);
}
