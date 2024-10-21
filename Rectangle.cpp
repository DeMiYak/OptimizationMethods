#include "Rectangle.h"

/// <summary>
/// ѕроверка на нахождение точки внутри фигуры (параллелипипеда).
/// true - внутри или на границе, false - снаружи.
/// </summary>
/// <param name="point"></param>
/// <returns></returns>
bool Rectangle::IsInside(const vector<double>& point) const
{
	/// ѕроверка на соответствие размерностей
	size_t psize = point.size();
	if (psize != bound.size()) {
		cout << endl << "Error: unequal sizes within IsInside" << endl;
		cout << "Look up line 15 at Rectangle.cpp";
		exit(EXIT_FAILURE);
	}

	/// ѕроверка: если хот€ бы одна координата снаружи - false.
	for (size_t i = 0; i < psize; ++i) {
		double pointTemp = point[i];
		if (pointTemp < bound[i].first || bound[i].second < pointTemp) {
			return false;
		}
	}
	return true;
}

/// <summary>
/// ѕриватный метод, провер€ющий валидность полученных точек-векторов.
/// ѕроверка на соответствие размеров и невырожденность параллелипипеда.
/// </summary>
/// <param name="fpt">ѕерва€ точка</param>
/// <param name="spt">¬тора€ точка</param>
void Rectangle::CheckValidity(const vector<double>& fpt, const vector<double>& spt)
{
	if (fpt.size() != spt.size()) {
		cout << endl << "Error: unequal sizes in Rectangle function." << endl;
		cout << "Look up line 7 at Rectangle.h";
		exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < fpt.size(); ++i) {
		if (fpt[i] == spt[i]) {
			cout << endl << "Error: degenerate rectangle (some coordinates coincide)" << endl;
			cout << "Look up line 6 at Rectangle.cpp";
			exit(EXIT_FAILURE);
		}
	}
}
