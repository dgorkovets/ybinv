#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include "FiniteBiquandle.h"
#include "mathutils.h"


FiniteBiquandle::FiniteBiquandle(int size)
{
    init(size);
}

triple_int FiniteBiquandle::_S1(triple_int x) const
{
    return triple_int(op1(x.first, x.second), op2(x.first, x.second), x.third);
}

triple_int FiniteBiquandle::_S2(triple_int x) const
{
    return triple_int(x.first, op1(x.second, x.third), op2(x.second, x.third));
}

void FiniteBiquandle::init(int size)
{
    order = size;
    setupOperation(0);
}

int FiniteBiquandle::size() const
{
    return order;
}

void FiniteBiquandle::setupOperation(int index)
{
    Nary number(fact(size()), 2 * size());
    number.setValue(index);
    const vector<int>& indices = number.getValue(); 
    op.clear();
    transform(indices.begin(), indices.end(), back_inserter(op), GetPermutationByIndex(size())); 
}

bool FiniteBiquandle::isOperationCorrect() const
{
    // B(x,y) = (x,y)
    const vector<int>& range = Range::get(size());
    vector<pair<int,int> > bad_pairs;
    bool isCorrect = true;

    for (int i = 0; i < size(); ++i)
    {
        set<int> seconds;
        for (int j = 0; j < size(); ++j)
        {
            if (op1(j, i) == j && op2(j, i) == i)
            {
                seconds.insert(j);
            }
        }
        if (seconds.empty())
        {
            isCorrect = false;
        }
        else if (seconds.size() > 1)
        {
            isCorrect = false;
            bad_pairs.push_back(make_pair(i, *seconds.rend()));
        }
    }

    // (BxId)(IdxB)(BxId) = (IdxB)(BxId)(IdxB)
    for (int i = 0; i < size(); ++i)
    {
        for (int j = 0; j < size(); ++j)
        {
            for (int k = 0; k < size(); ++k)
            {
                triple_int t(i,j,k);
                if (_S1(_S2(_S1(t))) != _S2(_S1(_S2(t))))
                {
                    return false;
                }
            }
        }
    }

    return isCorrect;
}

int FiniteBiquandle::op1(int x, int y) const
{
    return op.at(x)(y);
}

int FiniteBiquandle::op2(int x, int y) const
{
    return op.at(y + size())(x);
}

ostream& operator<<(ostream &os, const FiniteBiquandle &bq)
{
    os << "op1: " << endl;
    for_each(bq.op.begin(), bq.op.begin() + bq.size(), FiniteBiquandle::_op_printer(os));
    os << endl;
    os << "op2: " << endl;
    for_each(bq.op.begin() + bq.size(), bq.op.end(), FiniteBiquandle::_op_printer(os));

    return os;
}
