#include<iostream>
#include<string>
using namespace std;
template<class t>
class queue
{
	t* arr;
	int maxsize;
	int front;
	int rear;
	int size;
public:
	queue(int s = 10)
	{
		maxsize = s;
		arr = new t[maxsize];
		size = 0;
		front = 0;
		rear = 0;
	}
	bool isfull()
	{
		if (size == maxsize)
			return true;
		return false;
	}
	bool isempty()
	{
		if (size == 0)
			return true;
		return false;
	}
	int getsize()
	{
		return size;
	}
	bool enqueue(t a)
	{
		if (this->isfull())
			return false;
		else
		{
			arr[rear] = a;
			size++;
			rear = (rear + 1) % maxsize;
			return true;
		}
	}
	bool dequeue(t& a)
	{
		if (this->isempty())
			return false;
		else
		{
			a = arr[front];
			front = (front + 1) % maxsize;
			size--;
			return true;
		}
	}
	void print()
	{
		t a;
		for (int i = 0; i < this->getsize(); i++)
		{
			this->dequeue(a);
			cout << a << " ";
			this->enqueue(a);
		}
		cout << endl;
	}
	void integers(int k,int n)
	{
		queue<int> q[10];
		int x = 1;
		for (int j = 0; j < k; j++)
		{
			for (int i = 0; i < n; i++)
			{
				int a, b;
				this->dequeue(a);
				b = a / x;
				b = b % 10;
				q[b].enqueue(a);
			}
			int z;
			for (int l=0;l < 10;l++)
			{
				while (q[l].dequeue(z))
				{
					this->enqueue(z);
				}
			}
			x = x * 10;
		}
	}
	void strings(int k,int n)
	{
		queue<string> q[127];
		for (int i = 0; i < n; i++)
		{
			string x;
			this->dequeue(x);
			int y = x.size();
			if (y < k)
			{
				string u;
				for (int j = 0; j < k - y; j++)
				{
					u = u + " ";
				}
				u = u + x;
				this->enqueue(u);
			}
			else
			    this->enqueue(x);
		}
		for (int j = k-1; j >= 0; j--)
		{
			for (int i = 0; i < n; i++)
			{
				string a;
				int b;
				this->dequeue(a);
				b = int(a[j]);
				q[b].enqueue(a);
			}
			string z;
			for (int l = 0; l < 127; l++)
			{
				while (q[l].dequeue(z))
				{
					this->enqueue(z);
				}
			}
		}
	}
	~queue()
	{
		delete[] arr;
	}
};
int main()
{
	int a;
	cout << "Enter 0 for sorting integers and enter 1 for sorting strings: ";
	cin >> a;
	if (a == 0)
	{
		cout << "Enter no. of elements: ";
		cin >> a;
		queue<int> obj(a);
		int k;
		cout << "Enter max no. of digits: ";
		cin >> k;
		for (int i = 0; i < a; i++)
		{
			int b;
			cout << "Enter number: ";
			cin >> b;
			while (b < 0)
			{
				cout << "Re-enter number as negative cannot be processed: ";
				cin >> b;
			}
			obj.enqueue(b);
		}
		int c;
		cout << "Enter 0 if u want to sort: ";
		cin >> c;
		if (!c)
		{
			obj.integers(k,a);
		}
		obj.print();
	}
	else if (a == 1)
	{
		cout << "Enter no. of words: ";
		cin >> a;
		queue<string> obj(a);
		int k;
		cout << "Enter max no. of length: ";
		cin >> k;
		for (int i = 0; i < a; i++)
		{
			string b;
			cout << "Enter word: ";
			cin >> b;
			obj.enqueue(b);
		}
		int c;
		cout << "Enter 0 if u want to sort: ";
		cin >> c;
		if (!c)
		{
			obj.strings(k, a);
		}
		obj.print();
	}
	else
		cout << "Invalid command!";
	return 0;
}