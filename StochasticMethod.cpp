#include "StochasticMethod.h"

void StochasticMethod::Optimize(const BaseArea& ba, const BaseFunction& bf, const BaseStopCriterion& bsc)
{
	/// Генератор чисел от 0 до 1
	mt19937 gen(rd());
	uniform_real_distribution<> distr(0, 1);
	
	size_t count = 0;
	/// Подготовка вектора траекторий
	trajectory.clear();
	trajectory.push_back(startPoint);

	/// Значение f() в начальной точке.
	double f_min = bf(startPoint);

	/// Границы
	vector<pair<double, double>> bounds = ba.GetBounds();
	
	/// Чтобы генерировать распределение, воспользуемся методом декомпозиции

	/// 1. Выбираем локальный поиск с вероятностью p, глобальный - 1-p
	vector<double> randVec;
	do {
		++count;
		double alpha = distr(gen);
		if (alpha < p) {
			/// Создаём случайный вектор в области, затем жадно проверяем
			randVec = GlobalVectorSearch(bounds);
		}
		else {
			/// Создаём случайный вектор внутри n-мерной сферы, затем жадно проверяем
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
	/// Генерация случайных чисел
	mt19937 gen(rd());
	uniform_real_distribution<> distr(0, 1);
	
	vector<double> resVec;
	/// Покоординатно выбираем случайные значения в диапазонах bounds, пользуясь
	/// равномерным на (0, 1) распределением alpha.
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
	/// Генерация случайных чисел
	mt19937 gen(rd());
	normal_distribution<double> nd(0, 1);

	size_t size = bounds.size() + 2;

	/// Искомый случайный вектор
	vector<double> resVec;

	/// Может быть, следует реализовать нормальное распределение вручную.
	/// Есть разные результаты, позволящие реализовать распределение в n-мерном шаре.
	/// 
	/// Воспользуемся результатом (Voelker, 2017), которое показывает, что
	/// распределение в n-шаре равносильно распределению в (n+1)-сфере с двумя отброшенными координатами.
	/// Получим равномерное распределение на единичном n-шаре + домножим на delta**(1/n).
	
	/// Сумма
	double sum = 0;
	/// Заполняем вектор нормальным распределением
	for (size_t i = 0; i < size; ++i) {
		double normVal = nd(gen);
		sum += normVal * normVal;
		resVec.push_back(normVal);
	}
	/// Убираем лишние координаты
	resVec.pop_back();
	resVec.pop_back();
	/// Считаем константу для вычислений
	size_t resSize = resVec.size();
	const double constVal = pow(delta,1./resSize)/sqrt(sum);

	/// Вычисляем координаты для n-шара
	for (size_t i = 0; i < resSize; ++i) {
		resVec[i] *= constVal;
	}
	return resVec;
}
