#ifndef FINITEBIQUANDLE_H
#define FINITEBIQUANDLE_H


#include <vector>
#include <ostream>
#include "Permutation.h"
#include "utils.h"

using namespace std;

typedef triple<int, int, int> triple_int;

class FiniteBiquandle
{
    int order;
    vector<Permutation> op; // B: GxG -> GxG

    struct _op_printer
    {
        ostream& os;
        _op_printer(ostream &os) : os(os) {}
        void operator()(const Permutation& perm) { os << perm << endl; }
    };

    struct GetPermutationByIndex 
    {
        int perm_size;
        GetPermutationByIndex(int perm_size) : perm_size(perm_size) {}
        Permutation operator() (int index) {return PermutationFactory::getPermutation(perm_size, index); }
    };

    triple_int _S1(triple_int x) const; //!< S_1 = BxId;
    triple_int _S2(triple_int x) const; //!< S_2 = IdxB;

public:

    static const pair<int,int> BAD_YB_PAIR;
    static const pair<int,int> NO_FIXED_POINT_PAIR;

    FiniteBiquandle(int size);
    void init(int size);
    int size() const;

    // operation is 2*size permutations
    // represent "index" as size-ary number
    // and set appropriate permutations
    void setupOperation(int index);

    void setPermutationIndices(const vector<int>& indices);

    bool isOperationCorrect() const;
    vector<pair<int,int> > getBadPairs() const;

    int op1(int x, int y) const; // B_1
    int op2(int x, int y) const; // B_2

    friend ostream& operator<<(ostream &os, const FiniteBiquandle &bq);
};

ostream& operator<<(ostream &os, const FiniteBiquandle &bq);

#endif
