#pragma once
#include<vector>
#include"BaseFunction.h"
#include"DataTransfer.h"

using namespace std;



/// <summary>
/// ������� ����� �������� ���������.
/// ����� iter_num, ����� ������� �� ������������ �� ����� ��������
/// </summary>
class BaseStopCriterion {
public:
	/// <summary>
	/// ����������� �������� ������. ������ ���������� ���������
	/// ��������� �������� ���������, ������ �������� ��������� ��������� �����
	/// ���������� ��������� ����� ��������. � ��������� ������ ���� ���� �����
	/// � ����������� ����.
	/// </summary>
	/// <param name="iter_num">����� ��������</param>
	BaseStopCriterion(size_t iter_num) : iter_num(iter_num) {};
	/// <summary>
	/// ����� �������� ���������� �� �������� ���������.
	/// ����� ��������, ��� ���� ������ ���������� �������, � ������ - ���.
	/// ����� ������, ��� ��� ���� ������ ��������� ��������� ����������� Check?
	/// </summary>
	/// <param name="trajectory">���������� ������ �����������</param>
	/// <returns>������� ��������, ���� TRUE - ������� �������� ���������
	/// ��������� � ����� ������������� ������, FALSE - �����.</returns>
	virtual bool Check(const vector<vector<double>>& trajectory, const vector<double>& vec, const size_t& count) const = 0;
	virtual bool Check(const vector<vector<double>>& trajectory, const vector<size_t>& simplex_index, const BaseFunction& bf, const double& f_n_2, const size_t& count) const = 0;
	//virtual bool Check(const DataTransfer& dt) const = 0;
	/// <summary>
	/// ����� �������� �� ���������� ����� ��������
	/// </summary>
	/// <param name="count"></param>
	/// <returns></returns>
	virtual bool Check(const size_t& count) const;
protected:
	/// <summary>
	/// ����� ��������
	/// </summary>
	size_t iter_num;

};