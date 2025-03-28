#include <iostream>
using namespace std;
template <class t>
class Stack
{
    struct node
    {
        t data;
        node* next;
    };
    int size;
    node* head;
    node* tail;
public:
    Stack()
    {
        size = 0;
        head = nullptr;
        tail = nullptr;
    }
    ~Stack()
    {
        node* curr = head;
        while (curr != nullptr)
        {
            curr = curr->next;
            delete head;
            head = curr;
        }
    }
    void push(t value)
    {
        node* temp = new node;
        temp->data = value;
        temp->next = nullptr;
        if (head == nullptr)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }
        if (size == 100)
        {
            node* curr = head;
            head = head->next;
            delete curr;
        }
        else
            size++;
    }
    t pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return -1;
        }
        t value = tail->data;
        if (head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            node* curr = head;
            while (curr->next != tail)
            {
                curr = curr->next;
            }
            delete tail;
            tail = curr;
            tail->next = nullptr;
        }
        size--;
        return value;
    }
private:
    bool isEmpty()
    {
        if (size == 0)
            return true;
        return false;
    }
};

int main()
{
    Stack<int> st;
    while (1)
    {
        int a;
        cout << "Enter 0 if u want to push and 1 if u want to pop and -1 if u want to exit: ";
        cin >> a;
        while (a != 0 && a != 1 && a != -1)
        {
            cout << "Invalid input!" << endl << "Re-enter input: ";
            cin >> a;
        }
        if (a == 0)
        {
            int b;
            cout << "How many values u want to push: ";
            cin >> b;
            for (int i = 0; i < b; i++)
            {
                int c;
                cout << "Enter value: ";
                cin >> c;
                st.push(c);
            }
        }
        if (a == 1)
        {
            int b;
            cout << "how many values u want to pop: ";
            cin >> b;
            for (int i = 0; i < b; i++)
            {
                int c = st.pop();
                if (c != -1)
                    cout << c << " ";
                else
                    break;
            }
            cout << endl;
        }
        if (a == -1)
        {
            break;
        }
    }
    return 0;
}
