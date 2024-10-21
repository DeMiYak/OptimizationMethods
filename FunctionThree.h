#pragma once
#include"BaseFunction.h"

/// <summary>
/// Функция-мимик функции Била
/// </summary>
class FunctionThree : public BaseFunction
{
public:
	/// <summary>
	/// Конструктор
	/// </summary>
	/// <param name="_dim">Размерность функции (число независимых переменных)</param>
	FunctionThree() : BaseFunction(3) {};

	FunctionThree(const FunctionThree& fo) : BaseFunction(fo.dim) {};

	FunctionThree(FunctionThree&& fo) noexcept : BaseFunction(fo.dim) {};
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

