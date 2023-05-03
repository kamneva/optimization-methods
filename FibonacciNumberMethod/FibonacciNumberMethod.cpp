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

int fib(int n)
{
    if (n < 2)
        return 1;
    return fib(n - 2) + fib(n - 1);
}

int findMinFib(double a, double b)
{
    int num = 0;
    double div = fabs(a - b) / eps;

    while (fib(num) < div)
    {
        cout << "F_" << num << " = " << fib(num) << ";  N = " << num << "   =>   F_N < |L_0| / l" << endl;
        num++;
    }
    cout << "F_" << num << " = " << fib(num) << ";  N = " << num << "   =>   F_N >= |L_0| / l" << endl;
    return num;
}

double MethFib(double a, double b)
{
    cout << "_________________________" << endl;
    cout << "Метод Фибоначчи" << endl;
    int k = 0;

    double x;
    double L = fabs(b - a);
    cout << "l = eps = 0.001" << endl;
    cout << "|L_0| = " << L << ";   |L_0| / l = " << L / eps << endl;
    int N = findMinFib(a, b);
    cout << "\n---- Шаг " << k << " ----" << endl;

    double y = a + (b - a) * fib(N - 2) / fib(N);
    double z = a + (b - a) * fib(N - 1) / fib(N);

    cout << "y_" << k << " = a_" << k << " + F_" << N - 2 << " / F_" << N << " * (b_" << k << " - a_" << k << ") = " << y << endl;
    cout << "z_" << k << " = a_" << k << " + F_" << N - 1 << " / F_" << N << " * (b_" << k << " - a_" << k << ") = " << z << endl;

    while (true)
    {
        if (k != 0)
            cout << "\n---- Шаг " << k << " ----" << endl;

        double fy = f(y);
        double fz = f(z);

        cout << "f(y_" << k << ") = " << fy;
        cout << ";  f(z_" << k << ") = " << fz << endl;

        if (k != N - 3)
        {
            if (fy <= fz)
            {
                cout << "f(y_" << k << ") <= f(z_" << k << ")" << endl;
                a = a;
                b = z;
                z = y;
                y = a + (b - a) * fib(N - k - 3) / fib(N - k - 1);
            }
            else {
                cout << "f(y_" << k << ") > f(z_" << k << ")" << endl;
                a = y;
                b = b;
                y = z;
                z = a + (b - a) * fib(N - k - 2) / fib(N - k - 1);
            }
            cout << "a_" << k + 1 << " = " << a;
            cout << ";  b_" << k + 1 << " = " << b;
            cout << ";  y_" << k + 1 << " = " << y;
            cout << ";  z_" << k + 1 << " = " << z << endl;
        }
        if (k == N - 3)
        {
            cout << "k = " << k << " = N - 3" << endl;
            y = (a + b) / 2;
            z = y + eps;
            cout << "y_" << N - 2 << " = " << y;
            cout << ";  z_" << N - 2 << " = " << y << endl;
            cout << "y_" << N - 1 << " = " << y;
            cout << ";  z_" << N - 1 << " = " << z << endl;

            fy = f(y);
            fz = f(z);

            cout << "f(y_" << N - 1 << ") = " << fy;
            cout << ";  f(z_" << N - 1 << ") = " << fz << endl;

            if (fy <= fz)
            {
                cout << "f(y_" << N - 1 << ") <= f(z_" << N - 1 << ")" << endl;
                a = a;
                b = z;
            }
            else
            {
                cout << "f(y_" << N - 1 << ") > f(z_" << N - 1 << ")" << endl;
                a = y;
                b = b;
            }
            cout << "a_" << N - 1 << " = " << a;
            cout << ";  b_" << N - 1 << " = " << b << endl;
            x = (a + b) / 2;
            double fx = f(x);
            break;
        }
        else
        {
            k++;
        }
    }

    cout << "\n ---ОТВЕТ--- \nx* = [" << a << "; " << b << "]" << "\nx*: " << x << endl;
    cout << "f(x*): " << f(x) << endl;
    cout << "Конечное число шагов: " << k << endl;
    cout << "N: " << N << ";   F_N: " << fib(N) << endl;
    return x;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    double a = -1, b = 1;
    cout << "\tf(x) = x^3 + 3*x^2 - 2" << endl;
    cout << "\tL_0 = [a_0; b_0] = [" << a << ";" << b << "]" << endl;
    cout << "\teps = 0.001" << endl;

    MethFib(a, b);

    return 1;
}
