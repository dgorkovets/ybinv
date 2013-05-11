#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <ostream>
#include <vector>
#include <map>
using namespace std;

class Permutation
{
    int m_size;
    vector<int> m_content;
    struct _outter
    { 
        ostream &os;
        _outter(ostream &os) : os(os){}
        void operator()(int i){ os << " " << i; }
    };

    struct _enumerator
    {
        int elem;
        _enumerator() : elem(0) {}
        int operator()() { return elem++; }
    };

    void construct_steps(long index, vector<int>& rest_elements, vector<int>& result);

public:
    Permutation(int size, long index = -1);
    void construct(long index);
    int operator()(int index) const;
    friend ostream& operator<<(ostream &os, const Permutation &perm);
};

ostream& operator<<(ostream &os, const Permutation &perm);

class PermutationFactory
{

    // permutation size -> set of all permutations of such size
    map<int, vector<Permutation> > permutations;

    static PermutationFactory& getInstance();

    struct _perm_generator
    {
        int _size;
        int index;
        _perm_generator(int size) : _size(size), index(0) {}
        Permutation operator()() { return Permutation(_size, index++); }
    };

    PermutationFactory() {}

public:

    static const vector<Permutation>& ofSize(int size);
    static const Permutation& getPermutation(int size, long index);
    static const Permutation& getIdentityPermutation(int size);
};

#endif
