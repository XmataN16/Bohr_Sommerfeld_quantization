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

