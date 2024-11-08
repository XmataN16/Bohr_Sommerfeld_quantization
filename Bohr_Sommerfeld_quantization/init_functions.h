#pragma once
//���������
const double pi = 3.141592653589793;

// ��������� �����
const int Nx = 20; // ����� ����� �� ��� Ox
const int Ne = 100; // ����� ����� �� ��� ������� E
const double x1 = -2.0; // ����� ����� �� x
const double x2 = 2.0; // ������ ����� �� x

const double dx = (x2 - x1) / double(Nx); // ���������� �� ��� Ox

// ��������� ����������
const double V0 = 20.0; // ������� ����������
const double a = 1.5;  // ������ ����������

// ������� ��� ������� ���������� V(x)
double calc_V(double x)
{
	return(-V0 / (pow(cos(x / a), 2))); // ����� ����������� ������� �������� ��������� V(x)
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