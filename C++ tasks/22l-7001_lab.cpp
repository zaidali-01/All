#include <iostream>
using namespace std;

class BST
{
public:
    struct node
    {
        int data;
        node* left;
        node* right;
        node(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    node* root;

    BST() : root(nullptr) {}


};

class AVL : public BST
{
public:
    AVL() : BST() {}

    AVL(const AVL& other) : BST() 
    {
        if (other.root)
        {
            this->root = copyTree(other.root);
        }
    }

    ~AVL()
    {
        clearTree(root);
    }


    void insert(int value)
    {
        root = insertRecursive(root, value);
    }


    int height() const
    {
        return getHeight(root);
    }

    node* copyTree(node* nod)
    {
        if (!nod) 
        {
            return nullptr;
        }

        node* newNode = new node(nod->data);
        newNode->left = copyTree(nod->left);
        newNode->right = copyTree(nod->right);
        return newNode;
    }


    void clearTree(node* nod)
    {
        if (nod)
        {
            clearTree(nod->left);
            clearTree(nod->right);
            delete nod;
        }
    }

    int getHeight(node* node) const 
    {
        if (!node)
        {
            return 0;
        }
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return 1 + max(leftHeight, rightHeight);
    }


    node* rightRotate(node* y)
    {
        node* x = y->left;
        node* z = x->right;

        x->right = y;
        y->left = z;

        return x;
    }


    node* leftRotate(node* x)
    {
        node* y = x->right;
        node* z = y->left;

        y->left = x;
        x->right = z;

        return y;
    }


    node* insertRecursive(node* nod, int value)
    {

        if (!nod)
        {
            return new node(value);
        }

        if (value < nod->data) 
        {
            nod->left = insertRecursive(nod->left, value);
        }
        else if (value > nod->data) 
        {
            nod->right = insertRecursive(nod->right, value);
        }
        else {

            return nod;
        }


        int leftHeight = getHeight(nod->left);
        int rightHeight = getHeight(nod->right);

        int balance = leftHeight - rightHeight;


        if (balance > 1)
        {
            if (value < nod->left->data) 
            {
                return rightRotate(nod);
            }
            else {

                nod->left = leftRotate(nod->left);
                return rightRotate(nod);
            }
        }

        if (balance < -1) 
        {
            if (value > nod->right->data) 
            {

                return leftRotate(nod);
            }
            else 
            {

                nod->right = rightRotate(nod->right);
                return leftRotate(nod);
            }

        }
        return nod;
    }

    bool searchR(node* nod, int d) 
    {

        if (nod) 
        {
            if (nod->data > d)
                searchR(nod->left, d);

            else if (nod->data < d)
                searchR(nod->right, d);

            else
                cout << "found " << d << endl;

            return true;
        }
        else
            cout << "not found " << d << endl;

        return false;

    }

    bool searchR(int d) 
    {

        return searchR(root, d);

    }

    void InOrder()

    {
        InOrder(root);
    }

    void InOrder(node* t)

    {
        if (t)
        {
            InOrder(t->left);
            visit(t);
            InOrder(t->right);
        }

    }

    void visit(node* a)
    {
        cout << a->data << " ";
    }

};

int main() 
{
    AVL obj;
    obj.insert(4);
    obj.insert(1);
    obj.insert(12);
    obj.insert(9);
    obj.insert(71);
    obj.insert(0);
    obj.insert(3);
    obj.insert(102);
    obj.insert(81);
    obj.insert(6);
    obj.insert(28);
    obj.insert(67);
    obj.insert(45);

    cout << "AVL Tree Height: " << obj.height() << endl;
    obj.searchR(100);
    obj.InOrder();
    return 0;
}