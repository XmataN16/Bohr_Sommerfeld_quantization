#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <omp.h>
#include <init_functions.h>
#include <numerical_methods.h>
#include <IO_functions.h>

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
	double dE = (E_max - E_min) / Ne;

	int size_E = Ne + 1;
	double* E = init_E(size_E, E_max, dE);

	// Задаем начальное значение уровня энергии
	std::list<double> energy_levels;

	// Запуск основного цикла метода квантования Бора-Зоммерфельда
    #pragma omp parallel for
	for (int i = 0; i < size_E; i++)
	{
		// Шаг 1: Найти точки поворота a и b для текущего значения E
		double a = dichotomy(x1, 0.0, E[i], 1e-6);
		double b = dichotomy(0.0, x2, E[i], 1e-6);

		// Шаг 2: Найти площадь под графиком потенциала
		double S = 2.0 * integral_middle_rectangles(a, b, Nx, calc_dS, E[i]);

		// Шаг 3: Ищем квантовое число n, для которого S(E) близко к (n + gamma) * 2 * PI
		for (int n = 0; n < 5; n++)
		{
			double target_S = 2 * PI * (double(n) + gamma);
			if (abs(S - target_S) < 1e-1)  // tolerance — порог близости
			{
				energy_levels.push_back(E[i]);  // Добавляем энергию, если условие выполнено
				break;  // Переходим к следующему значению E, чтобы избежать дублирования
			}
		}

	}

	// Конец замера времени работы
	double end_time = omp_get_wtime();

	// Вывод времени работы реализации на экран консоли
	printf("Execution time: %f seconds\n", end_time - start_time);

	// После основного цикла добавления энергии
	std::list<double> unique_energy_levels = round_levels(energy_levels, 1e-1);  // Устанавливаем tolerance

	// Вывод уникальных уровней энергии
	std::cout << "Unique energy levels:\n";
	for (double energy : unique_energy_levels)
	{
		std::cout << energy << "\t";
	}
	std::cout << std::endl;


	// Сохранение массива V в файл
	save_array_to_file(V, size_V, "graph/V_values.txt");

	// Сохранение массива X в файл
	save_array_to_file(X, size_X, "graph/X_values.txt");

	// Сохранение уникальных уровней энергии в файл
	save_list_to_file(unique_energy_levels, "graph/energy_levels.txt");

	// Очистка памяти
	delete[] X;
	delete[] V;

	return 0;
}

