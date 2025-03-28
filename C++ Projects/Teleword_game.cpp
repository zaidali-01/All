#include<iostream>
#include<fstream>
#include<windows.h>
#include<chrono>
#include<conio.h>
using namespace std::chrono;
using namespace std;
int main()
{
	char grid[15][15];
	char words[1000];
	ifstream fin;
	fin.open("wording.txt");
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			fin >> grid[i][j];
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; 1; i++)
	{
		fin >> words[i];
		cout << words[i];
		if (words[i] == '.')
		{
			cout << endl;
			break;
		}
	}
	cout << endl;
	fin.close();
	char select;
	cout << "Press S to solve puzzle at once" << endl;
	cout << "Press T to solve puzzle step by step" << endl;
	cout << "Press X to print puzzle statistics" << endl;
	cin >> select;
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int wordpos[100];
	wordpos[0] = 0;
	int y = 1;
	for (int a = 1; 1; a++)
	{
		if (words[a] == ',')
		{
			wordpos[y] = a + 1;
			y++;
			a = a + 2;
		}
		if (words[a] == '.')
		{
			wordpos[y] = a + 1;
			break;
		}
		words[a] = words[a] - 32;
	}
	int k = 0, l = 1;
	int nums[15][15];
	for (int m = 0; m < 15; m++)
	{
		for (int n = 0; n < 15; n++)
		{
			nums[m][n] = 0;
		}
	}
	int rows[15]{}, columns[15]{};
	int LR = 0, RL = 0, UD = 0, DU = 0, LD = 0, LU = 0, RD = 0, RU = 0;
	bool check = false;
	auto start = high_resolution_clock::now();
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (grid[i][j] == words[k])
			{
				if (j != 14)
				{
					if (grid[i][j + 1] == words[k + 1])
					{
						int a = i, b = j + 2, c = k + 2;
						while (words[c] != ',' && words[c] != '.')
						{
							if (b <= 14)
							{
								if (grid[a][b] == words[c])
								{
									b++;
									c++;
									if (c == wordpos[l] - 1)
									{
										k = wordpos[l];
										l++;
										while (j < b)
										{
											columns[j]++;
											nums[i][j]++;
											j++;
										}
										rows[i]++;
										LR++;
										check = true;
										i = 0, j = -1;
										break;
									}
									if (b > 14)
										break;
								}
								else
									break;
							}
							else
								break;
						}
					}
				}
				if (j != 0)
				{
					if (grid[i][j - 1] == words[k + 1])
					{
						int a = i, b = j - 2, c = k + 2;
						while (words[c] != ',' && words[c] != '.')
						{
							if (b >= 0)
							{
								if (grid[a][b] == words[c])
								{
									b--;
									c++;
									if (c == wordpos[l] - 1)
									{
										k = wordpos[l];
										l++;
										while (j > b)
										{
											columns[j]++;
											nums[i][j]++;
											j--;
										}
										rows[i]++;
										RL++;
										check = true;
										i = 0, j = -1;
										break;
									}
									if (b < 0)
										break;
								}
								else
									break;
							}
							else
								break;
						}
					}
				}
				if (i != 14)
				{
					if (grid[i + 1][j] == words[k + 1])
					{
						int a = i + 2, b = j, c = k + 2;
						while (words[c] != ',' && words[c] != '.')
						{
							if (a <= 14)
							{
								if (grid[a][b] == words[c])
								{
									a++;
									c++;
									if (c == wordpos[l] - 1)
									{
										k = wordpos[l];
										l++;
										while (i < a)
										{
											rows[i]++;
											nums[i][j]++;
											i++;
										}
										columns[j]++;
										UD++;
										check = true;
										i = 0, j = -1;
										break;
									}
									if (a > 14)
										break;
								}
								else
									break;
							}
							else
								break;
						}
					}
				}
				if (i != 0)
				{
					if (grid[i - 1][j] == words[k + 1])
					{
						int a = i - 2, b = j, c = k + 2;
						while (words[c] != ',' && words[c] != '.')
						{
							if (a >= 0)
							{
								if (grid[a][b] == words[c])
								{
									a--;
									c++;
									if (c == wordpos[l] - 1)
									{
										k = wordpos[l];
										l++;
										while (i > a)
										{
											rows[i]++;
											nums[i][j]++;
											i--;
										}
										columns[j]++;
										DU++;
										check = true;
										i = 0, j = -1;
										break;
									}
									if (a < 0)
										break;
								}
								else
									break;
							}
							else
								break;
						}
					}
				}
				if (i != 14 && j != 14)
				{
					if (grid[i + 1][j + 1] == words[k + 1])
					{
						int a = i + 2, b = j + 2, c = k + 2;
						while (words[c] != ',' && words[c] != '.')
						{
							if (a <= 14 && b <= 14)
							{
								if (grid[a][b] == words[c])
								{
									a++;
									b++;
									c++;
									if (c == wordpos[l] - 1)
									{
										k = wordpos[l];
										l++;
										while (i < a && j < b)
										{
											rows[i]++;
											columns[j]++;
											nums[i][j]++;
											i++;
											j++;
										}
										LD++;
										check = true;
										i = 0, j = -1;
										break;
									}
									if (a > 14 && b > 14)
										break;
								}
								else
									break;
							}
							else
								break;
						}
					}
				}
				if (i != 0 && j != 14)
				{
					if (grid[i - 1][j + 1] == words[k + 1])
					{
						int a = i - 2, b = j + 2, c = k + 2;
						while (words[c] != ',' && words[c] != '.')
						{
							if (a >= 0 && b <= 14)
							{
								if (grid[a][b] == words[c])
								{
									a--;
									b++;
									c++;
									if (c == wordpos[l] - 1)
									{
										k = wordpos[l];
										l++;
										while (i > a && j < b)
										{
											rows[i]++;
											columns[j]++;
											nums[i][j]++;
											i--;
											j++;
										}
										LU++;
										check = true;
										i = 0, j = -1;
										break;
									}
									if (a < 0 && b > 14)
										break;
								}
								else
									break;
							}
							else
								break;
						}
					}
				}
				if (i != 0 && j != 0)
				{
					if (grid[i - 1][j - 1] == words[k + 1])
					{
						int a = i - 2, b = j - 2, c = k + 2;
						while (words[c] != ',' && words[c] != '.')
						{
							if (a >= 0 && b >= 0)
							{
								if (grid[a][b] == words[c])
								{
									a--;
									b--;
									c++;
									if (c == wordpos[l] - 1)
									{
										k = wordpos[l];
										l++;
										while (i > a && j > b)
										{
											rows[i]++;
											columns[j]++;
											nums[i][j]++;
											i--;
											j--;
										}
										RU++;
										check = true;
										i = 0, j = -1;
										break;
									}
									if (a < 0 && b < 0)
										break;
								}
								else
									break;
							}
							else
								break;
						}
					}
				}
				if (i != 14 && j != 0)
				{
					if (grid[i + 1][j - 1] == words[k + 1])
					{
						int a = i + 2, b = j - 2, c = k + 2;
						while (words[c] != ',' && words[c] != '.')
						{
							if (a <= 14 && b >= 0)
							{
								if (grid[a][b] == words[c])
								{
									a++;
									b--;
									c++;
									if (c == wordpos[l] - 1)
									{
										k = wordpos[l];
										l++;
										while (i < a && j > b)
										{
											rows[i]++;
											columns[j]++;
											nums[i][j]++;
											i++;
											j--;
										}
										RD++;
										check = true;
										i = 0, j = -1;
										break;
									}
									if (a > 14 && b < 0)
										break;
								}
								else
									break;
							}
							else
								break;
						}
					}
				}
			}
			if (select == 'T' && check)
			{
				check = false;
				for (int m = 0; m < 15; m++)
				{
					for (int n = 0; n < 15; n++)
					{
						if (nums[m][n] == 0)
							SetConsoleTextAttribute(h, 7);
						if (nums[m][n] == 1)
							SetConsoleTextAttribute(h, 6);
						if (nums[m][n] == 2)
							SetConsoleTextAttribute(h, 1);
						if (nums[m][n] > 2)
							SetConsoleTextAttribute(h, 4);
						cout << grid[m][n] << " ";
					}
					cout << endl;
				}
				int d = _getch();
				system("cls");
			}
		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	for (int m = 0; m < 15; m++)
	{
		for (int n = 0; n < 15; n++)
		{
			if (nums[m][n] == 0)
				SetConsoleTextAttribute(h, 7);
			if (nums[m][n] == 1)
				SetConsoleTextAttribute(h, 6);
			if (nums[m][n] == 2)
				SetConsoleTextAttribute(h, 1);
			if (nums[m][n] > 2)
				SetConsoleTextAttribute(h, 4);
			cout << grid[m][n] << " ";
		}
		cout << endl;
	}
	cout << endl;
	SetConsoleTextAttribute(h, 7);
	int scatter, count = 0;
	cout << "The teleword is: ";
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (nums[i][j] == 0)
			{
				cout << grid[i][j];
				if (count == 0)
				{
					scatter = i;
					count++;
				}
				if (scatter != i)
				{
					count++;
				}
				scatter = i;
			}
		}
	}
	cout << endl;
	if (select == 'X')
	{
		int longword = 0, shortword = 15, sum = 0, temp;
		for (int p = 0; p < y; p++)
		{
			temp = wordpos[p + 1] - 1 - wordpos[p];
			if (temp > longword)
				longword = temp;
			if (temp < shortword)
				shortword = temp;
			sum += temp;
		}
		int row = 0, r = 0, column = 0, s = 0;
		for (int t = 0; t < 15; t++)
		{
			if (rows[t] > row)
			{
				row = rows[t];
				r = t;
			}
			if (columns[t] > column)
			{
				column = columns[t];
				s = t;
			}
		}
		std::cout << endl << "Time taken by function: " << duration.count() << " microseconds" << endl;
		cout << "The longest word length is: " << longword << endl;
		cout << "The shortest word length is: " << shortword << endl;
		cout << "The average word length is: " << sum / y << endl;
		cout << "Word Distribution: ";
		cout << "Horizontal: " << LR + RL << "(" << LR << ", " << RL << "), ";
		cout << "Vertical: " << UD + DU << "(" << UD << ", " << DU << "), ";
		cout << "Diagonal: " << LD + LU + RD + RU << "(" << LD + LU << ", " << RD + RU << "), " << endl;
		cout << "Teleword Scatter: " << count << endl;
		cout << "Heaviest row is: " << r << endl;
		cout << "Heaviest column is: " << s << endl;
	}
	return 0;
}