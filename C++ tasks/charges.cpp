#include <iostream>
using namespace std;
int main()
{
	char a;
	char data[10];
	cin >> a;
	cin.ignore();
	cout << "Enter chracter array: ";
	cin.getline(data, 20);
	for (int i = 0; data[i] != '\0'; i++)
	{
		if (data[i] == a)
		{
			for (int j = i; data[j] != '\0'; j++)
			{
				data[j] = data[j + 1];
				if (data[j] == '\0')
					break;
			}
			i--;
		}
	}
	cout << data;


	return 0;
}