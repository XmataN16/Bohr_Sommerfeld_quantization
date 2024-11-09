#pragma once
// Параметры потенциала
const double V0 = 20.0;  // глубина потенциала
const double a = 1.5;  // ширина потенциала

const int Nx = 100; // Число узлов вдоль оси Ox

// Границы рассматриваемой области потенциала по x
const double x1 = -6.0;
const double x2 = 6.0;

// Приращение по x
const double dx = (x2 - x1) / Nx;

double calc_V(double x)
{
	return (-V0 / (pow(cosh(x / a), 2)));
}

// Инициализация массива X
double* init_X(int size_x)
{
	double* X = new double[size_x];

    #pragma omp parallel for
	for (int i = 0; i < size_x; i++)
	{
		X[i] = x1 + (i * dx);
	}

	return X;
}

// Инициализация массива V
double* init_V(double* X, int size_v)
{
	double* V = new double[size_v];

    #pragma omp parallel for
	for (int i = 0; i < size_v; i++)
	{
		V[i] = calc_V(X[i]);
	}

	return V;
}

// Функция вывода массива в консоль
void print_array(double* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << std::endl;
	}
}