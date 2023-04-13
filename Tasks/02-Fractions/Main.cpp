#include "Fraction.h"

#include <iostream>

using namespace std; 

int main()
{
    Fraction f1(1, 2);        // 1/2
    Fraction f2(3, 4);        // 3/4
    Fraction result;

    result = f1 + f2;      // 1/2 + 3/4 = 10/8
    result.Simplify();
    cout << "1/2 + 3/4 = " << result << endl;

    result = f2 - f1; // 3/4 - 1/2 = 2/8
    result.Simplify();
    cout << "3/4 - 1/2 = " << result << endl;

    result = f2 * 3;  // 3/4 * 3 = 9/4
    result.Simplify();
    cout << "3/4 * 3 = " << result << endl;

    Fraction f3;
    cin >> f3;             // input format is up to you, e.g. "1 2" to represent 1/2
    f3.Simplify();
    cout << "Read = " << f3 << endl;
}