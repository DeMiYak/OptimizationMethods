#pragma once
#include<vector>
#include"BaseStopCriterion.h"
#include"BaseArea.h"
#include"BaseFunction.h"
#include"DataTransfer.h"
using namespace std;
/// <summary>
/// Базовый класс для реализации методов оптимизации (нахождения экстремумов).
/// Пока предлагается реализовать только метод деформируемых многогранников (Nelder-Mead).
/// Возникает вопрос, где хранить траекторию? Кажется, что сам метод должен либо хранить
/// только точку, которая оптимизируется, либо траекторию (она понадобится для зарисовки графики).
/// </summary>
class BaseOptMethod {
public:
	/// <summary>
	/// Конструктор для базового класса с параметром-вектором
	/// </summary>
	/// <param name="startPoint">Начальная точка</param>
	explicit BaseOptMethod(const vector<double>& startPoint) : startPoint(startPoint) {};

	BaseOptMethod(const BaseOptMethod& bom) : startPoint(bom.startPoint) {};

	BaseOptMethod(BaseOptMethod&& bom) noexcept : startPoint(move(bom.startPoint)) {};

	/// <summary>
	/// Абстрактный метод оптимизации, который 
	/// </summary>
	/// <param name="ba">Область, внутри которой будет производиться поиск
	/// экстремума</param>
	/// <param name="bf">Функция, заданная в некоторой области, которая не обязательно
	/// связана с BaseArea. Важно, чтобы область из BaseArea, содержалась в области определения
	/// самой функции.</param>
	/// <param name="bsc">Критерий остановки. Предполагается, что метод оптимизации работает
	/// бесконечно, и для того, чтобы поиск выполнялся за конечное время, необходимо установить
	/// критерий, по которому поиск будет останавливаться и давать решение с определённой
	/// точностью. </param>
	virtual void Optimize(const BaseArea& ba, const BaseFunction& bf, const BaseStopCriterion& bsc) = 0;

	/// <summary>
	/// Сеттер для начальной точки
	/// </summary>
	/// <param name="_startPoint">Начальная точка</param>
	void SetStartPoint(const vector<double>& _startPoint) { startPoint = _startPoint; trajectory.clear(); };
	vector<vector<double>> GetTrajectory() const { return trajectory; };
	vector<double> GetStartPoint() const { return startPoint; };
protected:
	vector<double> startPoint;
	vector<vector<double>> trajectory;
	DataTransfer dt;
	/// <summary>
	/// Метод для корректировки положения точки в случае 
	/// выхода за границы области
	/// </summary>
	/// <param name="fixedPoint">Фиксированная точка, относительно которой 
	/// рассматривается положение изменяемой точки </param>
	/// <param name="adjustablePoint">Изменяемая точка, для которой корректируется положение</param>
	/// <param name="ba">Область</param>
	void CorrectPointPlacement(const vector<double>& fixedPoint, vector<double>& adjustablePoint, const BaseArea& ba);
};