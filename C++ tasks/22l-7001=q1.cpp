#include<iostream>
#include<vector>
using namespace std;
template<class k,class v>
class specialBST
{
	struct node
	{
	public:
		k key;
		v value;
		node* left;
		node* right;
		node()
		{
			left = nullptr;
			right = nullptr;
		}
	};
	node* root;
public:
	specialBST()
	{
		root = nullptr;
	}
	~specialBST()
	{
		destroy(root);
	}
	void destroy(node* nod)
	{
		if (nod == nullptr)
			return;
		destroy(nod->left);
		destroy(nod->right);
		delete nod;
	}
	bool duplicate(k num, node* nod)
	{
		if (nod == nullptr)
			return false;
		if (nod->key > num)
			return duplicate(num, nod->left);
		else if (nod->key < num)
			return duplicate(num, nod->right);
		else
			return true;
	}
	node* rightRotate(node*& y)
	{
		node* x = y->left;
		node* z = x->right;
		x->right = y;
		y->left = z;
		return x;
	}
	node* leftRotate(node*& x)
	{
		node* y = x->right;
		node* z = y->left;
		y->left = x;
		x->right = z;
		return y;
	}
	void makeroot(node* n, node*& nod)
	{
		if (n == root)
			return;
		if (nod->right == n)
		{
			nod = leftRotate(nod);
			this->makeroot(n, root);
			return;
		}
		else if (nod->left == n)
		{
			nod = rightRotate(nod);
			this->makeroot(n, root);
			return;
		}
		if (nod->key > n->key)
			this->makeroot(n, nod->left);
		else if (nod->key < n->key)
			this->makeroot(n, nod->right);
	}
	bool insert(k num1, v num2)
	{
		if (duplicate(num1, root))
			return false;
		node* n = inserting(num1, num2, root);
		this->makeroot(n, root);
		return true;
	}
	node* inserting(k num1, v num2, node*& nod)
	{
		if (nod == nullptr)
		{
			nod = new node;
			nod->key = num1;
			nod->value = num2;
			return nod;
		}
		if (nod->key > num1)
			return inserting(num1, num2, nod->left);
		else if (nod->key < num1)
			return inserting(num1, num2, nod->right);
	}
	bool deleted(k num)
	{
		if (!duplicate(num, root))
			return false;
		node* n = deleting(num, root);
		this->makeroot(n, root);
		return true;
	}
	node* deleting(k num, node*& nod)
	{
		if (nod->key > num)
		{
			node* n = deleting(num, nod->left);
			if (n == nullptr)
				return nod;
			return n;
		}
		else if (nod->key < num)
		{
			node* n = deleting(num, nod->right);
			if (n == nullptr)
				return nod;
			return n;
		}
		else
		{
			deleteNode(nod);
			return nod;
		}
	}
	void getPredecessor(node* nod, k& data, v& num)
	{
		while (nod->right != nullptr)
			nod = nod->right;
		data = nod->key;
		num = nod->value;
	}
	void deleteNode(node*& nod)
	{
		node* temp;
		temp = nod;
		if (nod->left == nullptr)
		{
			nod = nod->right;
			delete temp;
		}
		else if (nod->right == nullptr)
		{
			nod = nod->left;
			delete temp;
		}
		else
		{
			k d;
			v e;
			getPredecessor(nod->left, d, e);
			nod->key = d;
			nod->value = e;
			deleting(d, nod->left);
		}

	}
	v* search(k num)
	{
		node* n = searching(num, root);
		this->makeroot(n, root);
		if (n->key != num)
			return nullptr;
		return &n->value;
	}
	node* searching(k num, node* nod)
	{
		if (nod == nullptr)
		{
			return nullptr;
		}
		if (nod->key > num)
		{
			node* n = searching(num, nod->left);
			if (n == nullptr)
				return nod;
			return n;
		}
		else if (nod->key < num)
		{
			node* n = searching(num, nod->right);
			if (n == nullptr)
				return nod;
			return n;
		}
		else
		{
			return nod;
		}
	}
	int height(node* node)
	{
		if (node == nullptr)
			return 0;
		int lheight = height(node->left);
		int rheight = height(node->right);
		if (lheight > rheight) 
			return (lheight + 1);
		return (rheight + 1);
	}
	void currentlevel(node* nod, int level, vector<v>*& a)
	{
		if (nod == nullptr)
			return;
		if (level == 1)
			a->push_back(nod->value);
		else if (level > 1) 
		{
			currentlevel(nod->left, level - 1, a);
			currentlevel(nod->right, level - 1, a);
		}
	}
	int totalnodes(node* nod)
	{
		if (nod == nullptr)
			return 0;
		return totalnodes(nod->left) + totalnodes(nod->right) + 1;
	}
	vector<v>* levelwise()
	{
		vector<v>* a = new vector<v>;
		int h = height(root);
		for (int i = 1; i <= h; i++)
			currentlevel(root, i, a);
		return a;
	}
	void inordering(node* nod, vector<v>*& a)
	{
		if (nod == nullptr)
			return;
		inordering(nod->left, a);
		a->push_back(nod->value);
		inordering(nod->right, a);
	}
	vector<v>* inorder()
	{
		vector<v>* a = new vector<v>;
		inordering(root, a);
		return a;
	}
};
int main()
{
	specialBST<int,int> obj;
	while (1)
	{
		char option;
		cout << "Enter I if u want to insert" << endl;
		cout << "Enter D if u want to delete" << endl;
		cout << "Enter S if u want to search" << endl;
		cout << "Enter L if u want to print level-wise" << endl;
		cout << "Enter O if u want to print in-order" << endl;
		cout << "Enter E if u want to exit" << endl;
		cin >> option;
		while (option != 'I' && option != 'D' && option != 'S' && option != 'L' && option != 'O' && option != 'E')
		{
			cout << "Invalid input!\nRe-enter: ";
			cin >> option;
		}
		if (option == 'I')
		{
			int k, v;
			cout << "Enter key: ";
			cin >> k;
			cout << "Enter v: ";
			cin >> v;
			if (obj.insert(k, v))
				cout << "Successfully inserted!" << endl;
			else
				cout << "Key already exists!" << endl;
		}
		if (option == 'D')
		{
			int k;
			cout << "Enter key";
			cin >> k;
			if (obj.deleted(k))
				cout << "Successfully deleted!" << endl;
			else
				cout << "Key doesn't exists!" << endl;
		}
		if (option == 'S')
		{
			int k;
			cout << "Enter key";
			cin >> k;
			int* a = obj.search(k);
			if (a != nullptr)
				cout << "Key found with value " << *a << endl;
			else
				cout << "Key not found" << endl;
		}
		if (option == 'L')
		{
			vector<int>* a = obj.levelwise();
			for (int i = 0; i < a->size(); i++)
			{
				cout << a->at(i) << " ";
			}
			delete a;
			cout << endl;
		}
		if (option == 'O')
		{
			vector<int>* a = obj.inorder();
			for (int i = 0; i < a->size(); i++)
			{
				cout << a->at(i) << " ";
			}
			delete a;
			cout << endl;
		}
		if (option == 'E')
			break;
	}
	cout << "GOOD BYE!";
}