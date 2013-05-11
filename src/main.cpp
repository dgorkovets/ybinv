#include <algorithm>
#include <iostream>
#include <cmath>

#include "sqlite3.h"
#include "Permutation.h"
#include "FiniteBiquandle.h"
#include "mathutils.h"
#include "printer.h"


int main()
{
    int n = 4;
    FiniteBiquandle bq(n);
    bq.setupOperation(0);
    cout << bq << endl;

    const vector<int>& r = Range::get(10);
    cout << r << endl;

    return 0;
}
