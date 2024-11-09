#include <iostream>
#include <algorithm>
#include <cmath>
#include <omp.h>
#include <init_functions.h>
#include <numerical_methods.h>

int main()
{
	// Инициализируем размеры массивов X и V
	int size_X = Nx + 1;
	int size_V = Nx + 1;

	// Инициализация массивов X и V значениями
	double* X = init_X(size_X);
	double* V = init_V(X, size_V);

	double E_min = get_min_array(V, size_V);
	double E_max = get_max_array(V, size_V);

	std::cout << E_min << " " << E_max << std::endl;

	// Очистка памяти
	delete[] X;
	delete[] V;
}

