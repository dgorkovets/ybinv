#ifndef FINITEBIQUANDLE_H
#define FINITEBIQUANDLE_H


#include <vector>
#include <ostream>
#include "Permutation.h"
#include "utils.h"

using namespace std;

typedef triple<int, int, int> triple_int;
typedef int (*bqoper)(int,int); 

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

    struct _checkPairAsFixedPoint
    {
        int first;
        bool reversedOrder;
        _checkPairAsFixedPoint(bqoper op1, bqoper op2, int first, bool reversedOrder = false) : first(first), reversedOrder(reversedOrder) {}
        int operator()(int second) 
        { 
            if ((!reversedOrder && op1(first, second) == first && op2(first, second) == second)  ||
                (reversedOrder && op1(first, second) == first && op2(first, second) == second))
            { 
                return second; 
            }
        }
    };

    struct _checkPairForFixedComponent
    {
        int size;
        const static pair<int,int> NO_PAIR;
        const static pair<int,int> BAD_PAIR;
        _checkPairForFixedComponent(int size) : size(size) {}
        pair<int, int> operator()(int first)  
        { 
            const vector<int>& range = Range::get(size);
            vector<int> seconds;
            transform(range.begin(), range.end(), back_inserter(seconds), _checkPairAsFixedPoint(op1, op2, first));
            if (seconds.empty())
            {
                return NO_PAIR;
            }
            else if (seconds.size() == 1)
            {
                return GOOD_PAIR;
            }
            else
            {
                return make_pair(first, seconds.back());
            }
        }
    };

    triple_int _S1(triple_int x) const; //!< S_1 = BxId;
    triple_int _S2(triple_int x) const; //!< S_2 = IdxB;

public:

    FiniteBiquandle(int size);
    void init(int size);
    int size() const;

    // operation is 2*size permutations
    // represent "index" as size-ary number
    // and set appropriate permutations
    void setupOperation(int index);

    bool isOperationCorrect() const;

    int op1(int x, int y) const; // B_1
    int op2(int x, int y) const; // B_2

    friend ostream& operator<<(ostream &os, const FiniteBiquandle &bq);
};

ostream& operator<<(ostream &os, const FiniteBiquandle &bq);

#endif
