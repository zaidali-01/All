#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class BT
{
public:
	struct node
	{
		int data;
		char element;
		int code;
		node* left;
		node* right;
	public:
		node()
		{
			left = nullptr;
			right = nullptr;
		}
	};
	node* root;
	BT()
	{
		root = nullptr;
	}
	void encoding()
	{
		char arr[100];
		int fre[100];
		int a = 0;
		string read;
		ifstream in;
		in.open("text.txt");
		while (!in.eof())
		{
			getline(in, read);
			for (int i= 0; i < read.size(); i++)
			{
				bool flag = true;
				for (int j = 0; j < a; j++)
				{
					if (arr[j] == read[i])
					{
						fre[j]++;
						flag = false;
						break;
					}
				}
				if (flag)
				{
					arr[a] = read[i];
					fre[a++] = 1;
				}
			}
		}
		in.close();
		this->bubblesort(arr, fre, a);
		root = this->develop(root, arr, fre, a, 0);
		in.open("text.txt");
		while (!in.eof())
		{
			ofstream out;
			out.open("encoding.txt",ios_base::app);
			getline(in, read);
			for (int i = 0; i < read.size(); i++)
			{
				this->search(root, read[i],0);
			}
			out << endl;
			out.close();
		}
	}
	void decoding()
	{
		string read;

		ifstream in;
		int a = this->getlevel(root);
		in.open("encoding.txt");
		ofstream out;
		out.open("decoding.txt", ios_base::app);
		while (!in.eof())
		{
			getline(in, read);
			for (int i = 0; i < read.size(); i++)
			{
				int arr[20];
				int b = 0;
				for (int j = 0; j < a; j++)
				{
					arr[j] = read[i]-48;
					b++;
					if (read[i] != '0' && j!=a-1)
					{
						i++;
					}
					else
					{
						break;
					}
				}
				node* nod = root;
				
				for (int j = 0; j < b; j++)
				{
					if (arr[j] == 0)
					{
						nod = nod->left;
					}
					else
					{
						nod = nod->right;
					}
					if (j == b - 1)
					{
						cout << nod->element;
						out << nod->element;
					}
				}
			}
			cout << endl;
			out << endl;
		}
		out.close();
		in.close();
	}
	int getlevel(node* nod)
	{
		if (nod->right == nullptr)
			return 0;
		return this->getlevel(nod->right)+1;
	}
	node* develop(node*& nod, char* arr, int* fre, int n, int index)
	{
		if (index == n - 1)
		{
			nod = new node;
			nod->element = arr[index];
			nod->data = fre[index];
			return nod;
		}
		nod = new node;
		nod->right = develop(nod->right, arr, fre, n, index + 1);
		nod->right->code = 1;
		nod->left = new node;
		nod->left->element = arr[index];
		nod->left->data = fre[index];
		nod->left->code = 0;
		nod->data = nod->left->data + nod->right->data;
		return nod;
	}
	void search(node* nod, char a,int index)
	{
		ofstream out;
		out.open("encoding.txt",ios_base::app);
		if (index != 0)
		{
			out << nod->code;
		}
		if (nod->left->element == a)
		{
			out << nod->left->code;
			out.close();
			return;
		}
		if (nod->right != nullptr && nod->right->right == nullptr)
		{
			out << nod->right->code;
			out.close();
			return;
		}
		out.close();
		this->search(nod->right, a, index + 1);
	}
	void bubblesort(char* arr, int* fre, int n)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n - i-1; j++)
			{
				if (fre[j] < fre[j + 1])
				{
					int temp = fre[j];
					fre[j] = fre[j + 1];
					fre[j + 1] = temp;
					char a = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = a;
				}
			}
		}
		int temp = fre[n-2];
		fre[n-2] = fre[n-1];
		fre[n-1] = temp;
		char a = arr[n-2];
		arr[n-2] = arr[n-1];
		arr[n-1] = a;
	}
	int code(int index)
	{
		int a = 0, b = 1;
		for (int i = 0; i < index; i++)
		{
			b = b * 10;
			a = a + b;
		}
		return a;
	}
	void inorder(node* t)
	{
		if (t)
		{
			inorder(t->left);
			inorder(t->right);
			cout << t->element << " " << t->data << " " << t->code << endl;
		}
	}
};
int main()
{
	BT a;
	a.encoding();
	a.decoding();
	cout << endl << endl << endl << endl;
	return 0;
}