#include "FunctionOne.h"

double FunctionOne::operator()(const vector<double>& x) const
{
    /// ����� ��������� ���������� ������
    if (dim != x.size()) {
        cout << endl << "Error: wrong vector size.";
        exit(1);
    }
    return x[0] * x[0];
}

vector<double> FunctionOne::GetGradient()
{
    return vector<double>();
}
