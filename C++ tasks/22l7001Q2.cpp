#include<iostream>
#include<assert.h>
#include<string>
#include<fstream>
#include<List>
using namespace std;


class gItem
{
public:
	int id; //current vertex
	int a; //adj vertex 
	int w; //weight on edge bw the two
	string location;
	int idx;

	gItem()
	{
		id = 0;
		a = 0;
		w = 0;
		location = "a";
		idx = 0;
	}

	friend ostream& operator<<(ostream& out, gItem g)
	{
		out << "curr_vertex id: " << g.id << endl;
		out << "location: " << g.location << endl;
		out << "adj_vertex: " << g.a << endl;
		out << "weight: " << g.w << endl;
		out << "idx: " << g.idx << endl;
		out << endl;
		return out;
	}

	bool operator==(gItem g)
	{
		if (idx == g.idx && id == g.id && g.a == a && g.w == w)
			return true;
		return false;
	}

	gItem& operator=(const gItem g)
	{
		id = g.id;
		location = g.location;
		a = g.a;
		w = g.w;
		idx = g.idx;

		return *this;
	}
};


template <typename k, typename v>
struct Item
{
	k key;
	v value;
};

template<typename k, typename v>
class Minheap
{
	Item <int, gItem>* arr;
	int cap;
	int total;
	friend class Graph;

public:
	Minheap()
	{
		arr = nullptr;
		cap = 0;
		total = 0;
	}

	Minheap(int capacity)
	{
		total = 0;
		cap = capacity;
		arr = new Item<int, gItem>[cap];
	}

	void setcap(int vcap)
	{
		Item <int, gItem>* temp = arr;

		cap = vcap;
		arr = new Item<int, gItem>[cap];

		delete[] temp;

	}

	void heapDown(int root, int bottom)
	{
		int maxChild, rightChild, leftChild;
		leftChild = 2 * root + 1;
		rightChild = 2 * root + 2;
		if (leftChild <= bottom) // left child is part of the heap
		{
			if (leftChild == bottom) // only one child

				maxChild = leftChild;

			else
			{

				if (arr[leftChild].key > arr[rightChild].key)

					maxChild = rightChild;

				else

					maxChild = leftChild;

			}
			if (arr[root].key > arr[maxChild].key)
			{
				swap(arr[root], arr[maxChild]);
				heapDown(maxChild, bottom);

			}
		}
	}

	void heapUp(int root, int bottom)
	{
		int parent;
		if (bottom > root)
		{
			parent = (bottom - 1) / 2;
			if (arr[parent].key > arr[bottom].key)
			{
				swap(arr[parent], arr[bottom]);
				heapUp(root, parent);
			}
		}
	}

	void Buildheap()
	{
		for (int i = total - 1; i >= 0; i--)
			heapUp(0, i);
	}


	void insert(int data, gItem val)
	{

		if (total == cap)
		{
			Item<int, gItem>* temp;
			temp = new Item<int, gItem>[cap * 2];
			for (int i = 0; i < cap; i++)
			{
				temp[i] = arr[i];
			}
			delete[] arr;
			arr = nullptr;
			arr = temp;
			cap = cap * 2;
		}

		arr[total].value = val;
		arr[total].key = data;
		heapUp(0, total);

		total++;
	}

	void print()
	{
		for (int i = 0; i < total; i++)
		{
			cout << "key: " << arr[i].key << endl;
			cout << arr[i].value;

		}
		cout << endl << endl << endl;
	}

	void getmin(gItem& val)
	{
		assert(total > 0);
		val = arr[0].value;
	}

	void deletemin()
	{
		if (total > 0)
		{
			arr[0] = arr[total - 1];
			total--;

			//assert(total > 0);
			if (total > 0)
				heapDown(0, total);
		}
	}

	bool isEmpty()
	{
		if (total == 0)
			return true;
		return false;
	}

	bool getitem(int ID, gItem& g)
	{
		if (!isEmpty())
		{
			for (int i = 0; i < total; i++)
			{
				if (arr[i].value.id == ID)
				{
					g = arr[i].value;
					return true;
				}
			}
		}
		return false;
	}

	void decreaseKey(int index, int newkey, int* weights, int parent_id, int* parent)
	{
		if (!isEmpty())
		{
			for (int i = 0; i < total; i++)
			{
				if (arr[i].value.idx == index && arr[i].key > newkey) //only update key if newkey is smaller than existing
				{
					arr[i].key = newkey;
					arr[i].value.w = newkey; //newkey = weight of edge
					weights[index] = newkey;
					parent[index] = parent_id;
					Buildheap(); //minheap properties violated so rebuild heap

				}
			}
		}

	}

	~Minheap()
	{
		if (arr != nullptr)
		{
			delete[] arr;
			arr = nullptr;
		}
	}


};
class Graph
{
	int v;				 //no of vertices in graph
	list<gItem>* adj;
	bool* visited;

public:

	Graph(int n)
	{
		v = n;
		adj = new list<gItem>[v];
		visited = new bool[v];
		for (int i = 0; i < v; i++)
		{
			visited[i] = false;
		}
	}

	void setv(int n)
	{
		delete[] adj;
		adj = nullptr;

		v = n;
		adj = new list<gItem>[v];
		visited = new bool[v];
		for (int i = 0; i < v; i++)
		{
			visited[i] = false;
		}
	}

	void TakeInput(int n, gItem it)
	{
		adj[n].push_back(it);
	}

	void display()
	{
		//cout << "vertices: " << v << endl;
		for (int j = 0; j < v; j++)
		{
			cout << "LIST: " << j << endl;
			for (auto it = adj[j].cbegin(); it != adj[j].cend(); it++)
				cout << (*it);
			cout << endl << endl;
		}
	}

	int getv()
	{
		return v;
	}

	gItem getvertex(int i)
	{
		gItem x;
		if (adj[i].empty() == false)
			return adj[i].front();
		else
			return x;
	}

	list<gItem> getadjvertices(int i)
	{
		return adj[i];
	}

	int totaledges()
	{
		int sum = 0;
		for (int j = 0; j < v; j++)
		{
			for (auto it = adj[j].cbegin(); it != adj[j].cend(); it++)
				sum++;

		}
		return sum / 2;
	}

	bool addedge(int id1, int id2, int weight, Minheap<int, gItem>* heap)
	{
		bool flag1 = false;
		bool flag2 = false;
		gItem v1;
		gItem v2;

		//finding vertex from heap cz in case when new vertex is added without edge,  then that vertex cant be found in graph adj list since it only contains edges info
		if (heap->getitem(id1, v1) == true)
		{
			flag1 = true;
		}
		if (heap->getitem(id2, v2) == true)
		{
			flag2 = true;
		}

		if (flag1 == true && flag2 == true) //if both ids found 
		{
			for (int i = 0; i < v; i++)
			{
				for (auto it = adj[i].cbegin(); it != adj[i].cend(); it++)
				{
					if ((*it).id == id1 && (*it).a == id2) //edge already exists if id1 ka adj = id2
					{
						return false;
					}
				}
			}
			v2.w = weight;
			v2.a = v1.id;
			v1.w = weight;
			v1.a = v2.id;

			TakeInput(v1.idx, v1);
			TakeInput(v2.idx, v2);

			return true;
		}
		return false;
	}

	void addvertex(int id, string location)
	{
		list<gItem>* temp = adj;
		adj = new list<gItem>[v + 1];
		gItem vertex;
		vertex.id = id;
		vertex.location = location;
		vertex.idx = temp[v - 1].front().idx + 1;

		for (int j = 0; j < v; j++)
		{
			for (auto it = temp[j].cbegin(); it != temp[j].cend(); it++)
				TakeInput(j, (*it));
		}
		TakeInput(v, vertex);
		v++;

		delete[] temp;
		temp = nullptr;
	}

	int* spanningTree(Minheap<int, gItem>* h, int* parent)
	{
		gItem temp;
		int* weights = new int[v];
		for (int i = 0; i < v; i++)
		{
			weights[i] = -1;
			parent[i] = -1;
		}

		h->decreaseKey(0, 0, weights, -1, parent); //starting the path at 0th index
		//h->print();

		while (!h->isEmpty())
		{
			h->getmin(temp); //temp = min element from heap
			h->deletemin();
			visited[temp.idx] = true;

			for (auto it = adj[temp.idx].cbegin(); it != adj[temp.idx].cend(); it++)
			{
				gItem adj_vertex;
				h->getitem((*it).a, adj_vertex); //to find index of each vertex adjacent to temp

				if (visited[adj_vertex.idx] == false)
				{
					h->decreaseKey(adj_vertex.idx, (*it).w, weights, temp.id, parent); //update weights/keys in heap at all adjacent vertices & updates weights & parent arrays accordiingly
				}
			}
			//h->print();
		}
		return weights;
	}

	friend Minheap<int, gItem>* InFromFile(string filename, Graph& g);
	friend void SaveToFile(string filename, Graph g);

};

Minheap<int, gItem>* InFromFile(string filename, Graph& g)
{
	ifstream fin(filename);

	int cap;
	fin >> cap;
	Minheap<int, gItem>* heap = new Minheap<int, gItem>;
	heap->setcap(cap); //heap built of size = no' of vertices
	gItem c;
	char comma;

	for (int i = 0; i < cap; i++)
	{
		fin >> c.id;
		fin >> comma;
		fin >> c.location;
		c.idx = i;

		heap->insert(INT_MAX, c);
	}

	int edges;
	fin >> edges;
	gItem d;

	g.setv(cap);

	for (int j = 0; j < edges && !fin.eof(); j++)
	{
		fin >> d.id; //vertex id
		fin >> comma;
		heap->getitem(d.id, d); //to get location and idx
		fin >> d.a; //adj
		fin >> d.w; //weight

		g.TakeInput(d.idx, d);

		gItem e;
		heap->getitem(d.a, e);
		e.w = d.w;
		e.a = d.id;
		g.TakeInput(e.idx, e);
	}
	return heap;

}

void SaveToFile(string filename, Graph g)
{
	ofstream fout(filename);

	fout << g.getv() << endl;

	gItem vertex;
	for (int i = 0; i < g.getv(); i++)
	{
		vertex = g.getvertex(i);
		fout << vertex.id << ", " << vertex.location << endl;
	}
	fout << g.totaledges() << endl;

	list<gItem> l1;
	for (int i = 0; i < g.getv(); i++)
	{
		l1 = g.getadjvertices(i);
		for (auto it = l1.cbegin(); it != l1.cend(); it++)
		{
			if ((*it).a > (*it).id)
			{
				fout << (*it).id << "," << (*it).a << " " << (*it).w << endl;
			}
		}
	}
	fout.close();
}


int main()
{
	Graph graph(3);
	Minheap<int, gItem>* heap = new Minheap<int, gItem>;
	heap = InFromFile("graph.txt", graph);

	bool over = false;
	while (over == false)
	{
		int num;
		//heap->print();
		cout << endl << endl << "Enter number of task you want to perform: \n";
		cout << " 1).Input graph from file" << endl;
		cout << " 2).Save graph in file" << endl;
		cout << " 3).Add vertex in existing graph" << endl;
		cout << " 4).Add edge in existing graph" << endl;
		cout << " 5).Print edges of graph converted to spanning tree" << endl;
		cout << " 6).End Program" << endl << endl << endl;;

		cin >> num;
		//system("cls");

		if (num == 1)
		{
			heap = InFromFile("graph.txt", graph);
			graph.display();
		}
		else if (num == 2)
		{
			SaveToFile("g_out.txt", graph);
			cout << "Graph saved in file" << endl;
		}
		else if (num == 3)
		{
			string loc;
			int id;
			cout << "Enter ID: ";
			cin >> id;
			cout << "Enter location: ";
			cin >> loc;

			graph.addvertex(id, loc);
			SaveToFile("g_out.txt", graph);
			heap = InFromFile("g_out.txt", graph);

			cout << " VERTEX ADDED!\n";
			graph.display();
			//heap->print();
		}
		else if (num == 4)
		{
			int id1, id2, w;
			cout << "Enter ID of starting vertex: ";
			cin >> id1;
			cout << "Enter ID of ending vertex: ";
			cin >> id2;
			cout << "Enter weight of edge: ";
			cin >> w;

			bool flag = graph.addedge(id1, id2, w, heap);
			SaveToFile("g_out.txt", graph);
			heap = InFromFile("g_out.txt", graph);

			if (flag == true)
			{
				cout << "EDGE ADDED!\n";
				graph.display();
			}
			else
				cout << "INVALID ID!\n";
		}
		else if (num == 5)
		{
			int v = graph.getv();
			int* weights = new int[v];
			int* parent = new int[v];

			weights = graph.spanningTree(heap, parent);
			cout << endl << endl << "Edges after spanning: " << endl;
			for (int i = 0; i < v; i++)
			{
				if (parent[i] != -1)
					cout << "(" << parent[i] << ")" << "----" << weights[i] << "----" << "(" << graph.getvertex(i).id << ")" << endl;
			}
			cout << endl << endl;
		}
		else if (num == 6)
			over = true;
		else
		{
			cout << "INVALID NUMBER ENTERED!\n";
		}
	}

	return 0;
}