#pragma once
// ������� ������ ��������� � �������
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

// ������� ������ �������� � �������
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

// ����� ��������� ��� ������ ����� ��������� V(x) - E = 0
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
	return (a + b) / 2.0; // ���������� ������� �����
}

// ����� ������� ��������������� ��� ��������������
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
		// ���� ������� �������� � rounded_levels
		auto it = std::find_if(rounded_levels.begin(), rounded_levels.end(), [energy, tolerance](double rounded_energy)
			{
				return std::abs(energy - rounded_energy) < tolerance;
			});

		// ���� ������� ������� ��������, �������� ��� �� ������� ��������������
		if (it != rounded_levels.end())
		{
			*it = (*it + energy) / 2.0;
		}
		// ���� �������� �������� ���, ��������� ������� �������� � ���������
		else
		{
			rounded_levels.push_back(energy);
		}
	}

	// ��������� ������ rounded_levels � ������� �����������
	rounded_levels.sort();

	return rounded_levels;
}
