#include "BiquandleGenerator.h"
#include "FiniteBiquandle.h"
#include "mathutils.h"

BiquandleGenerator::BiquandleGenerator(int size) : m_size(size) 
{
}

void BiquandleGenerator::generate()
{
    Nary number(fact(m_size), 2 * m_size);
    FiniteBiquandle bq(m_size);
    number.setValue(index);
    bq.setPermutationIndices(number.getValue());

}
