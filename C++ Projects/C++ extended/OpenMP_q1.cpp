#include <iostream>
#include <ctime>
#include <omp.h>
using namespace std;

struct node
{
    int value;
    node* left;
    node* right;
    node(int v)
    {
        value = v;
        left = nullptr;
        right = nullptr;
    }
};

node* insert(node* root, int val)
{
    if (root==nullptr) 
    {
        return new node(val);
    }
    if (val < root->value)
    {
        root->left = insert(root->left, val);
    }
    else
    {
        root->right = insert(root->right, val);
    }
    return root;
}

node* createtree(int num)
{
    node* root = nullptr;
    srand(time(0));
    for (int i = 0; i < num; i++)
    {
        int random = rand() % 100 + 1;
        root = insert(root, random);
    }
    return root;
}

bool search(node* root, int target)
{
    if (root==nullptr) 
        return false;
    bool found = false;
    
    #pragma omp parallel sections shared(found)
    {
        #pragma omp section
        {
            if (root->value == target) 
                found = true;
        }
        
        #pragma omp section
        {
            if (found!=true && root->left) 
                found = search(root->left, target);
        }
        
        #pragma omp section
        {
            if (found!=true && root->right)
                found = search(root->right, target);
        }
    }
    return found;
}

void print(node* root)
{
    if (root==nullptr) 
        return;
    print(root->left);
    cout << root->value << " ";
    print(root->right);
}

int main()
{
    node* root = createtree(30);
    cout << "Binary Tree:" << endl;
    print(root);
    cout << endl;
    
    int target = 0;
    cout << "Enter value to search: ";
    cin >> target;
    
    bool found = search(root, target);
    
    if (found)
        cout << "Value " << target << " found in the tree!";
    else
        cout << "Value " << target << " not found in the tree!";
    return 0;
}
