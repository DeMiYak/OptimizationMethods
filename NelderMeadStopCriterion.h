#pragma once
#include "BaseStopCriterion.h"

/// <summary>
/// Специальный критерий остановки Nelder-Mead
/// </summary>
class NelderMeadStopCriterion : public BaseStopCriterion
{
public:
	NelderMeadStopCriterion(size_t iter_num, double eps = 1e-6) :
		BaseStopCriterion(iter_num),
		eps(eps) {};
	virtual bool Check(const vector<vector<double>>& trajectory, const vector<double>& vec, const size_t& count) const;
	virtual bool Check(const vector<vector<double>>& trajectory, const vector<size_t>& simplex_index, const BaseFunction& bf, const double& f_n_2, const size_t& count) const override;
	//virtual bool Check(const DataTransfer& dt) const override;
private:
	double eps;
};

