#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void CreateDataFile(const string& fname) {
    ofstream fout(fname, ios::binary); 

    cout << "Enter numbers :\n";
    int num;
    while (true) {
        cin >> num;
        if (cin.get() == '\n') break; 
        fout.write(reinterpret_cast<const char*>(&num), sizeof(num)); 
    }

    fout.close(); 
}
double CalculateAverage(const string& fname) {
    ifstream fin(fname, ios::binary); 
    if (!fin.is_open()) {
        cout << "Error: Unable to open file for reading." << endl;
        return 0.0;
    }

    int num;
    int sum = 0;
    int count = 0;
    while (fin.read(reinterpret_cast<char*>(&num), sizeof(num))) { 
        sum += num; 
        count++; 
    }

    fin.close(); 

    if (count == 0) return 0.0; 

    return static_cast<double>(sum) / count; 
}

void FindMinMax(const string& fname, int& maxNum, int& minNum) {
    ifstream fin(fname, ios::binary); 
    if (!fin.is_open()) {
        cout << "Error: Unable to open file for reading." << endl;
        return;
    }

    int num;
    fin.read(reinterpret_cast<char*>(&num), sizeof(num)); 
    maxNum = num;
    minNum = num;

    while (fin.read(reinterpret_cast<char*>(&num), sizeof(num))) { 
        if (num > maxNum) maxNum = num; 
        if (num < minNum) minNum = num; 
    }

    fin.close(); 
}

int main() {
    string inputFileName, outputFileName;
    cout << "Enter input file name: ";
    cin >> inputFileName;

    
    CreateDataFile(inputFileName);


    cout << "Enter output file name: ";
    cin >> outputFileName;

    double averageAll = CalculateAverage(inputFileName);


    int maxNum, minNum;
    FindMinMax(inputFileName, maxNum, minNum);

    double averageMinMax = (maxNum + minNum) / 2.0;

    ofstream fout(outputFileName, ios::binary);
    fout.write(reinterpret_cast<const char*>(&averageMinMax), sizeof(averageMinMax));
    fout.write(reinterpret_cast<const char*>(&averageAll), sizeof(averageAll));
    fout.close();

    cout << "Results have been saved in " << outputFileName << ":" << endl;
    ifstream fin(outputFileName, ios::binary);
    double result;
    cout << "Average of max and min components: ";
    fin.read(reinterpret_cast<char*>(&result), sizeof(result));
    cout << result << endl;

    cout << "Average of all components: ";
    fin.read(reinterpret_cast<char*>(&result), sizeof(result));
    cout << result << endl;

    fin.close();

    return 0;
}
