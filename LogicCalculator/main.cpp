#include"LogicCalculator.h"
#include<iostream>
using namespace std;

int main()
{
	while (true)
	{
		string expression;
		cout << "please input the exepression(0 to quit):" << endl;
		cin >> expression;
		if (expression.at(0) == '0') break;
		LogicCalculator logcal(expression);
		logcal.printChart();
		logcal.printOrExpression();
		logcal.printAndExpression();
	}
	return 0;
}