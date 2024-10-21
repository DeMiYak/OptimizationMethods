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

/// ����� �� ������� ������ �� �����, ������� ��������� ����������� �� ���� ����,
/// ��� ������ ������ ��������� �� ������ �����, ����� ������ �������� � ��� � ��� ������.
/// 
/// ����� � ���������� ������: ��������������� ����� ������ ���������� ����������� �������.
/// ��� ��������, ��� ��� ����� ������ ����� �����������:
/// - �����-����� ��� ������ ����������,
/// - ����������� �������
/// 
/// ������, ��������� ����������� (��� �������) ��������� ������� ����������� 1, 2, 3.
/// ��� ����� ����� ��������� ��������� ��������
/// 
/// ������� ����� BaseFunction:
/// 
/// 1. FunctionOneDim - ������� ����������� 1
/// 2. FunctionTwoDim - ������� ����������� 2
/// 3. FunctionThreeDim - ������� ����������� 3


/// ������ ���������, ��� ������ ������ ���������� ��������������� � ��������� ������������ �������.
/// �������������, ����� ������� ����� �������, � ������� ����� �������� ������. ��������,
/// ����� ����������� ������� ����� BaseArea.
/// 
/// �� BaseArea:
/// 
/// 1. Rectangle - �����, �������� ��������������
/// 
/// ��������� ������� �� ������ ����, ��������� �� ��� ������ ������������� ������ ������� ��� ���.
/// ��������, ������������� ������� � sin � cos. ����� ������� ������� ������������ ���,
/// � �� ��������������.
/// �� ����, ����� ������, ������������ �� ������������ ����� Rectangle ��� ���� �����, ��� ��
/// ���������� ����������� ������� �������/��������� � ������ ��������, ��� ���� ���������� �� ���������.
/// 
/// 
/// ����� ��������� ������ ������� ����� BaseOptMethod ��� ���������� ������� �����������.
/// � ������ ������������ ������ ���������� ����������� ������ ���� ����� -
/// ����� ������������� �������������� (NelderMeadMethod).


/// BaseOptMethod:
/// 
/// 1. NelderMeadMethod - ����� ������������� ��������������.
/// 
/// 
/// ������ ����� ��������� ������� ����� BaseStopCriterion - �������� ���������. �� �����, �����
/// ���������� ���������� ������ (��������, �� ����� �������� ��� ���������� ����� ���������� �������
/// ����������).


/// BaseStopCriterion:
/// 
/// 
/// 1. AbsoluteErrorStopCriterion - �������� ��������� �� epsilon (����� ��������� ���� ���������
/// ����� ����������).
/// 
/// 2. RelErrorStopCriterion - �������� ��������� �� ������������� ������ �������� �������
/// � ������ ����������.
/// 
/// ������ ���������: �������� ��������� ������������ ���������� �����. �������,
/// ������� ����������� �������, ���� �����, ������� ����� �������� �� ����������. 
/// 
/// ������ ������: ��� ��� �������������? ��� ����� � � ����� ������������������.
///  
/// 

/// ���������:
/// 1. ���������� ��������� ������ � ����� C++ (try-catch block)
/// 
/// 

/// <summary>
/// ������� main
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
	/// ������: ��� ���������� �����. ����� ������������ ����������
	// shared_ptr<BaseArea> rect(new Rectangle({-10, 10}, {-10, 10}));

	/// ���������� ��������������, � ������� �������� ������� �� �������
	shared_ptr<BaseArea> rectCompact(new Rectangle({ -1.3, -1 }, { 1.1, 1.1 }));

	/// ����������� ��������������, � ������� �������� �� ������� �� �������
	shared_ptr<BaseArea> rectSufficient(new Rectangle({ -10, -10 }, { 10, 10 }));
	shared_ptr<BaseOptMethod> nmm(new NelderMeadMethod(startPoint, alpha, gamma, beta, t));

	/// ����� ��������
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