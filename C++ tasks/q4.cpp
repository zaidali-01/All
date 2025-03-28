#include <iostream>
using namespace std;
struct node
{
	int data;
	node* next;
};
node* addtoend(node* head,int data)
{
	cout << "Enter input and -1 if u want to terminate: ";
	cin >> data;
	if (data == -1)
		return head;
	node* temp = new node;
	temp->data = data;
	head = addtoend(head, data);
	temp->next = head;
	return temp;
}
void traverse(node* head)
{
	if (head == nullptr)
		return;
	cout << head->data << " ";
	traverse(head->next);
}
void deletelist(node* head)
{
	node* current = head;
	while (current != nullptr)
	{
		current = head->next;
		delete head;
		head = current;
	}
}
int main()
{
	node* c = addtoend(nullptr, 0);
	traverse(c);
	deletelist(c);
	return 0;
}