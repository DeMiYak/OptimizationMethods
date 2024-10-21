#include "Printer.h"

void Printer::PrintData(const BaseOptMethod& bom)
{
	const vector<vector<double>>& trajectory = bom.GetTrajectory();
	size_t size = trajectory.size();
	cout << endl << "Trajectory length: " << size;
	for (size_t i = 0; i < size; ++i) {
		PrintVector(trajectory[i]);
	}
	cout << endl;
}

void Printer::PrintVector(const vector<double>& vec)
{
	cout << endl;
	for (size_t i = 0; i < vec.size(); i++) {
		cout << vec[i] << '\t';
	}
}
