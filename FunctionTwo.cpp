#include "FunctionTwo.h"

double FunctionTwo::operator()(const vector<double>& x) const
{
    /// Функция Розенброка
    if (dim != x.size()) {
        cout << endl << "Error: wrong vector size.";
        exit(1);
    }
    return (1 - x[0]) * (1 - x[0]) + 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]);
}

vector<double> FunctionTwo::GetGradient()
{
    return vector<double>();
}
