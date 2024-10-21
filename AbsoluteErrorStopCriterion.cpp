#include "AbsoluteErrorStopCriterion.h"

double Norm(const vector<double>& vec) {
	double sum = 0;
	for (size_t i = 0; i < vec.size(); ++i) {
		sum += vec[i] * vec[i];
	}
	return sqrt(sum);
}

vector<double> Subtract(const vector<double>& vec1, const vector<double>& vec2) {
	vector<double> temp;
	for (size_t i = 0; i < vec1.size(); ++i) {
		temp.push_back(vec1[i] - vec2[i]);
	}
	return temp;
}

bool AbsoluteErrorStopCriterion::Check(const vector<vector<double>>& trajectory, const vector<double>& vec, const size_t& count) const
{
	/// Проверка на переизбыток по числу итераций
	size_t size = trajectory.size();
	if (Norm(Subtract(trajectory[size-1], trajectory[size-2])) < eps) {
		return true;
	}
	return BaseStopCriterion::Check(count);
}

bool AbsoluteErrorStopCriterion::Check(const vector<vector<double>>& trajectory, const vector<size_t>& simplex_index, const BaseFunction& bf, const double& f_n_2, const size_t& count) const
{
	return false;
}
