#pragma once
#include<vector>
#include"BaseStopCriterion.h"
#include"BaseArea.h"
#include"BaseFunction.h"
#include"DataTransfer.h"
using namespace std;
/// <summary>
/// ������� ����� ��� ���������� ������� ����������� (���������� �����������).
/// ���� ������������ ����������� ������ ����� ������������� �������������� (Nelder-Mead).
/// ��������� ������, ��� ������� ����������? �������, ��� ��� ����� ������ ���� �������
/// ������ �����, ������� ��������������, ���� ���������� (��� ����������� ��� ��������� �������).
/// </summary>
class BaseOptMethod {
public:
	/// <summary>
	/// ����������� ��� �������� ������ � ����������-��������
	/// </summary>
	/// <param name="startPoint">��������� �����</param>
	explicit BaseOptMethod(const vector<double>& startPoint) : startPoint(startPoint) {};

	BaseOptMethod(const BaseOptMethod& bom) : startPoint(bom.startPoint) {};

	BaseOptMethod(BaseOptMethod&& bom) noexcept : startPoint(move(bom.startPoint)) {};

	/// <summary>
	/// ����������� ����� �����������, ������� 
	/// </summary>
	/// <param name="ba">�������, ������ ������� ����� ������������� �����
	/// ����������</param>
	/// <param name="bf">�������, �������� � ��������� �������, ������� �� �����������
	/// ������� � BaseArea. �����, ����� ������� �� BaseArea, ����������� � ������� �����������
	/// ����� �������.</param>
	/// <param name="bsc">�������� ���������. ��������������, ��� ����� ����������� ��������
	/// ����������, � ��� ����, ����� ����� ���������� �� �������� �����, ���������� ����������
	/// ��������, �� �������� ����� ����� ��������������� � ������ ������� � �����������
	/// ���������. </param>
	virtual void Optimize(const BaseArea& ba, const BaseFunction& bf, const BaseStopCriterion& bsc) = 0;

	/// <summary>
	/// ������ ��� ��������� �����
	/// </summary>
	/// <param name="_startPoint">��������� �����</param>
	void SetStartPoint(const vector<double>& _startPoint) { startPoint = _startPoint; trajectory.clear(); };
	vector<vector<double>> GetTrajectory() const { return trajectory; };
	vector<double> GetStartPoint() const { return startPoint; };
protected:
	vector<double> startPoint;
	vector<vector<double>> trajectory;
	DataTransfer dt;
	/// <summary>
	/// ����� ��� ������������� ��������� ����� � ������ 
	/// ������ �� ������� �������
	/// </summary>
	/// <param name="fixedPoint">������������� �����, ������������ ������� 
	/// ��������������� ��������� ���������� ����� </param>
	/// <param name="adjustablePoint">���������� �����, ��� ������� �������������� ���������</param>
	/// <param name="ba">�������</param>
	void CorrectPointPlacement(const vector<double>& fixedPoint, vector<double>& adjustablePoint, const BaseArea& ba);
};