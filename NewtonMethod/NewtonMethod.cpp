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


double MethodNew(double x1, double x2, double tk, double M)
{
    int k = 0;
    int kk = 0;
    int n = 2;

    double det = 0;
    std::cout << "_____________________________________________" << endl;
    std::cout << "\t\tМетод Ньютона" << endl;

    std::cout << "df(x) = (4 * x_1 + 0.2 * x_2; 12 * x_2 + 0.2 * x_1)^T" << endl;

    double a[2], dk[2];
    double delta1, delta2, a1, a2;
    double H[2][2];

    a[0] = x1;
    a[1] = x2;

    std::cout << "\n---- Шаг " << k << " ----" << endl;
    std::cout << "df(x^0) = (" << dfdx1(x1, x2) << "; " << dfdx2(x1, x2) << ")^T" << endl;

    double df;
    df = sqrt(pow(dfdx1(x1, x2), 2) + pow(dfdx2(x1, x2), 2));
    std::cout << "||df(x^0)|| = " << df << endl;

    double fx1, fx2;

    double matr[2][2];

    double d2fx2 = 4;
    double d2fxfy = 0.2;
    double d2fy2 = 12;

    H[0][0] = d2fx2;
    H[0][1] = d2fxfy;
    H[1][0] = d2fxfy;
    H[1][1] = d2fy2;

    cout << "\nH(x) = " << "\t";
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            matr[i][j] = H[i][j];
            cout << matr[i][j] << "\t";
        }
        cout << endl << "\t";
    }
    cout << endl;

    det = matr[0][0] * matr[1][1] - matr[1][0] * matr[0][1];
    cout << "Определитель матрицы Гессе равен: " << det << endl;
    double obr_matr[2][2];

    obr_matr[0][0] = H[1][1] / det;
    obr_matr[0][1] = -H[1][0] / det;
    obr_matr[1][0] = -H[0][1] / det;
    obr_matr[1][1] = H[0][0] / det;

    cout << "\nH^(-1)(x^k) = " << "\t";
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            H[i][j] = obr_matr[j][i];
            cout << H[i][j] << "\t";
        }
        cout << endl << "\t\t";
    }

    a1 = H[0][0];
    a2 = H[0][0] * H[1][1] - H[0][1] * H[1][0];

    while (df >= eps1 && k < M)
    {
        if (k != 0) {
            std::cout << "\n---- Шаг " << k << " ----" << endl;
            df = sqrt(pow(dfdx1(x1, x2), 2) + pow(dfdx2(x1, x2), 2));
            std::cout << "||df(x^" << k << ")|| = " << df << endl;
        }
        std::cout << "\n||df(x^" << k << ")|| >= eps1   &&   k < " << M << endl;

        fx1 = f(x1, x2);
        if (a1 > 0 && a2 > 0)
        {
            cout << "H^(-1)(x^" << k << ") > 0" << endl;
            dk[0] = (-1) * H[0][0] * dfdx1(x1, x2) + (-1) * H[0][1] * dfdx2(x1, x2);
            dk[1] = (-1) * H[1][0] * dfdx1(x1, x2) + (-1) * H[1][1] * dfdx2(x1, x2);
            std::cout << "d^" << k << " = (" << dk[0] << "; " << dk[1] << ")" << endl;
        }
        else
        {
            cout << "H^(-1)(x^" << k << ") <= 0" << endl;
            dk[0] = -dfdx1(x1, x2);
            dk[1] = -dfdx2(x1, x2);
            std::cout << "d^" << k << " = (" << dk[0] << "; " << dk[1] << ")" << endl;
        }

        std::cout << "t_" << k << " = " << tk << endl;
    tryAgain:
        a[0] = x1 + tk * dk[0];
        a[1] = x2 + tk * dk[1];

        fx2 = f(a[0], a[1]);
        std::cout << "f(x^" << k << ") =" << fx1 << endl;
        std::cout << "f(x^" << k + 1 << ") =" << fx2 << endl;

        if (a1 <= 0 && a2 <= 0)
            if (fx2 - fx1 < 0)
            {
                std::cout << "f(x^" << k + 1 << ") - f(x^" << k << ") =" << fx2 - fx1 << " < 0" << endl;
            }

            else {
                std::cout << "f(x^" << k + 1 << ") - f(x^" << k << ") =" << fx2 - fx1 << " > 0" << endl;
                tk = tk / 2;
                goto tryAgain;
            }

        delta1 = sqrt(pow(a[0] - x1, 2) + pow(a[1] - x2, 2));

        std::cout << "x^(" << k + 1 << ") = (" << x1 << "; " << x2 << ") - " << tk << " * (" << dk[0] << "; " << dk[1] << ") = (" << a[0] << ";" << a[1] << ")" << endl;

        delta2 = fabs(fx2 - fx1);

        if (delta1 < eps2 && delta2 < eps2)
        {
            std::cout << "||x^" << k + 1 << "- x^" << k << "|| = " << delta1 << endl;
            std::cout << "|f(x^" << k + 1 << ") - f(x^" << k << ")| = " << delta2 << endl;
            std::cout << "||x^" << k + 1 << "- x^" << k << "|| < eps2   &&    |f(x^" << k + 1 << ") - f(x^" << k << ")| < eps2" << endl;
            if (k == kk + 1)
                break;
            kk = k;
        }
        x1 = a[0];
        x2 = a[1];
        k = k + 1;
        df = sqrt(pow(dfdx1(x1, x2), 2) + pow(dfdx2(x1, x2), 2));

        if (df < eps1)
        {
            std::cout << "||df(x^" << k << ")|| = " << df << " < eps1 " << endl;
        }

        if (k == M)
        {
            std::cout << "k = M" << endl;
        }
    }
    std::cout << "\n ---ОТВЕТ--- \nx*: (" << a[0] << ";" << a[1] << ")" << endl;
    std::cout << "f(x*): " << f(a[0], a[1]) << endl;
    std::cout << "Конечное число шагов: " << k << endl;
    return 0;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    double x1 = 1.5, x2 = 0.5, tk = 1, a1 = -1, b1 = 1;

    double M = 10;

    std::cout << fixed;
    std::cout.precision(4);

    std::cout << "\tf(x) = 2 * x_1^2 + 0.2 * x_1 * x_2 + 6 * x_2^2" << endl;
    std::cout << "\tx^0 = [1.5; 0.5] " << endl;
    std::cout << "\tM = " << M << endl;
    std::cout << "\teps1 = " << eps1 << endl;
    std::cout << "\teps2 = " << eps2 << endl;
    std::cout << "\tt_k = " << tk << endl;

    std::cout << "\tdf(x)/dx_1 = 4 * x_1 + 0.2 * x_2" << endl;
    std::cout << "\tdf(x)/dx_2 = 12 * x_2 + 0.2 * x_1" << endl;

    MethodNew(x1, x2, tk, M);
    return 1;
}
