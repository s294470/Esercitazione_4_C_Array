#include "Utils.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

bool ImportData(const string& inputFilePath,
                double& S,
                size_t& n,
                double*& w,
                double*& r)
{
    ifstream file;
    file.open(inputFilePath);
    if(file.fail())
    {
        cerr<< "The file could not be opened correctly."<<endl;
        return false;
    }
    string weight;
    string rate;
    string line;
    string trashbin;
    istringstream issw;  // nomi di oggetti istringstream : iss+lettera significativa
    istringstream issr;
    int i = 1;

    while(!file.eof())   // facciamo il while perché dopo la riga 4 faccio tante operazioni tutte la stessa volta e perché altrimenti non posso sapere quando finisco il file
    {
        if(i==1)
        {
            getline(file,trashbin, ';'); // prima del ; ho S per indicare che dopo ; leggo il suo valore
            getline(file,line);
            istringstream isss;
            isss.str(line);
            isss >> S;
        }
        else if(i==2)
        {
            getline(file,trashbin, ';'); // prima del ; ho n per indicare che dopo ; leggo il suo valore
            getline(file,line);
            istringstream issn;
            issn.str(line);
            issn >> n;
            w = new double[n]; // ora che so la dimensione n posso creare i vettori
            r = new double[n];
        }

        else if(i==3) // la terza riga del file che leggo è intestazione
        {
            getline(file,trashbin);
        }
        else
        {
            getline(file,weight, ';');
            getline(file,rate);
            issw.str(weight);
            issr.str(rate);
            issw >> w[i-4]; //ogni riga avrà i-4 esima componente del vettore w
            issr >> r[i-4];
            issw.clear();
            issr.clear();
        }
        i = i+1;

    }

    file.close();
    return true;
}

void ComputeRor(const double& S,
                         const size_t& n,
                         const double* const& w,
                         const double* const& r,
                         double& rateOfReturn,
                         double& V)
{
    V=0;
    for (unsigned int i=0; i<n; i++)
        V += (1+r[i])*S*w[i]; //per ogni frazione w[i]*S ho il rate r[i], il valore totale si fa sommando
    rateOfReturn = (V/S)-1; //il rate of return è il numero t.c. V = (1+rateofreturn)*S
}


void ExportData(ostream& outobject,
                const double& S,
                const size_t& n,
                const double* const& w,
                const double* const& r,
                const double& rateOfReturn,
                const double& V)
{

    outobject << fixed<< showpoint << setprecision(2)<< "S = "<< S<< ", n = "<< n<< endl;

    outobject << "w = "<< ArrayToString(n,w)<< endl;

    outobject << "r = "<< ArrayToString(n,r)<< endl;

    outobject << fixed<< showpoint << setprecision(4)<< "Rate of return of the portfolio: "<< rateOfReturn<< endl;
    outobject << fixed<< showpoint << setprecision(2)<< "V: "<< V<< endl;

}


string ArrayToString(const size_t& n,
                     const double* const& v)
{

    ostringstream toString;
    toString << "[ ";
    for (unsigned int i = 0; i < n; i++)
        toString<< v[i]<< " ";
    toString << "]";

    return toString.str();

}
