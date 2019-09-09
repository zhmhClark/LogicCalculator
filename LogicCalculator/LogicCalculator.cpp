#include"LogicCalculator.h"

bool LogicCalculator::calculate(int val)
{
	valGotExp = expression;
	int n = val;
	bool* values = new bool[num];
	for (int i = num - 1; i >= 0; i--)
	{
		values[i] = n % 2;
		n /= 2;
	}
	int size = expression.size();
	for (int i = 0; i < size; i++)
	{
		char& c = valGotExp[i];
		if (c <= 'Z' && c >= 'A')
		{
			for (int j = 0; j < num; j++)
			{
				if (c == names[j])	c =(char)(values[j] + '0');
			}
		}
	}
	delete[] values;
	return calculateExp();
}

bool LogicCalculator::calculateExp()
{
	bool res = calculateTerm();
	bool stop = false;
	while (!stop)
	{
		if (!valGotExp.size())	break;
		char op = valGotExp[0];
		bool nextTerm = false;
		switch (op)
		{
		case '&':
			valGotExp = valGotExp.substr(1);
			nextTerm = calculateTerm();
			res = res && nextTerm;
			break;
		case '|':
			valGotExp = valGotExp.substr(1);
			nextTerm = calculateTerm();
			res = res || nextTerm;
			break;
		case '-':
			valGotExp = valGotExp.substr(2);
			nextTerm = calculateTerm();
			res = (!res) || nextTerm;
			break;
		case '<':
			valGotExp = valGotExp.substr(3);
			nextTerm = calculateTerm();
			res = (res==nextTerm);
			break;
		case '^':
			valGotExp = valGotExp.substr(1);
			nextTerm = calculateTerm();
			res = (res != nextTerm);
			break;
		default:
			stop = true;
		}
	}
	return res;
}

bool LogicCalculator::calculateTerm()
{
	int notNum = 0;
	while (valGotExp[0] == '!')
	{
		valGotExp = valGotExp.substr(1);
		notNum++;
	}
	bool res = calculatefactor();
	if(notNum%2)
	return !res;
	return res;
}

bool LogicCalculator::calculatefactor()
{
	bool res;
	if (valGotExp[0] == '(')
	{
		valGotExp = valGotExp.substr(1);
		res = calculateExp();
		valGotExp = valGotExp.substr(1);
	}
	else
	{
		res = valGotExp[0] - '0';
		valGotExp = valGotExp.substr(1);
	}
	return res;
}

LogicCalculator::LogicCalculator(const string& exp)
{
	expression = valGotExp = exp;
	int size = expression.size();
	for (int i = 0; i < size; i++)
	{
		char c = expression[i];
		if (c <= 'Z' && c >= 'A')
		{
			bool same = false;
			for (char& name : names)
				if (name == c)	same = true;
			if (!same) names.push_back(c);
		}
	}
	num = names.size();
}

void LogicCalculator::printChart()
{
	for (int i = 0; i < num; i++)
		cout << names[i] << '\t';
	cout << "result" << endl;
	int situations = 1, n = num;
	while (n--)	situations *= 2;
	for (int i = 0; i < situations; i++)
	{
		bool* assign = new bool[num];
		for (int j = 0; j < num; j++)	assign[j] = 0;
		int situation = i;
		int j = 0;
		while(situation)
		{
			assign[j++] = situation % 2;
			situation /= 2;
		}
		for (int j = 0; j < num; j++)
			cout << assign[num-j-1] << '\t';
		cout << calculate(i) << endl;
		delete[] assign;
	}	
}

void LogicCalculator::printOrExpression()
{
}

void LogicCalculator::printAndExpression()
{
}
