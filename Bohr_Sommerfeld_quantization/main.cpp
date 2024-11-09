#include <iostream>
#include <algorithm>
#include <cmath>
#include <omp.h>
#include <init_functions.h>
#include <numerical_methods.h>

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

	// ������ ��������� �������� ������ �������
	double E_current = E_max;

	// ������ ��������� ����� ������ ����������� ����-������������
	while (E_current > E_min)
	{
		// ��� 1: ����� ����� �������� a � b ��� �������� �������� E
		double a = dichotomy(x1, 0, E_current, 1e-6);
		double b = dichotomy(0, x2, E_current, 1e-6);

		// ��� 2: ����� ������� ��� �������� ����������

		E_current -= dE;
	}

	// ����� ������ ������� ������
	double end_time = omp_get_wtime();

	// ����� ������� ������ ���������� �� ����� �������
	printf("Execution time: %f seconds\n", end_time - start_time);

	// ������� ������
	delete[] X;
	delete[] V;
}

