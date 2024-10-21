#pragma once
#include "BaseFunction.h"

/// <summary>
/// ������� �����
/// </summary>
class FunctionOne : public BaseFunction
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="_dim">����������� ������� (����� ����������� ����������)</param>
	FunctionOne() : BaseFunction(1) {};

	FunctionOne(const FunctionOne& fo) : BaseFunction(fo.dim) {};

	FunctionOne(FunctionOne&& fo) noexcept : BaseFunction(fo.dim) {};
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
	virtual double operator()(const vector<double>& x) const;
	/// <summary>
	/// �������, ������������ �������� (�� ���� ������ ����� ��� vector<double>)
	/// </summary>
	virtual vector<double> GetGradient() override;
private:
};

