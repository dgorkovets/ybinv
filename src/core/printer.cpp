#include "printer.h"

ostream& operator<<(ostream &os, const vector<int>& value)
{
    VectorPrinter::print(os, value);
    return os;
}
