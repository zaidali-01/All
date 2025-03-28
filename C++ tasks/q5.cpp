#include<iostream>
using namespace std;
void num(int);
void print(int b)
{
	if (b == 0)
		return;
	num(b);
	cout << b << " ";
}
void num(int a)
{
	print(a-1);

}
int main()
{
	int n;
	cout << "Enter number: ";
	cin >> n;
	print(n);
	return 0;
}