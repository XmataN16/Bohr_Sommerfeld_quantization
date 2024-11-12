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
	// �������������� ������� �������� X � V
	int size_X = Nx + 1;
	int size_V = Nx + 1;

	// ������ ������ ������� ������
	double start_time = omp_get_wtime();

	// ������������� �������� X � V ����������
	double* X = init_X(size_X);
	double* V = init_V(X, size_V);

	// ����� ������������� � ������������ ���������� ������� ������� � �������� �������
	double E_min = get_min_array(V, size_V);
	double E_max = get_max_array(V, size_V);
	double dE = (E_max - E_min) / Ne;

	int size_E = Ne + 1;
	double* E = init_E(size_E, E_max, dE);

	// ������ ��������� �������� ������ �������
	std::list<double> energy_levels;

	// ������ ��������� ����� ������ ����������� ����-������������
    #pragma omp parallel for
	for (int i = 0; i < size_E; i++)
	{
		// ��� 1: ����� ����� �������� a � b ��� �������� �������� E
		double a = dichotomy(x1, 0.0, E[i], 1e-6);
		double b = dichotomy(0.0, x2, E[i], 1e-6);

		// ��� 2: ����� ������� ��� �������� ����������
		double S = 2.0 * integral_middle_rectangles(a, b, Nx, calc_dS, E[i]);

		// ��� 3: ���� ��������� ����� n, ��� �������� S(E) ������ � (n + gamma) * 2 * PI
		for (int n = 0; n < 5; n++)
		{
			double target_S = 2 * PI * (double(n) + gamma);
			if (abs(S - target_S) < 1e-1)  // tolerance � ����� ��������
			{
				energy_levels.push_back(E[i]);  // ��������� �������, ���� ������� ���������
				break;  // ��������� � ���������� �������� E, ����� �������� ������������
			}
		}

	}

	// ����� ������ ������� ������
	double end_time = omp_get_wtime();

	// ����� ������� ������ ���������� �� ����� �������
	printf("Execution time: %f seconds\n", end_time - start_time);

	// ����� ��������� ����� ���������� �������
	std::list<double> unique_energy_levels = round_levels(energy_levels, 1e-1);  // ������������� tolerance

	// ����� ���������� ������� �������
	std::cout << "Unique energy levels:\n";
	for (double energy : unique_energy_levels)
	{
		std::cout << energy << "\t";
	}
	std::cout << std::endl;


	// ���������� ������� V � ����
	save_array_to_file(V, size_V, "graph/V_values.txt");

	// ���������� ������� X � ����
	save_array_to_file(X, size_X, "graph/X_values.txt");

	// ���������� ���������� ������� ������� � ����
	save_list_to_file(unique_energy_levels, "graph/energy_levels.txt");

	// ������� ������
	delete[] X;
	delete[] V;

	return 0;
}

