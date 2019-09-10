#pragma once
#include<iostream>
#include <string>
#include <vector>
using namespace std;

class LogicCalculator
{
private:
	const string expression;	//命题公式
	string valGotExp;			//value-got expression,即指派真值的命题公式
	int num;					//变元数量
	vector<char> names;			//变元名称
	bool calculate(int);		//指派真值后的计算函数，将传入的参数处理为真值，再调用以下具体计算函数
	
	//以下三个具体计算函数相互调用，构成递归，仅在bool calculate(int) 中调用，计算指派真值后的表达式的值
	bool calculateExp();		//计算表达式
	bool calculateTerm();		//计算项
	bool calculatefactor();		//计算因子

public:
	LogicCalculator(const string&);
	void printChart();			//计算并输出真值表 （待完成：将计算和输出分离）
	void printOrExpression();	//待完成：主析取范式
	void printAndExpression();	//待完成：主合取范式
};


