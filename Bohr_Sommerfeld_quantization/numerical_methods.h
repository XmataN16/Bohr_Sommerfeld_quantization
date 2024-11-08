#pragma once
#include <cmath>

// Метод градиентного спуска для одномерного случая
double gradient_descent1D(std::vector<double> X, std::vector<double> V, double eps, double alpha)
{
	// Начальное приближение
	double X_current = X[X.size() / 2];
	double V_current = V[X.size() / 2];

	double X_prev, V_prev, gradient;

	do
	{
		// Текущие значения V(x) и x устанавливаем предыдущими
		X_prev = X_current;
		V_prev = V_current;

		// Расчет градиента
		gradient = (calc_V(X_prev + dx) - calc_V(X_prev - dx)) / (2*dx);

		// Обновление значений V и x (движение в направлении обратном градиенту -grad(V))
		X_current = X_prev - (alpha * gradient);
		V_current = calc_V(X_current);
	} 
	while (abs(V_current - V_prev) > eps and X_current >= x1 and X_current <= x2); // условие останова

	return V_current;
}

