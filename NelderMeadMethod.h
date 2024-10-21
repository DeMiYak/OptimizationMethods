#pragma once
#include "BaseOptMethod.h"

using namespace std;

/// <summary>
/// ����� ������ ������������� �������������� Nelder-Mead.
/// ����������� �� ������ ����� ������:
/// 1. ���������� - ���������� �������� �����
/// 2. ��������-������ - �� ��� ����� ��������� ��������
/// ����� ��������� ���������� � ��������...
/// ���� ������������ - ������ ��������, ������� ����� �������� ��������.
/// 
/// 
/// ��� ��� ������ ���� �������� ����� �� �������. ���������.
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
	/// ����������� ��������� (>0)
	/// </summary>
	double alpha;
	/// <summary>
	/// ����������� ���������� (>1)
	/// </summary>
	double gamma;
	/// <summary>
	/// ����������� ������ (0<beta<1)
	/// </summary>
	double beta;
	/// <summary>
	/// ����������� ���������� ����� ������� ���������
	/// </summary>
	double t;

	/// <summary>
	/// ������ �������� ���������. ������ ������� �� ����������, ����������
	/// �������� �� ������������ ��������
	/// </summary>
	vector<size_t> simplex_index;

	/// <summary>
	/// �������� ��������� � ������ �����. ������ - �� ������������ ������ �������� � �����������,
	/// �� ���� �� ���������� ������������� �� ��������� ��� ���� � �� �� ��������.
	/// </summary>
	vector<double> simplex_value;

	/// <summary>
	/// ������� ����� �������� � ��������� ���������. 
	/// �����: ��� ������������� ��������� InitTrajectoryAsSimplex 
	/// </summary>
	void InitSimplexValues(const BaseFunction& bf);

	/// <summary>
	/// ������ ��������� �������� ��� ������ Nelder-Mead 
	/// </summary>
	void InitTrajectoryAsSimplex(const BaseArea& ba);

	/// <summary>
	/// ���������� ������ ���� ��� ���������
	/// ��� ����� �����.
	/// </summary>
	vector<double> MassCenter(const pair<size_t, size_t>& minmax_index);

	/// <summary>
	/// ����� ���������
	/// </summary>
	vector<double> Reflection(const vector<double>& x_n_2, const vector<double>& x_max, const BaseArea& ba);

	/// <summary>
	/// ����� ��������
	/// </summary>
	void Reduction(const pair<size_t, size_t>& minmax_index, const vector<double>& x_min);

	/// <summary>
	/// ����� ������ (� beta)
	/// </summary>
	/// <returns></returns>
	vector<double> Compression(const vector<double>& x_n_2, const vector<double>& x_max);

	/// <summary>
	/// ����� ����������
	/// </summary>
	vector<double> Stretching(const vector<double>& x_n_2, const vector<double>& x_n_3, const BaseArea& ba);

	/// <summary>
	/// ��������� ������� ��� �������� �� ���������� ����. ����� �����������, ��� ���
	/// ����������� �������������� ����������
	/// </summary>
	void CheckInput();

	/// <summary>
	/// ����� ��� ���������� �������� ������������ � ������������� ���������
	/// � ������ �������������� �������������
	/// </summary>
	/// <returns>���� ��������: ������� �������� � ���������</returns>
	pair<size_t, size_t> FindMinMaxIndex(const BaseFunction& bf) const;

	
};

