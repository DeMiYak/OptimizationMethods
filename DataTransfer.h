#pragma once
#include<iostream>
#include<vector>
#include"BaseFunction.h"
using namespace std;
/// <summary>
/// Класс для переноса данных в критерий остановки
/// </summary>
class DataTransfer
{
public:
	/// <summary>
	/// Сеттеры
	/// </summary>
	/// <param name="_count"></param>
	
	void SetCount(const size_t& _count) { count = _count; };
	void SetFVal(const double& _f_val) { f_val = _f_val; };
	void SetTrajectory(const vector<vector<double>>& _trajectory) { trajectory = make_shared<vector<vector<double>>>(_trajectory); };
	void SetSimplexIndex(const vector<size_t>& simInd) { sim_ind = make_shared<vector<size_t>>(simInd); };
	//void SetBaseFunction(const BaseFunction& bf) { bfPtr = make_shared<BaseFunction>(bf); };
	void SetCurrPoint(const vector<double>& _currPoint) { currPoint = make_shared<vector<double>>(_currPoint); };
	void SetSimplexValues(const vector<double>& _simplexValues) { simplexValues = make_shared<vector<double>>(_simplexValues); };

	/// <summary>
	/// Геттеры
	/// </summary>
	/// <returns></returns>
	
	const size_t& GetCount() const { return count; };
	const double& GetFVal() const { return f_val; };
	const vector<vector<double>>& GetTrajectory() const { return *trajectory; };
	const vector<size_t>& GetSimplexIndex() const { return *sim_ind; };
	//const BaseFunction& GetBaseFunction() const { return *bfPtr; };
	const vector<double>& GetCurrPoint() const { return *currPoint; };
	const vector<double>& GetSimplexValues() const { return *simplexValues; };
private:
	size_t count = 0;
	double f_val = 0;
	/// <summary>
	/// Указатель на траекторию
	/// </summary>
	shared_ptr<vector<vector<double>>> trajectory = nullptr;
	/// <summary>
	/// Указатель на индексы симплекса
	/// </summary>
	shared_ptr<vector<size_t>> sim_ind = nullptr;
	//shared_ptr<BaseFunction> bfPtr = nullptr;
	/// Вместо bf можно сделать vector<double> и передавать его
	
	/// <summary>
	/// Указатель на значения симплекса
	/// </summary>
	shared_ptr<vector<double>> simplexValues = nullptr;
	/// <summary>
	/// Указатель на используемую точку
	/// </summary>
	shared_ptr<vector<double>> currPoint = nullptr;

};

