#pragma once
#include "BaseOptMethod.h"
#include "random"

using namespace std;
class StochasticMethod : public BaseOptMethod
{
public:
	explicit StochasticMethod(
		const vector<double>& startPoint,
		random_device& rd,
		double p = 0.5,
		double delta = 1) : 
		BaseOptMethod(startPoint), 
		p(p), 
		delta(delta),
		rd(rd){
		CheckInput();
	};
	
	/// <summary>
	/// Оптимизация стохастического метода:
	/// локальный + глобальный поиск, который осуществляет
	/// поиск точки максимума.
	/// </summary>
	/// <param name="ba">Область поиска</param>
	/// <param name="bf">Целевая функция</param>
	/// <param name="bsc">Критерий остановки</param>
	virtual void Optimize(const BaseArea& ba, const BaseFunction& bf, const BaseStopCriterion& bsc) override;
private:
	/// <summary>
	/// p - вероятность попасть в круг точки
	/// </summary>
	double p;

	/// <summary>
	/// Дельта - радиус круга, внутри которого
	/// будет рассматриваться равномерное распределение
	/// с вероятностью p
	/// </summary>
	double delta;

	/// <summary>
	/// Устройство для генерации случайных чисел
	/// </summary>
	random_device& rd;
	/// <summary>
	/// Метод на корректность ввода.
	/// Возможно будет полезно переписать этот метод в виде
	/// обработчика исключений
	/// </summary>
	void CheckInput();

	/// <summary>
	/// Метод генерации вектора глобального поиска
	/// </summary>
	/// <param name="bounds">Границы параллелограмма</param>
	/// <returns>Случайный вектор внутри параллелограмма</returns>
	vector<double> GlobalVectorSearch(const vector<pair<double, double>>& bounds) const;

	vector<double> LocalVectorSearch(const vector<pair<double, double>>& bounds) const;
};

