#include "Rectangle.h"

/// <summary>
/// �������� �� ���������� ����� ������ ������ (���������������).
/// true - ������ ��� �� �������, false - �������.
/// </summary>
/// <param name="point"></param>
/// <returns></returns>
bool Rectangle::IsInside(const vector<double>& point) const
{
	/// �������� �� ������������ ������������
	size_t psize = point.size();
	if (psize != bound.size()) {
		cout << endl << "Error: unequal sizes within IsInside" << endl;
		cout << "Look up line 15 at Rectangle.cpp";
		exit(EXIT_FAILURE);
	}

	/// ��������: ���� ���� �� ���� ���������� ������� - false.
	for (size_t i = 0; i < psize; ++i) {
		double pointTemp = point[i];
		if (pointTemp < bound[i].first || bound[i].second < pointTemp) {
			return false;
		}
	}
	return true;
}

/// <summary>
/// ��������� �����, ����������� ���������� ���������� �����-��������.
/// �������� �� ������������ �������� � ��������������� ���������������.
/// </summary>
/// <param name="fpt">������ �����</param>
/// <param name="spt">������ �����</param>
void Rectangle::CheckValidity(const vector<double>& fpt, const vector<double>& spt)
{
	if (fpt.size() != spt.size()) {
		cout << endl << "Error: unequal sizes in Rectangle function." << endl;
		cout << "Look up line 7 at Rectangle.h";
		exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < fpt.size(); ++i) {
		if (fpt[i] == spt[i]) {
			cout << endl << "Error: degenerate rectangle (some coordinates coincide)" << endl;
			cout << "Look up line 6 at Rectangle.cpp";
			exit(EXIT_FAILURE);
		}
	}
}
