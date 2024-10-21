#pragma once
#include<vector>
#include<iostream>

using namespace std;

/// <summary>
/// Базовый класс функций, который будет использоваться для
/// демонстрации работоспособности метода деформируемых многогранников (Nelder-Mead).
/// </summary>
class BaseFunction {
public:
	/// <summary>
	/// Конструктор
	/// </summary>
	/// <param name="_dim">Размерность функции (число независимых переменных)</param>
	BaseFunction(size_t _dim) :dim(_dim) {};

	BaseFunction(const BaseFunction& bf) : dim(bf.dim) {};

	BaseFunction(BaseFunction&& bf) noexcept : dim(bf.dim) {};
	/// <summary>
	/// Геттер размерности
	/// </summary>
	/// <returns>Размерность</returns>
	virtual size_t const GetDim() { return dim; }
	/// <summary>
	/// Оператор() для вычисления значения в точке
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	virtual double operator()(const vector<double>& x) const = 0;
	/// <summary>
	/// Функция, возвращающая градиент (по идее должна иметь тип vector<double>)
	/// </summary>
	virtual vector<double> GetGradient() = 0;
protected:
	const size_t dim;
};