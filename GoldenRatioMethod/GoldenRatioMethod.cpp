#include <iostream>
#include <cmath>
using namespace std;
#define eps 0.001

double f(double x)
{
    double x1 = x;
    double f;
    f = (pow(x1, 3) + 3 * pow(x1, 2) - 2);
    return f;
}

double Gold(double a, double b)
{
    cout << "_________________________" << endl;
    cout << "Метод «золотого сечения»" << endl;

    double delta = fabs(a - b);
    double x;

    int k = 0;

    double y = a + (b - a) * (3 - sqrt(5)) / 2;
    double z = a + b - y;

    cout << "\n---- Шаг " << k << " ----" << endl;
    cout << "delta = |b_" << k << " - a_" << k << "| = " << delta << "   =>   delta > eps" << endl;
    cout << "y_" << k << " = a_" << k << " + (3-sqrt(5)) / 2 * (b_" << k << " - a_" << k << ") = " << y << endl;
    cout << "z_" << k << " = a_" << k << "+ b_" << k << " - y_" << k << " = " << z << endl;

    while (delta > eps)
    {
        if (k != 0)
            cout << "\n---- Шаг " << k << " ----" << endl;

        double fy = f(y);
        double fz = f(z);

        cout << "f(y_" << k << ") = " << fy;
        cout << ";  f(z_" << k << ") = " << fz << endl;

        if (fy <= fz)
        {
            cout << "f(y_" << k << ") <= f(z_" << k << ")" << endl;
            a = a;
            b = z;
            z = y;
            y = a + b - y;
        }
        else {
            cout << "f(y_" << k << ") > f(z_" << k << ")" << endl;
            a = y;
            b = b;
            y = z;
            z = a + b - z;
        }
        cout << "a_" << k + 1 << " = " << a;
        cout << ";  b_" << k + 1 << " = " << b;
        cout << ";  y_" << k + 1 << " = " << y;
        cout << ";  z_" << k + 1 << " = " << z << endl;
        delta = fabs(a - b);
        if (delta > eps)
            cout << "delta = " << delta << "   =>   delta > eps" << endl;
        k++;
    }
    cout << "delta = " << delta << "   =>   delta < eps" << endl;
    x = (a + b) / 2;

    cout << "\n ---ОТВЕТ--- \nx*: " << x << endl;
    cout << "f(x*): " << f(x) << endl;
    cout << "Конечное число шагов: " << k << endl;

    return x;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    double a = -1, b = 1;
    cout << "\tf(x) = x^3 + 3*x^2 - 2" << endl;
    cout << "\tL_0 = [a_0; b_0] = [" << a << ";" << b << "]" << endl;
    cout << "\teps = 0.001" << endl;

    Gold(a, b);

    return 1;
}
