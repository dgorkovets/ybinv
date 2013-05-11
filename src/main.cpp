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
    int counter = 0;
    long all = pow(fact(n),2*n);
    cout << all << endl;
    for (int i = 0; i < all; i++)
    {
        bq.setupOperation(i);
        if (bq.isOperationCorrect())
        {
            counter++;
        }
    }
    cout << counter << endl;

    return 0;
}
