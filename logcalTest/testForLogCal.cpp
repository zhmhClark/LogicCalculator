#include<iostream>
#include<string>
using namespace std;

int main()
{
	char c = true;
	bool flag = true;
	string s = "hello,world!";
	cout << (char)(c+'0');
	cout << endl << flag<<endl;
	cout << (int)'!';
	cout << s.substr(1);
	cout << endl << s.substr(s.size())<<endl;
	return 0;
}