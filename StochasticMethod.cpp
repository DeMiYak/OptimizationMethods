#include "StochasticMethod.h"

void StochasticMethod::Optimize(const BaseArea& ba, const BaseFunction& bf, const BaseStopCriterion& bsc)
{
	/// ��������� ����� �� 0 �� 1
	mt19937 gen(rd());
	uniform_real_distribution<> distr(0, 1);
	
	size_t count = 0;
	/// ���������� ������� ����������
	trajectory.clear();
	trajectory.push_back(startPoint);

	/// �������� f() � ��������� �����.
	double f_min = bf(startPoint);

	/// �������
	vector<pair<double, double>> bounds = ba.GetBounds();
	
	/// ����� ������������ �������������, ������������� ������� ������������

	/// 1. �������� ��������� ����� � ������������ p, ���������� - 1-p
	vector<double> randVec;
	do {
		++count;
		double alpha = distr(gen);
		if (alpha < p) {
			/// ������ ��������� ������ � �������, ����� ����� ���������
			randVec = GlobalVectorSearch(bounds);
		}
		else {
			/// ������ ��������� ������ ������ n-������ �����, ����� ����� ���������
			randVec = LocalVectorSearch(bounds);
		}
		double f_rand = bf(randVec);
		if (f_rand < f_min) {
			f_min = f_rand;
			trajectory.push_back(randVec);
		}
	} while (!bsc.Check(trajectory, randVec, count));
}

void StochasticMethod::CheckInput()
{
	bool check = false;
	if (p <= 0 || p >= 1) {
		cout << endl << "Error: probability must be from 0 to 1.";
		check = true;
	}
	if (delta > 10) {
		cout << endl << "Error: large delta.";
		check = true;
	}
	if (check) {
		exit(1);
	}
}

vector<double> StochasticMethod::GlobalVectorSearch(const vector<pair<double, double>>& bounds) const
{
	/// ��������� ��������� �����
	mt19937 gen(rd());
	uniform_real_distribution<> distr(0, 1);
	
	vector<double> resVec;
	/// ������������� �������� ��������� �������� � ���������� bounds, ���������
	/// ����������� �� (0, 1) �������������� alpha.
	for (size_t i = 0; i < bounds.size(); ++i) {
		double temp1 = bounds[i].first, temp2 = bounds[i].second;
		double b = min(temp1, temp2);
		double a = fabs(temp1 - temp2);
		double alpha = distr(gen);
		resVec.push_back(alpha * a + b);
	}
	return resVec;
}

vector<double> StochasticMethod::LocalVectorSearch(const vector<pair<double, double>>& bounds) const
{
	/// ��������� ��������� �����
	mt19937 gen(rd());
	normal_distribution<double> nd(0, 1);

	size_t size = bounds.size() + 2;

	/// ������� ��������� ������
	vector<double> resVec;

	/// ����� ����, ������� ����������� ���������� ������������� �������.
	/// ���� ������ ����������, ���������� ����������� ������������� � n-������ ����.
	/// 
	/// ������������� ����������� (Voelker, 2017), ������� ����������, ���
	/// ������������� � n-���� ����������� ������������� � (n+1)-����� � ����� ������������ ������������.
	/// ������� ����������� ������������� �� ��������� n-���� + �������� �� delta**(1/n).
	
	/// �����
	double sum = 0;
	/// ��������� ������ ���������� ��������������
	for (size_t i = 0; i < size; ++i) {
		double normVal = nd(gen);
		sum += normVal * normVal;
		resVec.push_back(normVal);
	}
	/// ������� ������ ����������
	resVec.pop_back();
	resVec.pop_back();
	/// ������� ��������� ��� ����������
	size_t resSize = resVec.size();
	const double constVal = pow(delta,1./resSize)/sqrt(sum);

	/// ��������� ���������� ��� n-����
	for (size_t i = 0; i < resSize; ++i) {
		resVec[i] *= constVal;
	}
	return resVec;
}
