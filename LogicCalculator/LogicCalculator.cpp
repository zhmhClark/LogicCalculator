#include"LogicCalculator.h"

bool LogicCalculator::calculate(int val)
{
	valGotExp = expression;
	int n = val;
	//将传入参数处理为真值组（十进制整数转化成二进制）
	bool* values = new bool[num];
	for (int i = num - 1; i >= 0; i--)
	{
		values[i] = n % 2;
		n /= 2;
	}
	int size = expression.size();
	//用真值替换变元
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
	//真值指派后，调用具体计算函数
	return calculateExp();
}

bool LogicCalculator::calculateExp()
{
	bool res = calculateTerm();	//递归调用，算表达式里的项
	bool stop = false;
	while (!stop)
	{
		if (!valGotExp.size())	break;
		char op = valGotExp[0];
		bool nextTerm = false;
		switch (op)				//相邻项的逻辑运算
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
		case '-':								// ->运算
			valGotExp = valGotExp.substr(2);
			nextTerm = calculateTerm();
			res = (!res) || nextTerm;
			break;
		case '<':								// <->运算
			valGotExp = valGotExp.substr(3);
			nextTerm = calculateTerm();
			res = (res==nextTerm);
			break;
		case '^':								// 异或运算
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
	while (valGotExp[0] == '!')				//处理非运算
	{
		valGotExp = valGotExp.substr(1);
		notNum++;
	}
	bool res = calculatefactor();			//递归调用，处理项里的因子
	if(notNum%2)
	return !res;
	return res;
}

bool LogicCalculator::calculatefactor()
{
	bool res;
	if (valGotExp[0] == '(')				//因子由 '(' + 表达式 + ')' 构成
	{
		valGotExp = valGotExp.substr(1);
		res = calculateExp();				//递归调用，处理因子里的表达式
		valGotExp = valGotExp.substr(1);
	}
	else									//因子是单独的变元
	{
		res = valGotExp[0] - '0';
		valGotExp = valGotExp.substr(1);
	}
	return res;
}

LogicCalculator::LogicCalculator(const string& exp):expression(exp),valGotExp(exp)
{
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
    cout<<"∑";
    PrintExpression(0);
}

void LogicCalculator::printAndExpression()
{
    cout<<"∏";
    PrintExpression(1);
}

void LogicCalculator::PrintExpression(bool flag) {
    int situations = 1;
    situations = pow(2,num);
    int flag1 = 0;
    cout<<"[";
    for (int i = 0; i < situations; i++)
        if(calculate(i)^flag) {
            if(flag1)
                cout<<',';
            cout << i;
            flag1 = 1;
        }
    cout<<"]\n";
}
