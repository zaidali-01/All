#include <iostream>
using namespace std;
class Stack 
{
    int* data;
    int maxsize;
    int size;
    int top;
    int bottom;
    bool flip;
public:
    Stack(int s = 10) 
    {
        maxsize = s;
        size = 0;
        data = new int[maxsize];
        top = 0;
        bottom = 0;
        flip = false;
    }
    ~Stack()
    {
        delete[] data;
    }
    void push(int value) 
    {
        if (isFull())
        {
            doubleCapacity();
        }
        if (flip)
        {
            top = (top - 1 + maxsize) % maxsize;
            data[top] = value;
        }
        else
        {
            data[top] = value;
            top = (top + 1) % maxsize;
        }
        size++;
    }
    int pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return -1;
        }
        int value;
        if (flip)
        {
            value = data[top];
            top = (top + 1) % maxsize;
        }
        else
        {
            top = (top - 1 + maxsize) % maxsize;
            value = data[top];
        }
        size--;
        return value;
    }
    void flipStack()
    {
        int a = bottom;
        bottom = top;
        top = a;
        if (flip)
            flip = false;
        else
            flip = true;
    }
    void print()
    {
        int c, a;
        if (flip)
        {
            c = top;
            a = (bottom + 1) % maxsize;
        }
        else
        {
            c = bottom;
            a = top;
        }
        while (c != a)
        {
            cout << data[c] << " ";
            c = (c + 1) % maxsize;
        }
        cout << endl;
    }
private:
    bool isFull()
    {
        if(size == maxsize)
             return true;
        return false;
    }
    bool isEmpty()
    {
        if(size == 0)
             return true;
        return false;
    }
    void doubleCapacity() 
    {
        int s = maxsize * 2;
        int* d = new int[s];
        int c,a;
        if (flip)
        {
            c = top;
            a = (bottom + 1) % maxsize;
            top = 0;
            bottom = size - 1;
        }
        else
        {
            c = bottom;
            a = top;
            bottom = 0;
            top = size;
        }
        int i = 0;
        while (c != a)
        {
            d[i] = data[c];
            i++;
            c = (c + 1) % maxsize;
        }
        delete[] data;
        data = d;
    }
};

int main()
{
    Stack st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.print();
    return 0;
}
