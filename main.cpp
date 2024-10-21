#include<iostream>

#include"BaseOptMethod.h"
#include"NelderMeadMethod.h"
#include"StochasticMethod.h"

#include"BaseArea.h"
#include"Rectangle.h"

#include"BaseStopCriterion.h"
#include"AbsoluteErrorStopCriterion.h"
#include"NelderMeadStopCriterion.h"

#include"BaseFunction.h"
#include"FunctionOne.h"
#include"FunctionTwo.h"
#include"FunctionThree.h"

#include"Printer.h"

/// Чтобы не плутать вокруг да около, проведём несколько рассуждений на тему того,
/// что должна делать программа на данном этапе, какие задачи ставятся и как к ним прийти.
/// 
/// Начнём с постановки задачи: рассматривается метод поиска экстремума многомерной функции.
/// Это означает, что для нашей задачи нужно реализовать:
/// - класс-метод для поиска экстремума,
/// - многомерную функцию
/// 
/// Теперь, требуется реализовать (как минимум) скалярные функции размерности 1, 2, 3.
/// Для этого можно построить следующую иерархию
/// 
/// Базовый класс BaseFunction:
/// 
/// 1. FunctionOneDim - функция размерности 1
/// 2. FunctionTwoDim - функция размерности 2
/// 3. FunctionThreeDim - функция размерности 3


/// Теперь учитываем, что задача поиска экстремума рассматривается в некоторой ограниченной области.
/// Следовательно, нужно завести класс области, в котором будет решаться задача. Например,
/// введём абстрактный базовый класс BaseArea.
/// 
/// От BaseArea:
/// 
/// 1. Rectangle - класс, задающий параллелипипед
/// 
/// Возникают вопросы по поводу того, требуется ли для задачи рассматривать разные области или нет.
/// Допустим, рассматриваем функцию с sin и cos. Тогда кажется удобным использовать шар,
/// а не параллелипипед.
/// То есть, нужно решить, использовать ли единственный класс Rectangle для всех задач, или же
/// необходимо придумывать способы задания/зарисовки в разных областях, где есть подозрение на экстремум.
/// 
/// 
/// Также требуется ввести базовый класс BaseOptMethod для реализации методов оптимизации.
/// В рамках поставленной задачи необходимо реализовать только один метод -
/// метод деформируемых многогранников (NelderMeadMethod).


/// BaseOptMethod:
/// 
/// 1. NelderMeadMethod - метод деформируемых многогранников.
/// 
/// 
/// Помимо этого требуется базовый класс BaseStopCriterion - критерий остановки. Он нужен, чтобы
/// остановить выполнение метода (например, по числу итераций или расстоянию между последними точками
/// траектории).


/// BaseStopCriterion:
/// 
/// 
/// 1. AbsoluteErrorStopCriterion - критерий остановки по epsilon (норма отдаления двух последних
/// точек траектории).
/// 
/// 2. RelErrorStopCriterion - критерий остановки по относительной ошибке разности функций
/// в точках траектории.
/// 
/// Важное замечание: критерии остановки предполагают вычисление нормы. Поэтому,
/// следует реализовать функцию, либо класс, который будет отвечать за нормировку. 
/// 
/// Теперь вопрос: как это реализовывать? Что нужно и в какой последовательности.
///  
/// 

/// Замечания:
/// 1. Переделать обработку ошибок в стиле C++ (try-catch block)
/// 
/// 

/// <summary>
/// Функция main
/// </summary>
/// <returns>0</returns>
int main() {

	/// Nelder-Mead Method

	//vector<double> startPoint{ -1.2, 1.0 };
	vector<double> startPoint{ -1.2, 1.0 };
	double alpha = 1;
	double gamma = 2;
	double beta = 0.5;
	double t = 0.5;
	size_t iter_num = 1000;
	double eps = 1e-9;

	shared_ptr<BaseFunction> fo(new FunctionOne());
	shared_ptr<BaseFunction> ft(new FunctionTwo());
	shared_ptr<BaseFunction> fthree(new FunctionThree());
	shared_ptr<BaseStopCriterion> nmsc(new NelderMeadStopCriterion(iter_num, eps));
	/// Ошибка: две одинаковые точки. Нужно обрабатывать исключения
	// shared_ptr<BaseArea> rect(new Rectangle({-10, 10}, {-10, 10}));

	/// Компактный параллелипипед, в котором алгоритм выходит за границы
	shared_ptr<BaseArea> rectCompact(new Rectangle({ -1.3, -1 }, { 1.1, 1.1 }));

	/// Достаточный параллелипипед, в котором алгоритм не выходит за границы
	shared_ptr<BaseArea> rectSufficient(new Rectangle({ -10, -10 }, { 10, 10 }));
	shared_ptr<BaseOptMethod> nmm(new NelderMeadMethod(startPoint, alpha, gamma, beta, t));

	/// Класс принтера
	Printer printer;
	nmm->Optimize(*rectCompact, *ft, *nmsc);
	printer.PrintData(*nmm);

	cout << endl;
	nmm->Optimize(*rectSufficient, *ft, *nmsc);
	printer.PrintData(*nmm);

	cout << endl;
	shared_ptr<BaseArea> rectOneDim(new Rectangle({ -3 }, { 3 }));
	nmm->SetStartPoint({ -2.0 });
	nmm->Optimize(*rectOneDim, *fo, *nmsc);
	printer.PrintData(*nmm);

	cout << endl;

	shared_ptr<BaseArea> rectThreeDim(new Rectangle({ -5, -5, -5 }, { 5, 5, 5 }));
	nmm->SetStartPoint({ 0, 0, 0 });
	nmm->Optimize(*rectThreeDim, *fthree, *nmsc);
	printer.PrintData(*nmm);


	/// Stochastic Method.
	cout << endl;
	random_device rd;
	double p = 0.5;
	double delta = 1.0;
	vector<double> stocStartPoint{ 0,0,0 };
	shared_ptr<BaseStopCriterion> aesc(new AbsoluteErrorStopCriterion(iter_num, eps));
	shared_ptr<BaseOptMethod> stochasticMethod(new StochasticMethod(stocStartPoint, rd, p, delta));
	stochasticMethod->Optimize(*rectThreeDim, *fthree, *aesc);
	printer.PrintData(*stochasticMethod);
}