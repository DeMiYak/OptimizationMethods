#pragma once
#include "BaseOptMethod.h"

using namespace std;

/// <summary>
/// Класс метода деформируемых многогранников Nelder-Mead.
/// Рассуждения по поводу полей класса:
/// 1. Траектория - траектория движения точки
/// 2. Симплекс-фигура - по ней будет строиться симплекс
/// Зачем разделять траекторию и симплекс...
/// Есть альтернатива - вектор индексов, которые будут заменять симплекс.
/// 
/// 
/// Ещё для метода надо добавить выход за границы. Добавлено.
/// </summary>
class NelderMeadMethod : public BaseOptMethod
{
public:
	explicit NelderMeadMethod(const vector<double>& startPoint, 
		double alpha = 1, 
		double gamma = 2,
		double beta = 0.5,
		double t = 1) : 
		BaseOptMethod(startPoint),
		alpha(alpha),
		gamma(gamma),
		beta(beta),
		t(t){
		CheckInput();
	};
	virtual void Optimize(const BaseArea& ba, const BaseFunction& bf, const BaseStopCriterion& bsc) override;

private:
	/// <summary>
	/// Коэффициент отражения (>0)
	/// </summary>
	double alpha;
	/// <summary>
	/// Коэффициент растяжения (>1)
	/// </summary>
	double gamma;
	/// <summary>
	/// Коэффициент сжатия (0<beta<1)
	/// </summary>
	double beta;
	/// <summary>
	/// Изначальное расстояние между точками симплекса
	/// </summary>
	double t;

	/// <summary>
	/// Вектор индексов симплекса. Хранит индексы из траектории, образующие
	/// симплекс на произвольной итерации
	/// </summary>
	vector<size_t> simplex_index;

	/// <summary>
	/// Значения симплекса в каждой точке. Польза - за ограниченную память экономим в вычислениях,
	/// то есть не приходится пересчитывать по несколько раз одно и то же значение.
	/// </summary>
	vector<double> simplex_value;

	/// <summary>
	/// Функция задаёт значения в начальном симплексе. 
	/// Важно: для инициализации требуется InitTrajectoryAsSimplex 
	/// </summary>
	void InitSimplexValues(const BaseFunction& bf);

	/// <summary>
	/// Строит начальный симплекс для метода Nelder-Mead 
	/// </summary>
	void InitTrajectoryAsSimplex(const BaseArea& ba);

	/// <summary>
	/// Нахождение центра масс для симплекса
	/// без одной точки.
	/// </summary>
	vector<double> MassCenter(const pair<size_t, size_t>& minmax_index);

	/// <summary>
	/// Метод отражения
	/// </summary>
	vector<double> Reflection(const vector<double>& x_n_2, const vector<double>& x_max, const BaseArea& ba);

	/// <summary>
	/// Метод редукции
	/// </summary>
	void Reduction(const pair<size_t, size_t>& minmax_index, const vector<double>& x_min);

	/// <summary>
	/// Метод сжатия (с beta)
	/// </summary>
	/// <returns></returns>
	vector<double> Compression(const vector<double>& x_n_2, const vector<double>& x_max);

	/// <summary>
	/// Метод растяжения
	/// </summary>
	vector<double> Stretching(const vector<double>& x_n_2, const vector<double>& x_n_3, const BaseArea& ba);

	/// <summary>
	/// Приватная функция для проверки на корректный ввод. Нужны исправления, так как
	/// некорректно обрабатываются исключения
	/// </summary>
	void CheckInput();

	/// <summary>
	/// Метод для нахождения индексов минимального и максимального элементов
	/// в методе деформируемого многогранника
	/// </summary>
	/// <returns>Пару значений: индексы минимума и максимума</returns>
	pair<size_t, size_t> FindMinMaxIndex(const BaseFunction& bf) const;

	
};

