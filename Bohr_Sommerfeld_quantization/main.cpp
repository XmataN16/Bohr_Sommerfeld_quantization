#include <iostream>
#include <omp.h>
#include <vector>
#include <init_functions.h>
#include <numerical_methods.h>

void print_vector(std::vector<double> vec);

int main()
{
	std::vector<double> X;
	std::vector<double> V;
	std::vector<double> energy_levels;
	init_X(X);
	init_V(V, X);

	print_vector(V);
	return 0;
}

void print_vector(std::vector<double> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << std::endl;
	}
}
