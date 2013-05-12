#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include "FiniteBiquandle.h"
#include "mathutils.h"

const pair<int,int> FiniteBiquandle::BAD_YB_PAIR = make_pair(-1,-1);
const pair<int,int> FiniteBiquandle::NO_FIXED_POINT_PAIR = make_pair(-2,-2);

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
    setPermutationIndices(number.getValue());
}

void FiniteBiquandle::setPermutationIndices(const vector<int>& indices)
{
    op.clear();
    transform(indices.begin(), indices.end(), back_inserter(op), GetPermutationByIndex(size())); 
}

bool FiniteBiquandle::isOperationCorrect() const
{
    return getBadPairs().empty();
}

vector<pair<int,int> > FiniteBiquandle::getBadPairs() const
{
    // B(x,y) = (x,y)
    vector<pair<int,int> > bad_pairs;

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
            bad_pairs.push_back(NO_FIXED_POINT_PAIR);
        }
        else if (seconds.size() > 1)
        {
            bad_pairs.push_back(make_pair(*seconds.rend() + size(), i));
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
                    bad_pairs.push_back(BAD_YB_PAIR);
                }
            }
        }
    }

    return bad_pairs;
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
