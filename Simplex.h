#pragma once
#include"BaseArea.h"

/// <summary>
/// ����� ����������, ������� ������ n-������ �������� � ��������� ������ ����� �������.
/// ������������� �����, ������� �� ����, ���������� ����������� � BaseOptMethod::Optimize()
/// </summary>
class Simplex : public BaseArea {
public:
	/// <summary>
	/// ���������� ���������, ������� ������ �������� � ����� �� ����� � ������ ���������
	/// </summary>
	/// <param name="dim">����������� ���������</param>
	/// <param name="_dot_dist">���������� ����� ������� ���������</param>
	Simplex(int dim, double _dot_dist = 1) : 
		BaseArea(), 
		dot_dist(_dot_dist),
		simplex(vector<vector<double>>(dim, vector<double>(dim+1, 0))){
		double d1 = dot_dist * (sqrt(dim + 1) + dim - 1) / (dim * sqrt(2));
		double d2 = dot_dist * (sqrt(dim + 1) - 1) / (dim * sqrt(2));
		
		/// ���������� ��������� ���������������� ����������
		for (int i = 0; i < dim; ++i) {
			for (int k = 1; k < dim + 1; ++k) {
				/// �������: ���� ����� �� ���������, �� d1, � ����
				/// ���, �� d2 (��. Simplex.png).
				if (k - 1 == i) {
					simplex[i][k] = d1;
				}
				else simplex[i][k] = d2;
			}
		}
	}
private:
	vector<vector<double>> simplex;
	double dot_dist;
};