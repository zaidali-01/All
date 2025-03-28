#include<iostream>
using namespace std;
class heap
{
	int size, maxsize, tsize;
	int** h;
public:
	heap(int s=100)
	{
		maxsize = s;
		size = 0;
		tsize = 0;
		h = new int*[2];
		h[0] = new int[maxsize];
		h[1] = new int[maxsize];
	}
	void reheapupmin(int root, int bottom)
	{
		int parent;
		if (bottom > root)
		{
			parent = (bottom - 1) / 2;
			if (h[0][parent] > h[0][bottom])
			{
				int temp = h[0][parent];
				h[0][parent] = h[0][bottom];
				h[0][bottom] = temp;
				reheapupmin(root, parent);
			}
		}
	}
	void reheapupmax(int root, int bottom)
	{
		int parent;
		if (bottom > root)
		{
			parent = (bottom - 1) / 2;
			if (h[1][parent] < h[1][bottom])
			{
				int temp = h[1][parent];
				h[1][parent] = h[1][bottom];
				h[1][bottom] = temp;
				reheapupmax(root, parent);
			}
		}
	}
	void reheapdownmin(int root, int bottom)
	{
		int maxchild, rightchild, leftchild;
		leftchild = 2 * root + 1;
		rightchild = 2 * root + 2;
		if (leftchild <= bottom)
		{
			if (leftchild == bottom)
				maxchild = leftchild;
			else
			{
				if (h[0][leftchild] >= h[0][rightchild])
					maxchild = rightchild;
				else
					maxchild = leftchild;
			}
			if (h[0][root] > h[0][maxchild])
			{
				int temp = h[0][maxchild];
				h[0][maxchild] = h[0][root];
				h[0][root] = temp;
				reheapdownmin(maxchild, bottom);
			}
		}
	}
	void reheapdownmax(int root, int bottom)
	{
		int maxchild, rightchild, leftchild;
		leftchild = 2 * root + 1;
		rightchild = 2 * root + 2;
		if (leftchild <= bottom)
		{
			if (leftchild == bottom)
				maxchild = leftchild;
			else
			{
				if (h[1][leftchild] <= h[1][rightchild])
					maxchild = rightchild;
				else
					maxchild = leftchild;
			}
			if (h[1][root] < h[1][maxchild])
			{
				int temp = h[1][maxchild];
				h[1][maxchild] = h[1][root];
				h[1][root] = temp;
				reheapdownmax(maxchild, bottom);
			}
		}
	}
	bool insert(int d)
	{
		if (tsize == maxsize*2)
			return false;
		if (tsize % 2 != 0)
		{
			if (h[0][size] <= d)
			{
				h[1][size] = d;
				reheapupmax(0, size);
			}
			else
			{
				h[1][size] = h[0][size];
				h[0][size] = d;
				reheapupmin(0, size);
			}
			size++;
		}
		else
		{
			if (size == 0)
				h[0][size] = d;
			else
			{
				int p = (size - 1) / 2;
				if (h[1][p] < d)
				{
					h[1][size] = d;
					reheapupmax(0, size);
					h[0][size] = h[1][size];
				}
				else
				{
					h[0][size] = d;
					reheapupmin(0, size);
				}
			}
		}
		tsize++;
		return true;
	}
	bool delet()
	{
		if (tsize == 0)
			return false;
		if (tsize == 1)
		{
			tsize = 0;
		}
		else if (tsize % 2 == 0)
		{
			h[0][0] = h[0][size - 1];
			h[1][0] = h[1][size - 1];
			size--;
			reheapdownmin(0, size - 1);
			reheapdownmax(0, size - 1);
		}
		else
		{
			h[0][0] = h[0][size];
			h[1][0] = h[1][size - 1];
			size--;
			reheapdownmin(0, size);
			reheapdownmax(0, size - 1);
			if (h[0][size - 1] > h[1][size - 1])
			{
				int temp = h[0][size - 1];
				h[0][size - 1] = h[1][size - 1];
				h[1][size - 1] = temp;
			}
		}
		return true;
	}
	bool update(int old, int d)
	{
		int* a = nullptr, * b = nullptr, i;
		for (i = 0; i < size; i++)
		{
			if (old == h[1][i])
			{
				b = &i;
				break;
			}
			if (old == h[0][i])
			{
				a = &i;
				break;
			}
			if (tsize % 2 != 0 && i == size - 1 && old == h[0][i + 1])
			{
				a = &i;
			}
		}
		if (a == nullptr && b == nullptr)
			return false;
		else if (a)
		{
			h[0][*a] = h[0][size - 1 + tsize % 2];
			reheapdownmin(*a, size - 2 + tsize % 2);
			if (tsize % 2 == 0)
			{
				size--;
				h[0][size] = h[1][size];
			}
			else if (h[0][size - 1] > h[1][size - 1])
			{
				int temp = h[0][size - 1];
				h[0][size - 1] = h[1][size - 1];
				h[1][size - 1] = temp;
			}
			tsize--;
		}
		else
		{
			h[1][*b] = h[1 - tsize % 2][size - 1 + tsize % 2];
			reheapdownmax(*b, size - 2 + tsize % 2);
			if (tsize % 2 == 0)
				size--;
			else if (h[0][size - 1] > h[1][size - 1])
			{
				int temp = h[0][size - 1];
				h[0][size - 1] = h[1][size - 1];
				h[1][size - 1] = temp;
			}
			tsize--;
		}
		insert(d);
		return true;
	}
	void display()
	{
		int a = 0, b = 1;
		for (int i = 0; i < size; i++)
		{
			cout << h[0][i] << "," << h[1][i] << " ";
			a++;
			if (a == b)
			{
				cout << endl;
				a = 0;
				b *= 2;
			}
		}
		if (tsize % 2 != 0)
			cout << h[0][size];
		cout << endl;
	}
	~heap()
	{
		delete[] h[0];
		delete[] h[1];
		delete[] h;
	}
};
int main()
{
	heap obj;
	while (1)
	{
		char opt;
		cout << "Enter I to insert " << endl;
		cout << "Enter D to delete " << endl;
		cout << "Enter U to update " << endl;
		cout << "Enter P to display " << endl;
		cout << "Enter E to exit " << endl;
		cin >> opt;
		while (opt != 'I' && opt != 'D' && opt != 'U' && opt != 'P' && opt != 'E')
		{
			cout << "Invalid! Re-enter: ";
			cin >> opt;
		}
		if (opt == 'I')
		{
			int d;
			cout << "Enter number: ";
			cin >> d;
			if (obj.insert(d))
			{
				cout << "successfully inserted!" << endl;
			}
			else
				cout << "cannot insert!" << endl;
		}
		if (opt == 'D')
		{
			if (obj.delet())
				cout << "successfully deleted!" << endl;
			else
				cout << "cannot delete!" << endl;
		}
		if (opt == 'U')
		{
			int a, b;
			cout << "Enter number u want to update: ";
			cin >> a;
			cout << "Enter new number: ";
			cin >> b;
			if (obj.update(a, b))
				cout << "successfully updated!" << endl;
			else
				cout << "cannot update!" << endl;
		}
		if (opt == 'P')
		{
			obj.display();
		}
		if (opt == 'E')
			break;
	}
	return 0;
}