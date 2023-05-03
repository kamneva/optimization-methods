#include <iostream>
#include <cmath>
using namespace std;

#define eps 0.001
#define eps1 0.15
#define eps2 0.2

double f(double x1, double x2)
{
    double x = x1;
    double y = x2;
    double f;
    f = 2 * pow(x, 2) + 0.2 * x * y + 6 * pow(y, 2);
    return f;
}

double dfdx1(double x1, double x2)
{
    double x = x1;
    double y = x2;
    double f;
    f = 4 * x + 0.2 * y;
    return f;
}

double dfdx2(double x1, double x2)
{
    double x = x1;
    double y = x2;
    double f;
    f = 12 * y + 0.2 * x;
    return f;
}

double MethodGrad(double x1, double x2, double tk, int M)
{
    int k = 0;
    int kk = 0;
    cout << "_____________________________________________" << endl;
    cout << "Метод градиентного спуска с постоянным шагом" << endl;

    cout << "df(x) = (4 * x_1 + 0.2 * x_2; 12 * x_2 + 0.2 * x_1)^T" << endl;

    double a[2];
    double delta1, delta2;

    cout << "\n---- Шаг " << k << " ----" << endl;
    cout << "df(x^0) = (" << dfdx1(x1, x2) << "; " << dfdx2(x1, x2) << ")^T" << endl;

    double df;
    df = sqrt(pow(dfdx1(x1, x2), 2) + pow(dfdx2(x1, x2), 2));
    cout << "||df(x^0)|| = " << df << endl;

    double fx1, fx2;

    while (df >= eps1 && k < M)
    {
        if (k != 0) {
            cout << "\n---- Шаг " << k << " ----" << endl;
            df = sqrt(pow(dfdx1(x1, x2), 2) + pow(dfdx2(x1, x2), 2));
            cout << "||df(x^" << k << ")|| = " << df << endl;
        }
        cout << "||df(x^" << k << ")|| >= eps1   &&   k < " << M << endl;

    tryAgain:

        fx1 = f(x1, x2);

        a[0] = x1 - tk * dfdx1(x1, x2);
        a[1] = x2 - tk * dfdx2(x1, x2);
        delta1 = sqrt(pow(a[0] - x1, 2) + pow(a[1] - x2, 2));

        cout << "t_" << k << " = " << tk << endl;
        cout << "x^(" << k + 1 << ") = (" << x1 << "; " << x2 << ") - " << tk << " * (" << dfdx1(x1, x2) << "; " << dfdx2(x1, x2) << ") = (" << a[0] << ";" << a[1] << ")" << endl;

        fx2 = f(a[0], a[1]);
        cout << "f(x^" << k << ") =" << fx1 << endl;
        cout << "f(x^" << k + 1 << ") =" << fx2 << endl;

        delta2 = fabs(fx2 - fx1);

        if (fx2 - fx1 < 0)
        {
            cout << "f(x^" << k + 1 << ") - f(x^" << k << ") =" << fx2 - fx1 << " < 0" << endl;
            if (delta1 < eps2 && delta2 < eps2)
            {
                cout << "||x^" << k + 1 << "- x^" << k << "|| = " << delta1 << endl;
                cout << "|f(x^" << k + 1 << ") - f(x^" << k << ")| = " << delta2 << endl;
                cout << "||x^" << k + 1 << "- x^" << k << "|| < eps2   &&    |f(x^" << k + 1 << ") - f(x^" << k << ")| < eps2" << endl;
                if (k == kk + 1)
                    break;
                kk = k;
            }
        }
        else {
            cout << "f(x^" << k + 1 << ") - f(x^" << k << ") =" << fx2 - fx1 << " > 0" << endl;
            tk = tk / 2;
            goto tryAgain;
        }
        x1 = a[0];
        x2 = a[1];
        k = k + 1;
    }
    cout << "\n ---ОТВЕТ--- \nx*: (" << a[0] << ";" << a[1] << ")" << endl;
    cout << "f(x*): " << f(a[0], a[1]) << endl;
    cout << "Конечное число шагов: " << k + 1 << endl;
    return 0;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    double x1 = 0, x2 = 0.5, tk = 1, a1 = -1, b1 = 1;
    int M = 15;

    cout << fixed;
    cout.precision(4);
    cout << "\tf(x) = 2 * x_1^2 + 0.2 * x_1 * x_2 + 6 * x_2^2" << endl;
    cout << "\tx^0 = [0; 0.5] " << endl;
    cout << "\tM = " << M << endl;
    cout << "\teps1 = " << eps1 << endl;
    cout << "\teps2 = " << eps2 << endl;
    cout << "\tt_k = " << tk << endl;
    cout << "\tdf(x)/dx_1 = 4 * x_1 + 0.2 * x_2" << endl;
    cout << "\tdf(x)/dx_2 = 12 * x_2 + 0.2 * x_1" << endl;

    MethodGrad(x1, x2, tk, M);
    return 1;
}
