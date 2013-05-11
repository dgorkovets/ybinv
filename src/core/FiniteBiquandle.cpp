#include <algorithm>
#include <functional>
#include "FiniteBiquandle.h"
#include "mathutils.h"

const static pair<int,int> FiniteBiquandle::_checkPairForFixedComponent::NO_PAIR= make_pair(-1, -1);
const static pair<int,int> FiniteBiquandle::_checkPairForFixedComponent::BAD_PAIR = make_pair(-2, -2);

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
    //transform(range.begin(), range(end), back_inserter(bad_pairs), _checkPairForFixedComponent());
    bool isCorrect = true;

    for (int i = 0; i < size(); ++i)
    {
        set<int> seconds;
        for (int j = 0; j < size(); ++j)
        {
            if (op1(i, j) == i && op2(i, j) == j)
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
            bad_pairs.push_back(make_pair(i, *seconds.rend());
        }
    }
    // (BxId)(IdxB)(BxId) = (IdxB)(BxId)(IdxB)

    return isCorrect;
}

int FiniteBiquandle::op1(int x, int y) const
{
    return op.at(y)(x);
}

int FiniteBiquandle::op2(int x, int y) const
{
    return op.at(x + size())(y);
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
