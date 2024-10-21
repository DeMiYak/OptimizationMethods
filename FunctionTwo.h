#pragma once
#include "BaseFunction.h"

/// <summary>
/// ������� ����������
/// </summary>
class FunctionTwo : public BaseFunction
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="_dim">����������� ������� (����� ����������� ����������)</param>
	FunctionTwo() : BaseFunction(2) {};

	FunctionTwo(const FunctionTwo& fo) : BaseFunction(fo.dim) {};

	FunctionTwo(FunctionTwo&& fo) noexcept : BaseFunction(fo.dim) {};
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

	virtual vector<double> GetGradient() override;
private:
};

