#include "NelderMeadMethod.h"
#include"algorithm"

/// В процессе отладки
/// InitTrajectoryAsSimplex - корректен
/// FindMinMaxIndex - корректен
/// MassCenter - корректен
/// Reflection - корректен
/// Compression - ...
/// Stretching - ...
/// Reduction - ...

/// <summary>
/// Optimize звучит так, как будто в классе есть некоторая точка, и мы хотим её
/// оптимизировать. Учитывая то, что на лекции говорили об void методе, кажется, что
/// требуется изменять именно поля класса.
/// </summary>
/// <param name="ba">Базовая область</param>
/// <param name="bf">Базовая функция</param>
/// <param name="bsc">Базовый критерий остановки</param>
void NelderMeadMethod::Optimize(const BaseArea& ba, const BaseFunction& bf, const BaseStopCriterion& bsc)
{
	//dt.SetBaseFunction(bf);

	size_t dim = startPoint.size();
	InitTrajectoryAsSimplex(ba);
	/*InitSimplexValues(bf);*/
	/// Значение f_n_2, поскольку оно требуется для проверки критерия остановки
	double f_n_2 = 0;
	/// Число итераций
	size_t count = 0;
	
	//dt.SetCount(count);
	//dt.SetFVal(f_n_2);
	//dt.SetSimplexIndex(simplex_index);
	//dt.SetSimplexValues(simplex_value);
	//dt.SetTrajectory(trajectory);
	do {
		++count;
		//dt.SetCount(++count);
		/// Цикл для создания точек с соответствующими методами
		pair<size_t, size_t> minmax_index = FindMinMaxIndex(bf);
		/// Минимум-максимум на симплексе
		
		// Вычислить x_h, x_l и c_m.
		//--------------------------------------------------------------------------------------
		/// Точка минимума симплекса
		vector<double> x_min = trajectory[simplex_index[minmax_index.first]];
		/// Значение в индексе минимума
		double f_min = bf(x_min);
		
		/// Точка максимума симплекса
		vector<double> x_max = trajectory[simplex_index[minmax_index.second]];
		/// Значение в индексе максимума
		double f_max = bf(x_max);

		/// 0. Вычисление центра масс без одной точки
		/// На данном этапе центр масс вычисляется без корректировок относительно области.
		/// Для каждого метода необходимо соблюсти принадлежность точки-вектора области.
		vector<double> x_n_2 = MassCenter(minmax_index);
		
		/// x_n_2 внутри области как центр масс, поэтому корректировать точку не нужно
		f_n_2 = bf(x_n_2);
		//dt.SetFVal(f_n_2);
		//--------------------------------------------------------------------------------------

		// Отражение: вычислить
		//--------------------------------------------------------------------------------------
		/// 1. Отражение. Может выйти за пределы
		vector<double> x_n_3 = Reflection(x_n_2, x_max, ba);
		//--------------------------------------------------------------------------------------

		// Вычислить f_n_3
		//--------------------------------------------------------------------------------------
		/// 2. Выбор изменения многогранника (деформируем многогранник,
		/// исходя из значения в точке отражения)
		double f_n_3 = bf(x_n_3);
		//--------------------------------------------------------------------------------------
		
		/// 3. Проверка, вход в if-условие,
		/// получение итоговой точки траектории для начала следующей итерации.
		
		// Выполняется ли неравенство?
		//--------------------------------------------------------------------------------------
		/// Случай растяжения (Stretching). В этом случае нужно проверять на выход за границы.
		if (f_n_3 < f_max) {
			// ДА
			//--------------------------------------------------------------------------------------

			// Растяжение
			//--------------------------------------------------------------------------------------
			vector<double> x_n_4 = Stretching(x_n_2, x_n_3, ba);
			size_t size = trajectory.size();
			// Вычислить f_n_4
			//--------------------------------------------------------------------------------------
			double f_n_4 = bf(x_n_4);
			
			// Выполняется ли неравенство
			//--------------------------------------------------------------------------------------
			/// В траекторию добавляется точка x_n_4
			if (f_n_4 < f_min) {
				// ДА
				//--------------------------------------------------------------------------------------
				/// Сдвиг к краю траектории (так как точки промежуточно высчитываются там,
				/// что может быть не самой лучшей идеей
				/// Пользуясь тем соображением, что промежуточные вычисления внутри поля,
				/// выделенного для других целей - плохо, сделаем так, чтобы методы возвращали вектора.
				trajectory.push_back(x_n_4);
			}
			/// В траекторию добавляется точка x_n_3
			else {
				// НЕТ
				//--------------------------------------------------------------------------------------
				trajectory.push_back(x_n_3);
			}

			/// Меняем индекс точки максимума на другую (только что
			/// добавили в конец)
			simplex_index[minmax_index.second] = trajectory.size() - 1;
		}
		else {
			// НЕТ
			//--------------------------------------------------------------------------------------
			
			// Выполняется ли неравенство для всех i != h?
			//--------------------------------------------------------------------------------------
			/// Проверка неравенств на условие сжатия
			/// Совет: добавить вектор для f(x_i), это сэкономит память при вычислениях
			bool check = true;
			for (size_t i = 0; i < dim + 1; ++i) {
				// Перебираем по всем x_i, кроме x_h.
				// Если хотя бы для одного i: f_n_3 >= f_i - НЕТ
				if (i != minmax_index.second) {
					double f_i = bf(trajectory[simplex_index[i]]);
					if (f_n_3 >= f_i) {
						check = false;
						break;
					}
				}
			}

			if (!check) {
				// ДА
				//--------------------------------------------------------------------------------------
				
				// Выполняется ли равенство?
				//--------------------------------------------------------------------------------------
				/// Заменяем x_max на x_n_3
				if (f_n_3 >= bf(trajectory[simplex_index[minmax_index.second]])) {
					// НЕТ
					//--------------------------------------------------------------------------------------
					x_max = x_n_3;
				}

				// Сжатие: вычислить
				//--------------------------------------------------------------------------------------
				/// Сжатие. Для этого метода не нужно корректировать точку, так как
				/// это было проделано в Reflection.
				vector<double> x_n_5 = Compression(x_n_2, x_max);
				
				// Вычислить f_n_5
				//--------------------------------------------------------------------------------------
				/// Вычисление f(x_n_5)
				double f_n_5 = bf(x_n_5);
				if (f_n_5 > f_max) {
					// ДА
					//--------------------------------------------------------------------------------------
					
					// Редукция
					//--------------------------------------------------------------------------------------
					/// Редукция. Причём, минимум и максимум могут измениться
					/// (по понятным причинам). Все точки располагаются внутри симплекса, поэтому
					/// корректировать эти точки не нужно.
					Reduction(minmax_index, x_min);
				}
				else {
					// НЕТ
					//--------------------------------------------------------------------------------------
					
					// Замена x_max на x_n_5
					//--------------------------------------------------------------------------------------
					/// Получили новую точку посредством замены
					trajectory.push_back(x_n_5);
					/// Поменяли индекс симплекса, который отслеживает
					/// необходимые точки, образующие многограннник
					simplex_index[minmax_index.second] = trajectory.size() - 1;
				}
			}
			else {
				// НЕТ
				//--------------------------------------------------------------------------------------
				/// Замена x_max на x_n_3 
				trajectory.push_back(x_n_3);
				simplex_index[minmax_index.second] = trajectory.size() - 1;
			}
		}
	/*	dt.SetSimplexIndex(simplex_index);
		dt.SetTrajectory(trajectory);*/
	/// Возможно, метод Check можно обобщить, сделав новый класс, который хранить необходимые данные
	} 
	while (!bsc.Check(trajectory, simplex_index, bf, f_n_2, count));
	/*while (!bsc.Check(dt));*/
}

void NelderMeadMethod::InitSimplexValues(const BaseFunction& bf)
{
	simplex_value.clear();
	/// Здесь предполагается, что trajectory.size() = startPoint.size() + 1.
	for (size_t i = 0; i < trajectory.size(); ++i) {
		simplex_value.push_back(bf(trajectory[i]));
	}
}

/// <summary>
/// Реализация построения симплекса. Вопрос может возникнуть с тем,
/// как проверить, что симплекс лежит внутри параллелипипеда.
/// 
/// Проверка симплекса пока не реализована.
/// </summary>
void NelderMeadMethod::InitTrajectoryAsSimplex(const BaseArea& ba)
{
	/// Удаляем траекторию и добавляем начальную точку
	trajectory.clear();
	trajectory.push_back(startPoint);
	size_t size = startPoint.size();
	double d1 = t / (size * sqrt(2)) * (sqrt(size + 1) + size - 1);
	double d2 = t / (size * sqrt(2)) * (sqrt(size + 1)  - 1);
	/// Создаём копию для построения симплекса
	vector<double> copy(startPoint);
	

	/// Создание точки со сдвигом (как в симплексе)
	copy[0] += d1;
	for (size_t i = 1; i < size; ++i) {
		copy[i] += d2;
	}

	/// Создание симплекса - заполнение траектории первыми точками
	for (size_t i = 1; i < size; ++i) {
		trajectory.push_back(copy);
		/// Заменяем d1 на d2 и d2 на d1
		copy[i] = startPoint[i] + d1;
		copy[i - 1] = startPoint[i - 1] + d2;
	}
	trajectory.push_back(copy);

	/// Построение вектора индексов симплекса. Он будет отвечать за
	/// индексы симплекса на каждой итерации. Так можно заменить
	/// построение отдельного симплекса
	simplex_index.clear();
	for (size_t i = 0; i < size+1; ++i) {
		simplex_index.push_back(i);
	}

	/// Корректируем точки
	for (size_t i = 1; i < trajectory.size(); ++i) {
		CorrectPointPlacement(startPoint, trajectory[i], ba);
	}
}

vector<double> NelderMeadMethod::MassCenter(const pair<size_t, size_t>& minmax_index)
{
	/// Размерность точки 
	size_t size = startPoint.size();
	size_t index_max = simplex_index[minmax_index.second];
	vector<double> x_n_2(size, 0);

	/// Пробегаемся по точкам симплекса, прибавляя
	/// все, кроме точки, на которой достигается максимум
	for (size_t i = 0; i < size + 1; ++i) {
		if (index_max != simplex_index[i]) {
			/// Сокращённое покоординатное сложение
			//transform(x_n_2.begin(), x_n_2.end(), trajectory[simplex_index[i]].begin(), x_n_2.begin(), plus<double>());
			for (size_t k = 0; k < size; ++k) {
				x_n_2[k] += trajectory[simplex_index[i]][k];
			}
		}
	}

	/// Усреднение точек
	for (size_t i = 0; i < size; ++i) {
		x_n_2[i] /= size;
	}
	return x_n_2;
}

vector<double> NelderMeadMethod::Reflection(const vector<double>& x_n_2, const vector<double>& x_max, const BaseArea& ba)
{
	size_t size = startPoint.size();
	vector<double> x_n_3(x_n_2);
	/// Вычисление отражения
	for (size_t i = 0; i < size; ++i) {
		x_n_3[i] += alpha * (x_n_2[i] - x_max[i]);
	}
	CorrectPointPlacement(x_n_2, x_n_3, ba);
	return x_n_3;
}

void NelderMeadMethod::Reduction(const pair<size_t, size_t>& minmax_index, const vector<double>& x_min)
{
	size_t size = simplex_index.size();
	size_t min_index = minmax_index.first;
	/// Поскольку во время редукции меняется весь симплекс,
	/// следует добавлять все точки в траекторию
	for (size_t i = 0; i < size; ++i) {
		size_t curr_index = simplex_index[i];
		if (min_index != curr_index) {
			/// Заменяем все x_i на x_l + 0.5*(x_i-x_l)
			vector<double> x_i(x_min);
			const vector<double>& x_curr(trajectory[curr_index]);
			for (size_t k = 0; k < x_i.size(); ++k) {
				x_i[k] += 0.5 * (x_curr[k] - x_min[k]);
			}
			/// Когда заполнили, вставляем в траекторию и меняем индекс
			trajectory.push_back(x_i);
			simplex_index[i] = trajectory.size() - 1;
		}
	}
}

vector<double> NelderMeadMethod::Compression(const vector<double>& x_n_2, const vector<double>& x_max)
{
	vector<double> x_n_5(x_n_2);
	for (size_t i = 0; i < x_n_2.size(); ++i) {
		x_n_5[i] += beta * (x_max[i] - x_n_2[i]);
	}
	return x_n_5;
}

vector<double> NelderMeadMethod::Stretching(const vector<double>& x_n_2, const vector<double>& x_n_3, const BaseArea& ba)
{
	size_t size = startPoint.size();
	vector<double> x_n_4(x_n_2);
	for (size_t i = 0; i < size; ++i) {
		x_n_4[i] += gamma * (x_n_3[i] - x_n_2[i]);
	}
	CorrectPointPlacement(x_n_2, x_n_4, ba);
	return x_n_4;
}

void NelderMeadMethod::CheckInput()
{
	bool check = true;
	if (alpha <= 0) {
		cout << endl << "Error: Alpha must be > 0." << endl;
		check = false;
	}
	if (gamma <= 1) {
		cout << endl << "Error: Gamma must be > 1." << endl;
		check = false;
	}
	if (!(0 < beta && beta < 1)) {
		cout << endl << "Error: Beta must be between 0 and 1." << endl;
		check = false;
	}
	if (!check) {
		exit(1);
	}
}

pair<size_t, size_t> NelderMeadMethod::FindMinMaxIndex(const BaseFunction& bf) const
{
	/// Вычисляем индекс для k-ой итерации
	size_t size = simplex_index.size();

	/// Вводим минимум, максимум и ищем их индексы
	double min = bf(trajectory[simplex_index[0]]);
	double max = min;
	size_t min_index = 0, max_index = 0;
	for (size_t i = 1; i < size; ++i) {
		double f = bf(trajectory[simplex_index[i]]);
		if (min > f) {
			min = f;
			min_index = i;
		}
		if (max < f) {
			max = f;
			max_index = i;
		}
	}
	return pair<size_t, size_t>(min_index, max_index);
}