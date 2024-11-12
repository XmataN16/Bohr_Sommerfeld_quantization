#pragma once
// Константы
const double PI = 3.141;
const double gamma = 0.5;
const double m = 1.0;
const double h = 6.62607015 * pow(10, -34);

// Параметры потенциала
const double V0 = 20.0;  // глубина потенциала
const double a = 1.5;  // ширина потенциала

const int Nx = 1000; // Число узлов вдоль оси Ox
const int Ne = 1000; // Число узлов вдоль оси энергии

// Границы рассматриваемой области потенциала по x
const double x1 = -6.0;
const double x2 = 6.0;

// Приращение по x
const double dx = (x2 - x1) / Nx;

// Функция для расчета значения потенциала в точке x
double calc_V(double x)
{
	return (-V0 / (pow(cosh(x / a), 2)));
}

// Функция для расчета dS(E)
double calc_dS(double x, double E)
{
	return sqrt(2 * m * (E - calc_V(x)));
}

// Инициализация массива X
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

// Инициализация массива V
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

// Инициализация массива V
double* init_E(int size_E, double E_max, double dE)
{
	double* E = new double[size_E];

    #pragma omp parallel for
	for (int i = 0; i < size_E; i++)
	{
		E[i] = E_max - (i * dE);
	}

	return E;
}

// Функция вывода массива в консоль
void print_array(double* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << std::endl;
	}
}