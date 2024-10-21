#pragma once
#include"BaseArea.h"

/// <summary>
/// Класс симплексов, который создаёт n-мерный симплекс с указанной длиной между точками.
/// Рудиментарный класс, который по идее, независимо реализуется в BaseOptMethod::Optimize()
/// </summary>
class Simplex : public BaseArea {
public:
	/// <summary>
	/// Конструтор симплекса, который создаёт симплекс с одной из точек в центре координат
	/// </summary>
	/// <param name="dim">Размерность симплекса</param>
	/// <param name="_dot_dist">Расстояние между точками симплекса</param>
	Simplex(int dim, double _dot_dist = 1) : 
		BaseArea(), 
		dot_dist(_dot_dist),
		simplex(vector<vector<double>>(dim, vector<double>(dim+1, 0))){
		double d1 = dot_dist * (sqrt(dim + 1) + dim - 1) / (dim * sqrt(2));
		double d2 = dot_dist * (sqrt(dim + 1) - 1) / (dim * sqrt(2));
		
		/// Заполнение симплекса соответствующими значениями
		for (int i = 0; i < dim; ++i) {
			for (int k = 1; k < dim + 1; ++k) {
				/// Условие: если равны на диагонали, то d1, а если
				/// нет, то d2 (см. Simplex.png).
				if (k - 1 == i) {
					simplex[i][k] = d1;
				}
				else simplex[i][k] = d2;
			}
		}
	}
private:
	vector<vector<double>> simplex;
	double dot_dist;
};