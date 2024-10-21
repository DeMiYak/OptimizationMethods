#pragma once
#include "BaseStopCriterion.h"

//enum NORM{TWO, ONE, INFTY};
double Norm(const vector<double>& vec);

vector<double> Subtract(const vector<double>& vec1, const vector<double>& vec2);

class AbsoluteErrorStopCriterion : public BaseStopCriterion
{
public:
	AbsoluteErrorStopCriterion(size_t iter_num, double eps = 1e-6) :
		BaseStopCriterion(iter_num),
		eps(eps) {};

	virtual bool Check(const vector<vector<double>>& trajectory, const vector<double>& vec, const size_t& count) const override;
	virtual bool Check(const vector<vector<double>>& trajectory, const vector<size_t>& simplex_index, const BaseFunction& bf, const double& f_n_2, const size_t& count) const override;

private:
	double eps;
};

