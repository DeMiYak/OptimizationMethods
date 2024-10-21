#include "NelderMeadStopCriterion.h"

bool NelderMeadStopCriterion::Check(const vector<vector<double>>& trajectory, const vector<double>& vec, const size_t& count) const
{
	return false;
}

/// <summary>
/// ����� ��������� �������� ��� Nelder-Mead. 
/// ���������: ���������� BaseFunction, ������, ����� ��������� �� ������������
/// �����������. ����� �����, ����� �������� �������������� ������ � BaseFunction, ��� 
/// ��� ������ ��� ���������� ����� ��� ����������
/// </summary>
/// <param name="trajectory">���������� ������ �����������</param>
/// <param name="bf">������� �������</param>
/// <returns>TRUE - �����������, FALSE - �� �����������.</returns>
bool NelderMeadStopCriterion::Check(const vector<vector<double>>& trajectory, const vector<size_t>& simplex_index, const BaseFunction& bf, const double& f_n_2, const size_t& count) const
{
	/// �����
	double sum = 0;
	size_t size = simplex_index.size();

	/// ���������� ����� sum
	for (size_t k = 0; k < size; ++k) {
		double f_k = bf(trajectory[simplex_index[k]]);
		sum += (f_k - f_n_2)*(f_k - f_n_2);
	}

	/// �������� �����. Size > 1, ��� ��� ��������� � n-������ ������������
	/// ����������� n+1.
	sum = sqrt(sum / (size - 1));
	return sum <= eps ? true : BaseStopCriterion::Check(count);
}

//bool NelderMeadStopCriterion::Check(const DataTransfer& dt) const
//{
//	const vector<size_t>& simplex_index(dt.GetSimplexIndex());
//	const vector<vector<double>>& trajectory(dt.GetTrajectory());
//	const BaseFunction& bf(dt.GetBaseFunction());
//	const double& f_n_2(dt.GetFVal());
//	const size_t& count(dt.GetCount());
//	double sum = 0;
//	size_t size = simplex_index.size();
//
//	/// ���������� ����� sum
//	for (size_t k = 0; k < size; ++k) {
//		double f_k = bf(trajectory[simplex_index[k]]);
//		sum += (f_k - f_n_2) * (f_k - f_n_2);
//	}
//
//	/// �������� �����. Size > 1, ��� ��� ��������� � n-������ ������������
//	/// ����������� n+1.
//	sum = sqrt(sum / (size - 1));
//	return sum <= eps ? true : BaseStopCriterion::Check(count);
//}
