#include "FunctionThree.h"

/// <summary>
/// Вычисляет функцию от трёх переменных.
/// Точка минимума в (3.25, 1.25, -0.75)
/// </summary>
/// <param name="x">Вектор, где вычисляется функция</param>
/// <returns>Значение функции в точке-векторе</returns>
double FunctionThree::operator()(const vector<double>& x) const
{
	return pow(2*x[0] + x[1] + x[2] - 7, 2) +
		pow(x[0] + 2*x[1] + x[2] - 5, 2) +
		pow(x[0] + x[1] + 2*x[2] - 3, 2);
}

vector<double> FunctionThree::GetGradient()
{
	return vector<double>();
}
