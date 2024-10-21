#pragma once
#include<vector>

using namespace std;

//enum NORM{TWO, ONE, INFTY};
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