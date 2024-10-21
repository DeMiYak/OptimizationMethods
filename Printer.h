#pragma once
#include<iostream>
#include"BaseOptMethod.h"
class Printer
{
public:
	void PrintData(const BaseOptMethod& bom);
private:
	void PrintVector(const vector<double>& vec);
};

