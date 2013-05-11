#ifndef PRINTER_H
#define PRINTER_H

#include <algorithm>
#include <ostream>
#include <vector>

using namespace std;

class VectorPrinter
{
    template<typename T>
    struct _elem_outter
    { 
        ostream &os;
        _elem_outter(ostream &os) : os(os){}
        void operator()(T e){ os << " " << e; }
    };

public:
    
    template<typename T>
    static void print(ostream &os, const vector<T>& value)
    {
        for_each(value.begin(), value.end(), _elem_outter<T>(os));
    }
};

ostream& operator<<(ostream &os, const vector<int>& value); 

#endif

