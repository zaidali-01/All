#include<iostream>
using namespace std;
class matrix
{
	int row;
	int column;
	int** values;
public:
	matrix()
	{
		row = 0;
		column = 0;
		values = nullptr;
	}
	matrix(int r, int c)
	{
		row = r;
		column = c;
		values = new int* [row];
		for (int i = 0; i < row; i++)
		{
			values[i] = new int[column];
		}
	}
	matrix(const matrix& obj)
	{
		row = obj.row;
		column = obj.column;
		values = new int* [obj.row];
		for (int i = 0; i < obj.row; i++)
		{
			values[i] = new int[obj.column];
		}
		for (int i = 0; i < obj.row; i++)
		{
			for (int j = 0; j < obj.column; j++)
			{
				values[i][j] = obj.values[i][j];
			}
		}
	}
	int getrow() const
	{
		return row;
	}
	int getcolumn() const
	{
		return column;
	}

	friend istream& operator >> (istream&, matrix&);

	friend ostream& operator << (ostream&, const matrix&);

	matrix operator - ()
	{
		matrix temp(row, column);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				temp.values[i][j] = -values[i][j];
			}
		}
		return temp;
	}
	matrix operator + (const matrix& obj)
	{
		matrix sum(row, column);
		if (row == obj.row && column == obj.column)
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					sum.values[i][j] = values[i][j] + obj.values[i][j];
				}
			}
		}
		else
		{
			cout << "NOT VALID" << endl;
		}
		return sum;
	}
	matrix operator - (const matrix& obj)
	{
		matrix subtract(row, column);
		if (row == obj.row && column == obj.column)
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < column; j++)
				{
					subtract.values[i][j] = values[i][j] - obj.values[i][j];
				}
			}
		}
		else
		{
			cout << "NOT VALID" << endl;
		}
		return subtract;
	}
	matrix operator * (const matrix& obj)
	{
		matrix multiply(row, obj.column);
		if (column == obj.row)
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < obj.column; j++)
				{
					multiply.values[i][j] = 0;
				}
			}
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < obj.column; j++)
				{
					for (int k = 0; k < column; k++)
					{
						multiply.values[i][j] += values[i][k] * obj.values[k][j];
					}
				}
			}
		}
		else
		{
			cout << "NOT VALID" << endl;
		}
		return multiply;
	}
	int* operator [] (int i)
	{
		return values[i];
	}
	matrix operator = (const matrix& obj)
	{
		for (int i = 0; i < row; i++)
		{
			delete[] values[i];
		}
		delete[] values;
		row = obj.row;
		column = obj.column;
		values = new int* [row];
		for (int i = 0; i < row; i++)
		{
			values[i] = new int[column];
		}
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				values[i][j] = obj.values[i][j];
			}
		}
		return *this;
	}
	~matrix()
	{
		for (int i = 0; i < row; i++)
		{
			delete[] values[i];
		}
		delete[] values;
		values = nullptr;
	}
};
istream& operator >> (istream& cin, matrix& obj)
{
	cout << "Enter entries of matrix: " << endl;
	for (int i = 0; i < obj.getrow(); i++)
	{
		for (int j = 0; j < obj.getcolumn(); j++)
		{
			cin >> obj.values[i][j];
		}
	}
	return cin;
}
ostream& operator << (ostream& cout, const matrix& obj)
{
	for (int i = 0; i < obj.getrow(); i++)
	{
		for (int j = 0; j < obj.getcolumn(); j++)
		{
			cout << obj.values[i][j] << " ";
		}
		cout << endl;
	}
	return cout;
}
int main()
{
	matrix a(2, 2), b(2, 2), c(2, 2);
	cin >> a >> b;
	c = -a;
	cout << c;
	c = a + b;
	cout << c;
	c = a - b;
	cout << c;
	c = a * b;
	cout << c << c[1][1] << endl;
	return 0;
}