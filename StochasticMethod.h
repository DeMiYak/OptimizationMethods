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
	/// ����������� ��������������� ������:
	/// ��������� + ���������� �����, ������� ������������
	/// ����� ����� ���������.
	/// </summary>
	/// <param name="ba">������� ������</param>
	/// <param name="bf">������� �������</param>
	/// <param name="bsc">�������� ���������</param>
	virtual void Optimize(const BaseArea& ba, const BaseFunction& bf, const BaseStopCriterion& bsc) override;
private:
	/// <summary>
	/// p - ����������� ������� � ���� �����
	/// </summary>
	double p;

	/// <summary>
	/// ������ - ������ �����, ������ ��������
	/// ����� ��������������� ����������� �������������
	/// � ������������ p
	/// </summary>
	double delta;

	/// <summary>
	/// ���������� ��� ��������� ��������� �����
	/// </summary>
	random_device& rd;
	/// <summary>
	/// ����� �� ������������ �����.
	/// �������� ����� ������� ���������� ���� ����� � ����
	/// ����������� ����������
	/// </summary>
	void CheckInput();

	/// <summary>
	/// ����� ��������� ������� ����������� ������
	/// </summary>
	/// <param name="bounds">������� ���������������</param>
	/// <returns>��������� ������ ������ ���������������</returns>
	vector<double> GlobalVectorSearch(const vector<pair<double, double>>& bounds) const;

	vector<double> LocalVectorSearch(const vector<pair<double, double>>& bounds) const;
};

