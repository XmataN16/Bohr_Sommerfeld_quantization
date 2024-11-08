#pragma once
//Константы
const double pi = 3.141592653589793;

// Параметры сетки
const int Nx = 20; // Число узлов по оси Ox
const int Ne = 100; // Число узлов по оси энергии E
const double x1 = -2.0; // Левая грань по x
const double x2 = 2.0; // Правая грань по x

const double dx = (x2 - x1) / double(Nx); // Приращение по оси Ox

// Параметры потенциала
const double V0 = 20.0; // глубина потенциала
const double a = 1.5;  // ширина потенциала

// Функция для задания потенциала V(x)
double calc_V(double x)
{
	return(-V0 / (pow(cos(x / a), 2))); // Здесь указывается функция задающая потенциал V(x)
}


void init_X(std::vector<double>& X)
{
	for (int i = 0; i < Nx + 1; i++)
	{
		X.push_back(x1 + (double(i) * dx));
	}
}

void init_V(std::vector<double>& V, std::vector<double> X)
{
	for (int i = 0; i < X.size(); i++)
	{
		V.push_back(calc_V(X[i]));
	}
}