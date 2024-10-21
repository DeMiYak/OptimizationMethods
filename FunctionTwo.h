#pragma once
#include "BaseFunction.h"

/// <summary>
/// Функция Розенброка
/// </summary>
class FunctionTwo : public BaseFunction
{
public:
	/// <summary>
	/// Конструктор
	/// </summary>
	/// <param name="_dim">Размерность функции (число независимых переменных)</param>
	FunctionTwo() : BaseFunction(2) {};

	FunctionTwo(const FunctionTwo& fo) : BaseFunction(fo.dim) {};

	FunctionTwo(FunctionTwo&& fo) noexcept : BaseFunction(fo.dim) {};
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

	virtual vector<double> GetGradient() override;
private:
};

