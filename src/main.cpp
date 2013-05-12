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
    long all = pow(fact(n), 2*n);
    cout << all << endl;
    int i = 0;
    while (i < 1000000)
    {
        cout << i << " of " << all << endl;
        bq.setupOperation(i);
        if (bq.isOperationCorrect())
        {
            counter++;
            i++;
        }
        else
        {
            
        }
    }
    cout << counter << endl;

    return 0;
}
