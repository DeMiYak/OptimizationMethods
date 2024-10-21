#pragma once
#include"BaseArea.h"

/// <summary>
/// Класс параллелипипеда для построения 
/// области поиска экстремума.
/// Хранит pair<vector<double>, vector<double>> для точек.
/// По смыслу лучше, чем vector<pair<double,double>>, так как
/// рассматриваются две точки, а не набор точек размерности два
/// </summary>
class Rectangle : public BaseArea {
public:
	/// <summary>
	/// Конструктор для параллелипипеда. Инициализирует 
	/// bound парами точек fpt, spt покоординатно и соответственно.
	/// Проверяет на соответствие размеров (возможно рудимент) и
	/// на покоординатное совпадение координат (вырождение параллелипипеда) 
	/// </summary>
	/// <param name="fpt">Первая точка</param>
	/// <param name="spt">Вторая точка</param>
	Rectangle(vector<double> fpt, vector<double> spt) : BaseArea() {
		/// Проверка на корректность данных
		CheckValidity(fpt, spt);
		
		/// Делаем границы для нашего параллелипипеда
		for (size_t i = 0; i < fpt.size(); ++i) {
			bound.push_back(make_pair(fpt[i], spt[i]));
		}
	};
	
	/// <summary>
	/// Конструктор копирования 
	/// </summary>
	/// <param name="rectangle">Копируемый объект</param>
	Rectangle(const Rectangle& rectangle) : BaseArea(), bound(rectangle.bound) {};

	/// <summary>
	/// Конструктор перемещения
	/// </summary>
	/// <param name="rectangle">Перемещаемый объект</param>
	Rectangle(Rectangle&& rectangle) noexcept : BaseArea(), bound(move(rectangle.bound)) {};

	Rectangle& operator=(const Rectangle& rectangle){
		if (this != &rectangle) {
			this->bound = rectangle.bound;
		}
		return *this;
	}
	virtual vector<pair<double, double>> GetBounds() const { return bound; };

	virtual bool IsInside(const vector<double>& point) const;
private:
	/// <summary>
	/// Граница, представленная парами
	/// </summary>
	vector<pair<double, double>> bound;

	/// <summary>
	/// Приватный метод для проверки точек-аргументов на корректность:
	/// нет ли вырождения параллелипипеда и соответствие размерностей точек.
	/// Для размерности точек можно предложить вариант "уравнивания размерностей" от
	/// меньшего к большему  
	/// </summary>
	/// <param name="fpt">Первая точка</param>
	/// <param name="spt">Вторая точка</param>
	void CheckValidity(const vector<double>& fpt, const vector<double>& spt);
};

///// <summary>
///// @brief Базовый генератор выборки
///// </summary>
//class BaseSampleGenerator
//{
//public:
//	/// <summary>
//	/// Конструтор класса
//	/// </summary>
//	/// <param name="_samVol">Объём выборки</param>
//	BaseSampleGenerator(int _samVol) :
//		samVol(_samVol),
//		sample(new int[_samVol]) {
//	};
//	/// <summary>
//	/// Конструктор копирования
//	/// </summary>
//	/// <param name="bsg">Генератор выборки</param>
//	BaseSampleGenerator(const BaseSampleGenerator& bsg) :
//		samVol(bsg.samVol)
//	{
//		sample = new int[samVol];
//		for (int i = 0; i < samVol; i++) {
//			sample[i] = bsg.sample[i];
//		}
//	};
//	/// <summary>
//	/// Конструктор перемещения
//	/// </summary>
//	/// <param name="bsg">Генератор выборки</param>
//	BaseSampleGenerator(BaseSampleGenerator&& bsg) noexcept :
//		samVol(std::exchange(bsg.samVol, 0)),
//		sample(std::move(bsg.sample))
//	{
//		bsg.sample = nullptr;
//	}
//	/// <summary>
//	/// Оператор присваивания с копированием
//	/// </summary>
//	/// <param name="bsg">Генератор выборки</param>
//	/// <returns>Генератор выборки</returns>
//	BaseSampleGenerator& operator=(const BaseSampleGenerator& bsg) {
//		if (this != &bsg) {
//			samVol = bsg.samVol;
//			delete[] sample;
//			sample = new int[samVol];
//			for (int i = 0; i < samVol; i++) {
//				sample[i] = bsg.sample[i];
//			}
//		}
//		return *this;
//	}
//	/// <summary>
//	/// Оператор присваивания с перемещением
//	/// </summary>
//	/// <param name="bsg">Генератор выборки</param>
//	/// <returns>Генератор выборки</returns>
//	BaseSampleGenerator& operator=(BaseSampleGenerator&& bsg) noexcept {
//		if (this != &bsg) {
//			sample = std::move(bsg.sample);
//			samVol = std::exchange(bsg.samVol, 0);
//			bsg.sample = nullptr;
//		}
//		return *this;
//	}
//	/// <summary>
//	/// Вывод данных о выборке
//	/// </summary>
//	friend std::ostream& operator<<(std::ostream& os, const BaseSampleGenerator& bsg) {
//		os << std::endl << "Объём выборки = " << bsg.samVol;
//		os << "\nВыборка: [" << bsg.sample[0];
//		for (int i = 1; i < bsg.samVol; i++) {
//			os << ", " << bsg.sample[i];
//		}
//		os << "]" << std::endl;
//		return os;
//	}
//	/// <summary>
//	/// Виртуальный метод генерации выборки
//	/// </summary>
//	/// <param name="dis">Распределение</param>
//	/// <param name="_samVol">Объём выборки</param>
//	virtual void Simulate(const Distribution& dis, int _samVol) = 0;
//	/// <summary>
//	/// Виртуальный деструктор класса
//	/// </summary>
//	virtual ~BaseSampleGenerator() { delete[] sample; samVol = 0; };
//	/// <summary>
//	/// Получение выборки
//	/// </summary>
//	/// <returns>Указатель на выборку</returns>
//	int* GetSample() const { return sample; };
//	/// <summary>
//	/// Получение объёма выборки
//	/// </summary>
//	/// <returns>Объём выборки</returns>
//	int GetSamVol() const { return samVol; };
//protected:
//	/// <summary>
//	/// Массив выборочных значений
//	/// </summary>
//	int* sample;
//	/// <summary>
//	/// Объём выборки
//	/// </summary>
//	int samVol;
//};