#pragma once
#include<vector>
#include<iostream>

using namespace std;

/// <summary>
/// ������� ����� �������, ������� ����� �������������� ���
/// ������������ ����������������� ������ ������������� �������������� (Nelder-Mead).
/// </summary>
class BaseFunction {
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="_dim">����������� ������� (����� ����������� ����������)</param>
	BaseFunction(size_t _dim) :dim(_dim) {};

	BaseFunction(const BaseFunction& bf) : dim(bf.dim) {};

	BaseFunction(BaseFunction&& bf) noexcept : dim(bf.dim) {};
	/// <summary>
	/// ������ �����������
	/// </summary>
	/// <returns>�����������</returns>
	virtual size_t const GetDim() { return dim; }
	/// <summary>
	/// ��������() ��� ���������� �������� � �����
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	virtual double operator()(const vector<double>& x) const = 0;
	/// <summary>
	/// �������, ������������ �������� (�� ���� ������ ����� ��� vector<double>)
	/// </summary>
	virtual vector<double> GetGradient() = 0;
protected:
	const size_t dim;
};