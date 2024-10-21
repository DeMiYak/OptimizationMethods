#pragma once
#include<iostream>
#include<vector>
#include"BaseFunction.h"
using namespace std;
/// <summary>
/// ����� ��� �������� ������ � �������� ���������
/// </summary>
class DataTransfer
{
public:
	/// <summary>
	/// �������
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
	/// �������
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
	/// ��������� �� ����������
	/// </summary>
	shared_ptr<vector<vector<double>>> trajectory = nullptr;
	/// <summary>
	/// ��������� �� ������� ���������
	/// </summary>
	shared_ptr<vector<size_t>> sim_ind = nullptr;
	//shared_ptr<BaseFunction> bfPtr = nullptr;
	/// ������ bf ����� ������� vector<double> � ���������� ���
	
	/// <summary>
	/// ��������� �� �������� ���������
	/// </summary>
	shared_ptr<vector<double>> simplexValues = nullptr;
	/// <summary>
	/// ��������� �� ������������ �����
	/// </summary>
	shared_ptr<vector<double>> currPoint = nullptr;

};

