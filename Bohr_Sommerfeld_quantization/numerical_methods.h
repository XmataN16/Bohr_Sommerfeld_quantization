#pragma once
// Функция поиска максимума в массиве
double get_max_array(double* array, int size)
{
	double max_array = array[0];

    #pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		if (array[i] > max_array) max_array = array[i];
	}

	return max_array;
}

// Функция поиска минимума в массиве
double get_min_array(double* array, int size)
{
	double min_array = array[0];

    #pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		if (array[i] < min_array) min_array = array[i];
	}

	return min_array;
}

// Метод дихотомии для поиска корня уравнения V(x) - E = 0
double dichotomy(double a, double b, double E, double tolerance) 
{
	double mid;
	while (std::abs(b - a) > tolerance) 
	{
		mid = (a + b) / 2.0;
		if ((calc_V(mid) - E) * (calc_V(a) - E) < 0) 
		{
			b = mid;
		}
		else 
		{
			a = mid;
		}
	}
	return (a + b) / 2.0; // Возвращаем среднюю точку
}

// Метод средних прямоугольников для интегрирования
template <typename Func, typename... Args>
double integral_middle_rectangles(double a, double b, int N, Func f, Args... args)
{
	double dx = (b - a) / N;
	double sum = 0.0;
	double x_middle;

    #pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < N; i++)
	{
		x_middle = a + (i + 0.5) * dx;  
		sum += f(x_middle, args...);  
	}

	return sum * dx;
}

std::list<double> round_levels(const std::list<double>& energy_levels, double tolerance)
{
	std::list<double> rounded_levels;

	for (double energy : energy_levels)
	{
		// Ищем близкое значение в rounded_levels
		auto it = std::find_if(rounded_levels.begin(), rounded_levels.end(), [energy, tolerance](double rounded_energy)
			{
				return std::abs(energy - rounded_energy) < tolerance;
			});

		// Если находим близкое значение, заменяем его на среднее арифметическое
		if (it != rounded_levels.end())
		{
			*it = (*it + energy) / 2.0;
		}
		// Если близкого значения нет, добавляем текущее значение в результат
		else
		{
			rounded_levels.push_back(energy);
		}
	}

	// Сортируем список rounded_levels в порядке возрастания
	rounded_levels.sort();

	return rounded_levels;
}
