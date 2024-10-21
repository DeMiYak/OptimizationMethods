#include"BaseOptMethod.h"

/// <summary>
/// ����� ������������� ����� � ������ 
/// </summary>
/// <param name="fixedPoint"></param>
/// <param name="adjustablePoint"></param>
/// <param name="ba"></param>
void BaseOptMethod::CorrectPointPlacement(const vector<double>& fixedPoint, vector<double>& adjustablePoint, const BaseArea& ba)
{
	/// ����� ����: ����� ����� ���� ����������� ��-�������. ����� 
	/// ��������� ����������� �� ������ �� ���������. ���� i-�� ����������
	/// ������������� ����� ������ ����������, ���� ������.
	
	/// ���� ���������� ����� ������
	if (ba.IsInside(adjustablePoint)) {
		return;
	}
	/// alpha - ����������� ������. �� �� ����������� 1, ��� ��� ���������� �����
		/// ��������� ��� �������
	double alpha = 1;
	const vector<pair<double, double>>& bounds = ba.GetBounds();

	/// ������ ����� ���������� � ������������� �������
	vector<double> diffVector(adjustablePoint);
	/// ���������� ������� alpha � ��������� diffVector
	for (size_t i = 0; i < bounds.size(); ++i) {
		double adCoord = adjustablePoint[i];
		double fixCoord = fixedPoint[i];
		/// ������
		diffVector[i] -= fixCoord;
		double diff = fabs(adCoord - fixCoord);
		/// ���� ���������� ���������� ������ ������������� - ������� ���������
		/// ������� ���� ��������� � ������� ����� ������� �� ������ ������� �� ������������� ����������.
		/// 
		/// ����� ����, ���������� ��������� ������, ����� ������� ������ � ������������� �����
		if (adCoord < fixCoord) {
			alpha = min(alpha, fabs(bounds[i].first - fixCoord) / diff);
		}
		else if(adCoord > fixCoord) {
			alpha = min(alpha, fabs(bounds[i].second - fixCoord) / diff);
		}

		/// ����� alpha 
	}
	/// ������ �������� �������
	for (size_t i = 0; i < diffVector.size(); ++i) {
		diffVector[i] *= alpha;
	}

	/// ������ ���������� �����
	for (size_t i = 0; i < diffVector.size(); ++i) {
		adjustablePoint[i] = fixedPoint[i] + diffVector[i] * alpha;
	}
}
