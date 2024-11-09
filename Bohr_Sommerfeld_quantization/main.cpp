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

	// Начало замера времени работы
	double start_time = omp_get_wtime();

	// Инициализация массивов X и V значениями
	double* X = init_X(size_X);
	double* V = init_V(X, size_V);

	// Поиск максимального и минимального допустимых уровней энергии в заданной области
	double E_min = get_min_array(V, size_V);
	double E_max = get_max_array(V, size_V);

	// Задаем начальное значение уровня энергии
	double E_current = E_max;

	// Запуск основного цикла метода квантования Бора-Зоммерфельда
	while (E_current > E_min)
	{
		// Шаг 1: Найти точки поворота a и b для текущего значения E
		double a = dichotomy(x1, 0, E_current, 1e-6);
		double b = dichotomy(0, x2, E_current, 1e-6);

		// Шаг 2: Найти площадь под графиком потенциала

		E_current -= dE;
	}

	// Конец замера времени работы
	double end_time = omp_get_wtime();

	// Вывод времени работы реализации на экран консоли
	printf("Execution time: %f seconds\n", end_time - start_time);

	// Очистка памяти
	delete[] X;
	delete[] V;
}

