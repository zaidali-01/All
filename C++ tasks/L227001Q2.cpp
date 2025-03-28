#include <iostream>
using namespace std;
struct Node
{
    int data;
    struct Node* next;
};

void zigZagList(Node* head)
{
    bool flag = true;
    Node* current = head;
    while (current->next != NULL)
    {
        if (flag)
        {
            if (current->data > current->next->data)
                swap(current->data,
                    current->next->data);
        }
        else
        {
            if (current->data <
                current->next->data)
                swap(current->data,
                    current->next->data);
        }

        current = current->next;
        flag = !flag;
    }
}
void push(Node** head_ref,
    int new_data)
{
    struct Node* new_Node = new Node;
    new_Node->data = new_data;
    new_Node->next = (*head_ref);
    (*head_ref) = new_Node;
}

void printList(struct Node* Node)
{
    while (Node != NULL)
    {
        cout << Node->data << " ";
        Node = Node->next;
    }
    cout << endl;
}
int main()
{
    Node* head = NULL;
    push(&head, 7);
    push(&head, 6);
    push(&head, 5);
    push(&head, 2);
    push(&head, 1);

    printf("Given linked list ");
    printList(head);

    zigZagList(head);

    printf("Zig Zag Linked list ");
    printList(head);

    return (0);
}