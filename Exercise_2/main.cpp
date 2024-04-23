#include <iostream>
#include <fstream>
#include <sstream>
#include "Utils.hpp"

using namespace std;


int main()
{
    string inputFilePath = "./data.csv";
    double S = 0.00;
    size_t n = 0;
    double* w = nullptr;
    double* r = nullptr;

    if (!ImportData(inputFilePath, S, n, w, r))
    {
        cerr<< "It was not possible to import data from the file."<< endl;
        return -1;
    }


    double rateOfReturn;
    double V;
    ComputeRor(S, n, w, r, rateOfReturn, V);

    ExportData(cout, S, n, w, r, rateOfReturn, V);  // stampa sul terminale: outobject = cout

    string outputFilePath = "./result.txt";         // stampa sul file "result.txt"
    ofstream file;
    file.open(outputFilePath);

    if (file.fail())
    {
        cerr << "It was not possibe to open the export file." << endl;
        return -1;
    }

    ExportData(file, S, n, w, r, rateOfReturn, V);   // stampa su file: outobject = file
    file.close();

    delete[] w;
    delete[] r;


    return 0;
}

