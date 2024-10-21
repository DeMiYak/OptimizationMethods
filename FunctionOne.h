#pragma once
#include "BaseFunction.h"

/// <summary>
/// Функция сферы
/// </summary>
class FunctionOne : public BaseFunction
{
public:
	/// <summary>
	/// Конструктор
	/// </summary>
	/// <param name="_dim">Размерность функции (число независимых переменных)</param>
	FunctionOne() : BaseFunction(1) {};

	FunctionOne(const FunctionOne& fo) : BaseFunction(fo.dim) {};

	FunctionOne(FunctionOne&& fo) noexcept : BaseFunction(fo.dim) {};
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
	virtual double operator()(const vector<double>& x) const;
	/// <summary>
	/// Функция, возвращающая градиент (по идее должна иметь тип vector<double>)
	/// </summary>
	virtual vector<double> GetGradient() override;
private:
};

