#include<iostream>
#include<string>
using namespace std;
void print(string s,int index)
{
	if (index == s.size())
		return;
	print(s, index + 1);
	cout << s[index];
}
int main()
{
	string s = "My name is Zaid!";
	print(s,0);
	return 0;
}