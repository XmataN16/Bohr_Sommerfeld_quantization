#pragma once
// ���������
const double PI = 3.141592653589793;
const double m = 1.0;

// ��������� ����������
const double V0 = 20.0;  // ������� ����������
const double a = 1.5;  // ������ ����������

const int Nx = 100; // ����� ����� ����� ��� Ox

// ������� ��������������� ������� ���������� �� x
const double x1 = -6.0;
const double x2 = 6.0;

// ���������� �� x
const double dx = (x2 - x1) / Nx;
// ���������� �� �������
const double dE = 0.001;

// ������� ��� ������� �������� ���������� � ����� x
double calc_V(double x)
{
	return (-V0 / (pow(cosh(x / a), 2)));
}

// ������� ��� ������� dS(E)
double cals_dS(double x, double E)
{
	return sqrt(2 * m * (E - calc_V(x)));
}

// ������������� ������� X
double* init_X(int size_X)
{
	double* X = new double[size_X];

    #pragma omp parallel for
	for (int i = 0; i < size_X; i++)
	{
		X[i] = x1 + (i * dx);
	}

	return X;
}

// ������������� ������� V
double* init_V(double* X, int size_V)
{
	double* V = new double[size_V];

    #pragma omp parallel for
	for (int i = 0; i < size_V; i++)
	{
		V[i] = calc_V(X[i]);
	}

	return V;
}

// ������� ������ ������� � �������
void print_array(double* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << std::endl;
	}
}