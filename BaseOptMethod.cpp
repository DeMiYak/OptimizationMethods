#include"BaseOptMethod.h"

/// <summary>
/// Метод корректировки точке в случае 
/// </summary>
/// <param name="fixedPoint"></param>
/// <param name="adjustablePoint"></param>
/// <param name="ba"></param>
void BaseOptMethod::CorrectPointPlacement(const vector<double>& fixedPoint, vector<double>& adjustablePoint, const BaseArea& ba)
{
	/// Какая идея: точка может быть расположена по-разному. Нужно 
	/// учитывать направление по каждой из координат. Либо i-ая координата
	/// фиксированной точки меньше изменяемой, либо больше.
	
	/// Если изменяемая точка внутри
	if (ba.IsInside(adjustablePoint)) {
		return;
	}
	/// alpha - коэффициент сжатия. Он не превосходит 1, так как изменяемая точка
		/// находится вне области
	double alpha = 1;
	const vector<pair<double, double>>& bounds = ba.GetBounds();

	/// Вектор между изменяемой и фиксированной точками
	vector<double> diffVector(adjustablePoint);
	/// Определяем минимум alpha и вычисляем diffVector
	for (size_t i = 0; i < bounds.size(); ++i) {
		double adCoord = adjustablePoint[i];
		double fixCoord = fixedPoint[i];
		/// Вектор
		diffVector[i] -= fixCoord;
		double diff = fabs(adCoord - fixCoord);
		/// Если изменяемая координата меньше фиксированной - считаем отношение
		/// разницы этих координат к разнице длины отрезка от нижней границы до фиксированной координаты.
		/// 
		/// Кроме того, необходимо учитывать случай, когда границы близки к фиксированной точке
		if (adCoord < fixCoord) {
			alpha = min(alpha, fabs(bounds[i].first - fixCoord) / diff);
		}
		else if(adCoord > fixCoord) {
			alpha = min(alpha, fabs(bounds[i].second - fixCoord) / diff);
		}

		/// Имеем alpha 
	}
	/// Меняем значения вектора
	for (size_t i = 0; i < diffVector.size(); ++i) {
		diffVector[i] *= alpha;
	}

	/// Меняем изменяемую точку
	for (size_t i = 0; i < diffVector.size(); ++i) {
		adjustablePoint[i] = fixedPoint[i] + diffVector[i] * alpha;
	}
}
