#pragma once
#include<vector>
#include"BaseFunction.h"
#include"DataTransfer.h"

using namespace std;



/// <summary>
/// Базовый класс критерия остановки.
/// Имеет iter_num, чтобы следить за ограничением по числу итераций
/// </summary>
class BaseStopCriterion {
public:
	/// <summary>
	/// Конструктор базового класса. Классы наследники реализуют
	/// отдельные критерии остановки, однако ключевым критерием остановки будет
	/// превышение заданного числа итераций. В противном случае есть риск войти
	/// в бесконечный цикл.
	/// </summary>
	/// <param name="iter_num">Число итераций</param>
	BaseStopCriterion(size_t iter_num) : iter_num(iter_num) {};
	/// <summary>
	/// Метод проверки траектории на критерий остановки.
	/// Важно отметить, что одни методы используют функции, а другие - нет.
	/// Тогда вопрос, как для двух разных критериев остановки реализовать Check?
	/// </summary>
	/// <param name="trajectory">Траектория метода оптимизации</param>
	/// <returns>Булевое значение, если TRUE - условия критерия остановки
	/// выполнены и метод останавливает работу, FALSE - иначе.</returns>
	virtual bool Check(const vector<vector<double>>& trajectory, const vector<double>& vec, const size_t& count) const = 0;
	virtual bool Check(const vector<vector<double>>& trajectory, const vector<size_t>& simplex_index, const BaseFunction& bf, const double& f_n_2, const size_t& count) const = 0;
	//virtual bool Check(const DataTransfer& dt) const = 0;
	/// <summary>
	/// Метод проверки на превышение числа итераций
	/// </summary>
	/// <param name="count"></param>
	/// <returns></returns>
	virtual bool Check(const size_t& count) const;
protected:
	/// <summary>
	/// Число итераций
	/// </summary>
	size_t iter_num;

};