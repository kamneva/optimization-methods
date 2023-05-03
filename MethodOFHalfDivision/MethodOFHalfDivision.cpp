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

double HalfTimeMethod(double a, double b)
{
	cout << "_________________________" << endl;
	cout << "Метод половинного деления" << endl;
	int k = 0;
	double x = (a + b) / 2;
	double fx = f(x);
	double L = fabs(b - a);
	cout << "\n---- Шаг " << k << " ----" << endl;
	cout << "x_" << k << " = (a_" << k << " + b_" << k << ") /2 = " << x;
	cout << ";\t f(x_" << k << ") = " << fx << endl;
	cout << "|L_2" << k << "| = |b_" << k << " - a_" << k << "| = " << L << " => L_2" << k << " > eps" << endl;
	while (L > eps)
	{
		if (k != 0)
			cout << "\n---- Шаг " << k << " ----" << endl;
		double y = a + L / 4;
		double fy = f(y);
		double z = b - L / 4;
		double fz = f(z);
		cout << "y_" << k << " = a_" << k << " + |L_2" << k << "| / 4 = " << y;
		cout << ";\t f(y_" << k << ") = " << fy << endl;
		cout << "z_" << k << " = b_" << k << " - |L_2" << k << "| / 4 = " << z;
		cout << ";\t f(z_" << k << ") = " << fz << endl;
		fx = f(x);
		cout << "f(x_" << k << ") = " << fx << endl;
		if (fy < fx)
		{
			cout << "f(y_" << k << ") < f(x_" << k << ")" << endl;
			b = x;
			a = a;
			x = y;
		}
		else {
			if (fz < fx)
			{
				cout << "f(z_" << k << ") < f(x_" << k << ")" << endl;
				a = x;
				b = b;
				x = z;
			}
			else {
				cout << "f(x_" << k << ") >= f(y_" << k << ")";
				cout << " && f(x_" << k << ") >= f(z_" << k << ")" << endl;
				a = y;
				b = z;
				x = x;
			}
		}
		cout << "a_" << k + 1 << " = " << a;
		cout << ";\t b_" << k + 1 << " = " << b;
		cout << ";\t x_" << k + 1 << " = " << x << endl;
		L = fabs(b - a);
		if (L > eps)
			cout << "L_2" << k + 1 << " = " << L << " => L_2" << k + 1 << " > eps" << endl;
		k++;
	}
	cout << "L_2" << k << " = " << L << " => L_2" << k << " < eps" << endl;
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
	HalfTimeMethod(a, b);
	return 1;
}