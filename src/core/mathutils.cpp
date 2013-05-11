#include <numeric>
#include <algorithm>
#include "mathutils.h"

int fact(int n)
{
    static int fact[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 
                         362880, 3628800, 39916800, 479001600};
    return fact[n];
}

Nary::Nary(int base, int digitcount) : 
    base(base), 
    digitcount(digitcount)
{
    setValue(0);
}

void Nary::_setValueStep(vector<int>& accum, int newvalue)
{
    if (newvalue > 0)
    {
        accum.insert(accum.begin(), newvalue % base);
        _setValueStep(accum, newvalue / base);
    }

    accum.insert(accum.begin(), digitcount - accum.size(), 0);
}

void Nary::setValue(int newvalue)
{
    value.clear();
    _setValueStep(value, newvalue);
}

const vector<int>& Nary::getValue() const
{
    return value;
}

bool Nary::next(int pos, int position_value)
{
    if (pos == -1 || position_value < -1 || position_value > base)
    {
        return false;
    }

    if (pos == NARY_LAST_POS)
    {
        pos = digitcount - 1;
    }

    fill(value.begin() + pos + 1, value.end(), 0);

    if (position_value == NARY_JUST_INCREMENT)
    {
        value.at(pos)++;
    }
    else
    {
        value.at(pos) = position_value;
    }

    if(value.at(pos) == base)
    {
        return next(pos - 1);
    }

    return true;
}

Range& Range::getInstance()
{
    static Range range;
    return range;
}

const vector<int>& Range::get(int size)
{
    Range &r = getInstance();
    if (r.ranges.find(size) == r.ranges.end())
    {
        vector<int>& newrange = r.ranges[size];
        newrange.resize(size);
        generate(newrange.begin(), newrange.end(), _generator());
    }

    return r.ranges[size];
}

