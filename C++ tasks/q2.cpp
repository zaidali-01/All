#include<iostream>
#include<string>
using namespace std;
void cpystring(string a,string& b,int index)
{
	if (index == 0)
		b = "";
	if (index == a.size())
		return;
	b += a[index];
	cpystring(a, b, index + 1);
}
int main()
{
	string s1 = "zaid";
	string s2 = "ali";
	cpystring(s1, s2, 0);
	cout << s2;
	return 0;
}