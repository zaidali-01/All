#include<iostream>
using namespace std;

class list {
	struct node {
		node* next;
		node* child;
		int data;
	};
	node* head;
	node* tail;
public:

	list()
	{
		head = nullptr;
		tail = nullptr;
	}
	bool isempty()
	{
		if (head == nullptr && tail == nullptr)
		{
			return true;
		}
		return false;
	}
	int size() const
	{
		int i = 0;
		node* current;
		current = head;
		while (current != nullptr)
		{
			i++;
			current = current->next;
		}
		return i;
	}
	node* gethead()
	{
		return head;
	}
	bool insertatstart(int const data)
	{
		node* temp = new node;
		temp->child = nullptr;
		if (temp == NULL) return false;
		else {
			temp->data = data;
			temp->next = head;
			if (isempty())
			{
				tail = temp;
			}
			head = temp;
			return true;
		}
	}
	bool insertatend(int const data)
	{
		node* temp = new node;
		temp->child = nullptr;
		if (temp == NULL) return false;
		else {
			temp->data = data;
			temp->next = nullptr;
			if (isempty())
			{
				head = temp;
			}
			else
				tail->next = temp;
			tail = temp;
			return true;
		}
	}
	void deletefromstart()
	{
		node* current;
		current = head;
		if (!isempty())
		{
			head = head->next;
			delete current;
		}
	}
	void deletefromend()
	{
		node* current, * previous = nullptr;
		current = head;
		if (!isempty())
		{
			while (current != tail)
			{
				previous = current;
				current = current->next;
			}
			tail = previous;
			delete current;
		}
	}
	void printforward() const
	{
		node* current;
		current = head;
		while (current != nullptr)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
	void insertchild(int index,node* m)
	{
		node* current = head;
		int i = 0;
		while (current!=nullptr)
		{
			if (i == index)
			{
				current->child = m;
			}
			i++;
			current = current->next;
		}
	}
	void flatlist()
	{
		node* current = head;
		while (current != nullptr)
		{
			if (current->child != nullptr)
			{
				node* c = current->child, * a = nullptr;
				
				while (c != nullptr)
				{
					a = c;
					c = c->next;
				}
				a->next = current->next;
				current->next = current->child;
			}
			current = current->next;
		}
	}
	~list()
	{
		node* temp1, * temp2;
		temp1 = head;
		while (temp1 != nullptr)
		{
			temp2 = temp1->next;
			delete temp1;
			temp1 = temp2;
		}
		head = nullptr;
		tail = nullptr;
	}
};
int main()
{
	int a;
	cout << "Enter no. of linklist level: ";
	cin >> a;
	list* l = new list[a];
	for (int i = 0; i < a; i++)
	{
		int b;
		cout << "Enter no. of elements in the "<<i+1<<" level: ";
		cin >> b;
		for (int j = 0; j < b; j++)
		{
			int c;
			cout << "Enter element: ";
			cin >> c;
			l[i].insertatend(c);
		}
	}
	bool flag = true;
	while (1)
	{
		cout << "Enter 0 if u want to insert child ";
		cin >> flag;
		if (flag)
			break;
		cout << "Enter the level u want to insert to ";
		int x, y,z;
		cin >> x;
		cout << "Enter the level u want to insert ";
		cin >> y;
		cout << "Enter the index u want to insert to ";
		cin >> z;
		l[x - 1].insertchild(z, l[y - 1].gethead());
	}
	l[0].flatlist();
	return 0;
}