#include<iostream>
using namespace std;

template <class t>
class sortedset {
	struct node {
		node* next;
		t data;
	};
	node* head;
	node* tail;
public:

	sortedset()
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
		node* current = head;
		while (current != nullptr)
		{
			i++;
			current = current->next;
		}
		return i;
	}
	void insert(t data)
	{
		node* temp = new node;
		temp->data = data;
		node* current = head, * previous = nullptr;
		while (current != nullptr && current->data < data)
		{
			previous = current;
			current = current->next;
		}
		if (current!=nullptr && current->data == data)
		{
			delete temp;
			return;
		}
		temp->next = current;
		if (current == nullptr)
		{
			tail = temp;
		}
		if (current == head)
			head = temp;
		else
			previous->next = temp;
	}
	void delet(int const index)
	{
		int a = 1;
		node* current = head, * previous = nullptr;
		while (current != nullptr)
		{
			if (a == index)
			{
				if (a == 1)
				{
					head = current->next;
				}
				else
					previous->next = current->next;
				if (index == this->size())
				{
					tail = previous;
				}
				delete current;
				break;
			}
			previous = current;
			current = current->next;
			a++;
		}
	}
	void print() const
	{
		node* current;
		current = head;
		if (head == nullptr)
		{
			cout << "The set is empty!";
		}
		while (current != nullptr)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
	void unionset(sortedset<t> const& otherset)
	{
		node* c = otherset.head;
		while (c != nullptr)
		{
			this->insert(c->data);
			c = c->next;
		}
	}
	~sortedset()
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
	sortedset<int> obj[2];
	for (int z = 0; z < 2; z++)
	{
		int a, b;
		cout << "Enter size for set " << z + 1 <<": ";
		cin >> a;
		for (int i = 0; i < a; i++)
		{
			cout << "Enter element: ";
			cin >> b;
			obj[z].insert(b);
		}
		obj[z].print();
		bool flag = true;
		while (1)
		{
			cout << "Enter 0 if u want to delete an element: ";
			cin >> flag;
			if (obj[z].size() == 0 && !flag)
			{
				cout << "Cannot delete as the set is empty!";
				break;
			}
			if (flag)
				break;
			else
			{
				cout << "Enter the index u want to delete: ";
				int k;
				cin >> k;
				while (k <= 0 && k > obj[z].size())
				{
					cout << "Index doesn't exist!\nRe-enter index: ";
					cin >> k;
				}
				obj[z].delet(k);
				obj[z].print();
			}
		}
		obj[z].print();
	}
	bool flag = true;
	cout << "Enter 0 if you want to take union of both: ";
	cin >> flag;
	if (!flag)
	{
		obj[0].unionset(obj[1]);
		obj[0].print();
	}
	return 0;
}