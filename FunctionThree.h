#pragma once
#include"BaseFunction.h"

/// <summary>
/// �������-����� ������� ����
/// </summary>
class FunctionThree : public BaseFunction
{
public:
	/// <summary>
	/// �����������
	/// </summary>
	/// <param name="_dim">����������� ������� (����� ����������� ����������)</param>
	FunctionThree() : BaseFunction(3) {};

	FunctionThree(const FunctionThree& fo) : BaseFunction(fo.dim) {};

	FunctionThree(FunctionThree&& fo) noexcept : BaseFunction(fo.dim) {};
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

