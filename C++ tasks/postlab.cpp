#include<iostream>
using namespace std;
class stack {
private:
    int size; 
    int index; 
    int* array; 
public:

    stack(int s)
    {
        size = s;
        index = 0;
        array = new int[size];
    }
    ~stack()
    {
        delete[] array;
    }
    void push(int n) 
    {
        if (!isFull())
        {
            array[index] = n;
            index++;
        }
        else
        {
            cout << "stack full" << endl;
        }
    }
    void pop() 
    {
        if (!isEmpty())
        {
            index--;
        }
        else
        {
            cout << "stack is empty" << endl;
        }
    }
    bool isFull()
    {
        return (index == size);
    }


    bool isEmpty()
    {
        return (index == 0);
    }
    void print()
    {
        if (isEmpty())
        {
            cout << "Stack is empty";
        }
        for (int i = 0; i < index; i++)
        {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    int const& top()
    {
        return array[index-1];
    }

    int sizee()
    {
        return index;
    }
    void clear()
    {
        while (!isEmpty())
        {
            pop();
        }
    }
    void duplicateTop() 
    {
        if (isFull())
        {
            cout << "stack is full so no duplication " << endl;
        }
        else
        {
            int c;
            c = top();
            push(c);
        }
    }

    void swaptwo() {
        if (isEmpty() || index == 1)
        {
            cout << "no swapping " << endl;
        }
        else 
        {
            int a, b;
            a = top();
            pop();
            b = top();
            pop();
            push(a);
            push(b);

        }
    }
    void removedata(int data) 
    {
        if (isEmpty())
            return;
        int i = 0;
        int arr[10];
        while (!isEmpty()) 
        {
            if (top() == data)
            {
                pop();
            }
            else
            {
                arr[i] = top();
                pop();
                i++;
            }
        }
        while (i > 0)
        {
            push(arr[--i]);
        }
    }
    void reverse()
    {
        int i = 0;
        int arr[10];
        while (!isEmpty())
        {
            arr[i++] = top();
            pop();
        }

        for (int j = 0; j < i; j++)
        {
            push(arr[j]);
        }
    }
    bool ispalindrome()
    {
        int a = sizee() / 2;
        for (int i = 0; i < a; i++)
        {
            if (array[i] != array[index - i - 1])
                return false;
        }
        return true;
    }
};
int main() 
{
    stack obj(5);
    obj.push(1);
    obj.push(2);
    obj.push(2);
    obj.push(1);
    obj.print();
    obj.swaptwo();
    obj.print();
    obj.reverse();
    obj.print();
    obj.duplicateTop();
    obj.print();
    obj.removedata(1);
    obj.print();
    obj.clear();
    obj.print();
    if (obj.ispalindrome())
        cout << "Palindrome" << endl;
    return 0;
}