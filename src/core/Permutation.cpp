#include <algorithm>
#include <iostream>
#include "Permutation.h"
#include "mathutils.h"

Permutation::Permutation(int size, long index) :
    m_size(size)
{
    if (index >= 0)
    {
        construct(index);
    }
}

void Permutation::construct_steps(long index, vector<int>& rest_elements, vector<int>& result)
{
    // see: http://www.duskyrobin.com/tpu/2004-06-00004.pdf
    if (rest_elements.size() > 1)
    {
        int t = result.size() + 1;
        long ntfact = fact(m_size - t);
        long k = (index + ntfact) / ntfact;
        index -= (k - 1) * ntfact;
        vector<int>::iterator elem = rest_elements.begin() + k - 1;
        result.push_back(*elem);
        rest_elements.erase(elem);
        construct_steps(index, rest_elements, result);
    }
    else
    {
        result.push_back(*rest_elements.begin());
    }
}

void Permutation::construct(long index)
{
    vector<int> initial_perm(m_size);
    m_content.clear();
    generate_n(initial_perm.begin(), m_size, _enumerator());
    construct_steps(index, initial_perm, m_content);
}

int Permutation::operator()(int index) const
{
    return m_content.at(index);
}

ostream& operator<<(ostream &os, const Permutation &perm)
{
    for_each(perm.m_content.begin(), perm.m_content.end(), Permutation::_outter(os));
    return os;
}


PermutationFactory& PermutationFactory::getInstance()
{
    static PermutationFactory factory;
    return factory;
}

const vector<Permutation>& PermutationFactory::ofSize(int size)
{
    map<int, vector<Permutation> >& perms = getInstance().permutations;
    map<int, vector<Permutation> >::iterator permset = perms.find(size);
    if (permset == perms.end())
    {
        vector<Permutation>& newset = perms[size];
        newset.resize(fact(size), Permutation(size));
        generate(newset.begin(), newset.end(), _perm_generator(size));
        permset = perms.find(size);
    }
    return permset->second;
}

const Permutation& PermutationFactory::getPermutation(int size, long index)
{
    return ofSize(size)[index];
}

const Permutation& PermutationFactory::getIdentityPermutation(int size)
{
    return getPermutation(size, 0);
}

vector<Permutation>::const_iterator PermutationFactory::nextOf(const Permutation& initialperm, int pos)
{
    const vector<Permutation>& permset = ofSize(initialperm.size());
    vector<Permutation>::const_iterator initPermIt = find(permset.begin(), permset.end(), initialperm);
    vector<Permutation>::const_iterator nextperm = find_if(initPermIt, permset.end(), FindFirstNotMatchAtPos(pos, initialperm(pos)));
    return nextperm;
}
