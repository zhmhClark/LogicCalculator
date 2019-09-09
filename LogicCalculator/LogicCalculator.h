#pragma once
#include<iostream>
#include <string>
#include <vector>
using namespace std;

class LogicCalculator
{
private:
	string expression, valGotExp;
	int num;
	vector<char> names;
	bool calculate(int);
	bool calculateExp();
	bool calculateTerm();
	bool calculatefactor();

public:
	LogicCalculator(const string&);
	void printChart();
	void printOrExpression();
	void printAndExpression();
};


