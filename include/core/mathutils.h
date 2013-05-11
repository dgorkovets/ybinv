#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <vector>
#include <map>

#define NARY_LAST_POS -2
#define NARY_JUST_INCREMENT -1

using namespace std;

int fact(int n);


class Nary
{
    int base;
    int digitcount;
    vector<int> value;

    void _setValueStep(vector<int>& accum, int newvalue);

public:

    Nary(int base, int digitcount = -1);
    void setValue(int newvalue);
    const vector<int>& getValue() const;
    bool next(int pos = NARY_LAST_POS, int newvalue = NARY_JUST_INCREMENT);

};

class Range
{
    map<int, vector<int> > ranges;

    Range() {}
    static Range& getInstance();

    struct _generator
    {
        int current;
        _generator() : current(0) {}
        int operator()() { return current++; }
    };

public:
    
    static const vector<int>& get(int size);

};


#endif
