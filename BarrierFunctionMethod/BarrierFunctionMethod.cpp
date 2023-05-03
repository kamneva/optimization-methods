#include <iostream>
#include <cmath>
using namespace std;

#define eps 0.01
#define eps1 0.2
#define eps2 0.2

double g(double x1, double x2)
{
    double x = x1;
    double y = x2;
    double g;
    g = 8 * x + y - 7;
    return g;
}

double f(double x1, double x2)
{
    double x = x1;
    double y = x2;
    double f;
    f = 6 * pow(x, 2) + pow(y, 2) - 5;
    return f;
}
double Fobr(double x1, double x2, double rk)
{
    double x = x1;
    double y = x2;
    double F;
    F = f(x, y) - rk / g(x, y);
    return F;
}

double Pobr(double x1, double x2, double rk)
{
    double x = x1;
    double y = x2;
    double P;
    P = -rk / g(x, y);
    return P;
}

double dFobrx1(double x1, double x2, double rk)
{
    double x = x1;
    double y = x2;
    double dFx1;
    dFx1 = 12 * x + 8 * rk / (pow(g(x, y), 2));
    return dFx1;
}

double dFobrx2(double x1, double x2, double rk)
{
    double x = x1;
    double y = x2;
    double dFx2;
    dFx2 = 2 * y + rk / (pow(g(x, y), 2));
    return dFx2;
}
double BarrierFunction(double x1, double x2, double rk, double C)
{
    int k = 0;
    int kk = 0;
    double _X;

    int M = 1000;
    double tk = 1;
    cout << "_____________________________________________" << endl;
    cout << "\tМетод барьерных функций" << endl;

    double Func, Pxr;

    Pxr = Pobr(x1, x2, rk);

    Func = Fobr(x1, x2, rk);

    cout << "dF(x,r^k) = (12 * x_1 + 8 * r^k / (8 * x_1 + x_2 - 7)^2; 2 * x_2 + r^k / (8 * x_1 + x_2 - 7)^2)^T" << endl;

    double a[2];
    double delta1, delta2;


    cout << "\n---- Шаг " << k << " ----" << endl;
    cout << "dF(x^0,r^0) = (" << dFobrx1(x1, x2, rk) << "; " << dFobrx2(x1, x2, rk) << ")^T" << endl;
    cout << "F(x^0,r^0) = f(x) - r^0 / g(x^0) = " << Func << endl;

    double df;
    df = sqrt(pow(dFobrx1(x1, x2, rk), 2) + pow(dFobrx2(x1, x2, rk), 2));
    cout << "||dF(x^0,r^0)|| = " << df << endl;
    cout << "P(x*(r^" << k << "),r^" << k << ") = " << Pxr << endl;

    double fx1, fx2;


    while (Pxr >= eps && df >= eps1 && k < M)
    {
        Func = Fobr(x1, x2, rk);
        cout << "F(x^" << k << ", r^" << k << ") = " << Func << endl;
        tk = 1;
        while (df >= eps1 && k < M)
        {
            if (k != 0) {
                cout << "\n---- Шаг " << k << " ----" << endl;

                cout << "||dF(x^" << k << ", r^" << k << ")|| = " << df << endl;
            }

            cout << "||dF(x^" << k << ", r^" << k << ")|| >= eps1   &&   k < " << M << endl;
            cout << "P(x*(r^" << k << "),r^" << k << ") = " << Pxr << " >= " << eps << "= eps " << endl;
            cout << "r^" << k << " = " << rk << endl;

        tryAgain:

            fx1 = Fobr(x1, x2, rk);

            a[0] = x1 - tk * dFobrx1(x1, x2, rk);
            a[1] = x2 - tk * dFobrx2(x1, x2, rk);
            delta1 = sqrt(pow(a[0] - x1, 2) + pow(a[1] - x2, 2));

            cout << "\nt_" << k << " = " << tk << endl;
            cout << "x^" << k << "(r^" << k << ")) = (" << x1 << "; " << x2 << ") - " << tk << " * (" << dFobrx1(x1, x2, rk) << "; " << dFobrx2(x1, x2, rk) << ") = (" << a[0] << ";" << a[1] << ")" << endl;
            // x1 = a[0];
            // x2 = a[1];

            fx2 = Fobr(a[0], a[1], rk);
            cout << "F(x^" << k << "(r^" << k << ")) = " << fx1;
            cout << "\tF(x^" << k + 1 << "(r^" << k << ")) = " << fx2 << endl;

            delta2 = fabs(fx2 - fx1);

            if (fx2 - fx1 <= 0)
            {
                cout << "F(x^" << k + 1 << "(r^" << k << ")) - F(x^" << k << "(r^" << k << ")) = " << fx2 - fx1 << " <= 0" << endl;
                if (delta1 < eps2 && delta2 < eps2)
                {
                    cout << "||x^" << k + 1 << "(r^" << k << ")) - x^" << k << "(r^" << k << "))|| = " << delta1 << endl;
                    cout << "|F(x^" << k + 1 << "(r^" << k << ")) - F(x^" << k << "(r^" << k << "))| = " << delta2 << endl;
                    cout << "||x^" << k + 1 << "(r^" << k << ")) - x^" << k << "(r^" << k << "))|| < eps2   &&    | F(x^" << k + 1 << "(r^" << k << ")) - F(x^" << k << "(r^" << k << ")) | < eps2" << endl;
                    if (k == kk + 1)
                        break;
                    kk = k;
                }
                else
                {
                    cout << "||x^" << k + 1 << "(r^" << k << ")) - x^" << k << "(r^" << k << "))|| = " << delta1 << endl;
                    cout << "|F(x^" << k + 1 << "(r^" << k << ")) - F(x^" << k << "(r^" << k << "))| = " << delta2 << endl;
                    cout << "||x^" << k + 1 << "(r^" << k << ")) - x^" << k << "(r^" << k << "))|| > eps2   &&    | F(x^" << k + 1 << "(r^" << k << ")) - F(x^" << k << "(r^" << k << ")) | > eps2\n" << endl;
                }
            }
            else {
                cout << "F(x^" << k + 1 << "(r^" << k << ")) - F(x^" << k << "(r^" << k << ")) = " << fx2 - fx1 << " > 0" << endl;
                tk = tk / 2;
                goto tryAgain;
            }

            x1 = a[0];
            x2 = a[1];
            k = k + 1;

            df = sqrt(pow(dFobrx1(x1, x2, rk), 2) + pow(dFobrx2(x1, x2, rk), 2));
        }

        if (g(a[0], a[1]) <= 0) {
            cout << "\tПромежуточный ответ: x^" << k + 1 << "(r^" << k << "): (" << a[0] << ";" << a[1] << ")" << endl;
            x1 = a[0];
            x2 = a[1];
            Pxr = Pobr(x1, x2, rk);

            rk = rk / C;
            k++;
        }
        else
        {
            cout << "\tПромежуточный ответ: x^" << k + 1 << "(r^" << k << "): (" << a[0] << ";" << a[1] << ") не принадлежит множеству Х" << endl;
            x1 = a[0];
            x2 = a[1];
            Pxr = Pobr(x1, x2, rk);
            rk = rk / C;
            k++;
        }

    }

    cout << "\n ---Ответ--- \nx*: (" << a[0] << ";" << a[1] << ")" << endl;
    cout << "f(x*): " << f(a[0], a[1]) << endl;
    cout << "Конечное число шагов: " << k << endl;

    return 0;

}


int main()
{
    setlocale(LC_ALL, "Russian");
    double x1 = -1, x2 = 1, tk = 1, a1 = -1, b1 = 1;
    double r0 = 0.5;
    int C = 8;

    cout << fixed;
    cout.precision(3);

    cout << "\tf(x) = x_1^2 + 2 * x_2^2 - 5" << endl;
    cout << "\tg_1(x) = 8 * x_1 + x_2 - 7 <= 0" << endl;
    cout << "\tx^0 = [" << x1 << "; " << x2 << "] " << endl;
    cout << "\tC = " << C << endl;
    cout << "\teps = " << eps << ";\teps1 = " << eps1 << ";\teps2 = " << eps2 << endl;
    cout << "\tr_0 = " << r0 << endl;


    BarrierFunction(x1, x2, r0, C);
    return 1;
}
