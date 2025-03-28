#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<class T>
class Stack {
private:
	class Node {
	public:
		T data;
		Node* next;
		Node* top;
		Node() {
			next = NULL;
			top = NULL;
		}
	};
	Node* head;
	Node* tail;
	int size;
public:
	Stack() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	~Stack() {
		Node* temp;
		while (head != nullptr) {
			temp = head->next;
			delete head;
			head = temp;
		}
	}

	bool IsEmpty() {
		return size == 0;
	}
	bool push(T val) {
		Node* temp = new Node;
		temp->data = val;
		if (head == nullptr) {
			head = temp;
			tail = temp;
		}
		else {
			temp->next = head;
			head = temp;
		}
		size++;
		return true;
	}
	T pop() {
		if (head != nullptr) {
			T tempdata = head->data;
			Node* temp = head->next;
			delete head;
			head = temp;
			size--;
			return tempdata;
		}
	}
	T top() {
		if (head != nullptr)
			return head->data;
	}
	int getSize() {
		return size;
	}
};

int Find(string s1, string s2) {
	int si1 = s1.size();
	int si2 = s2.size();
	int i = 0;
	bool found;
	for (i = 0; i < si1; i++) {
		found = true;
		for (int j = 0; j < si2; j++)
		{
			if (s1[i + j] != s2[j]) {
				found = false;
				break;
			}
		}
		if (found) {
			return i;
		}
	}
	return -1;
}

string getSubstring(string str, int startIndex, int endIndex) {
	if (startIndex >= str.size() || startIndex > endIndex || endIndex >= str.size()) {
		return "";
	}

	int substringLength = endIndex - startIndex + 1;
	string result(substringLength, ' '); // Initialize a string with the required length

	for (int i = 0; i < substringLength; i++) {
		result[i] = str[startIndex + i];
	}

	return result;
}


class XMLData : public Stack<char> {
	Stack s1;
public:
	void commentscheck(string d, int& lno) {
		s1.push(d[0]);
		s1.push(d[1]);
		s1.push(d[2]);
		for (int i = 3; i < d.size(); i++)
		{
			if (d[i] == '<' || d[i] == '-' || d[i] == '>') {
				s1.push(d[i]);
			}
			if (d[i] == '>') break;
		}
		if (s1.top() != '>') {
			cout << "Error on the line number " << lno << " due to >" << endl;
		}
		else s1.pop();
		int count = 0;
		while (1) {
			if (s1.pop() == '-') count++;
			if (s1.top() == '<') break;
		}
		if (count != 4)
		{
			cout << "Error on line number " << lno << " due to - " << endl;
		}
		lno++;
		while (!s1.IsEmpty()) {
			s1.pop();
		}
	}
	void Check() {
		bool error = false;
		string data;
		ifstream fin;
		int linenumber = 1;
		int ExcCount = 0;
		int questionCount = 0;
		bool backslash = false;
		int commas = 0;
		bool validInput = false;
		bool startInput = false;
		fin.open("q1.xml");
		while (!fin.eof()) {
			backslash = false;
			questionCount = 0;
			ExcCount = 0;
			commas = 0;
			getline(fin, data, '\n');
			if (data[0] == '<' && data[1] == '!') {
				commentscheck(data, linenumber);
				continue;
			}
			for (int i = 0; i < data.size(); i++)
			{
				if (data[i] == '<' || data[i] == '?' || data[i] == '/' || data[i] == '"' || data[i] == '!') {
					if (data[i] == '<') {
						validInput = true;
						startInput = true;
					}
					else if (startInput != true)
					{
						cout << "Error at start of line " << linenumber << " due to " << data[i] << endl;
						s1.pop();
						error = true;
						continue;
					}
					if (validInput == true) {
						s1.push(data[i]);
					}
					if (data[i] == '?') {
						questionCount++;
						s1.pop();
					}
					if (questionCount > 2 || (questionCount > 0 && linenumber != 1)) {
						cout << "Error at line " << linenumber << " due to ? " << endl;
						questionCount--;
						error = true;
						continue;
					}

					if (data[i] == '!') {
						ExcCount++;
					}
					if (data[i] == '/')
					{
						if (backslash == true) {
							cout << "Error at the line " << linenumber << " due to " << data[i] << endl;
							error = true;
							s1.pop();
						}
						if (data[i - 1] != '<' && data[i + 1] != '>')
						{
							error = true;
							cout << "Error on the line " << linenumber << " caused by " << data[i] << endl;
							s1.pop();
						}
						else s1.pop();
						backslash = true;
					}
					if (data[i] == '"')
					{
						commas++;
						if (commas == 1 && data[i - 1] != '=')
						{
							error = true;
							cout << "Error at line " << linenumber << " due to " << data[i] << endl;
							commas--;
							s1.pop();
							continue;
						}
					}

					if (data[i] == '"' && s1.top() != '"') {
						if (commas > 1) {
							error = true;
							cout << "Error on the line number " << linenumber << "cause by mismatch of " << data[i] << endl;
							s1.pop();
							continue;
						}
					}
					else if (data[i] == '"' && s1.top() == '"' && commas > 1)
					{
						s1.pop();
						s1.pop();
						commas = 0;
						continue;
					}
					if (data[i] == '!' && s1.top() == '!' && ExcCount > 2) {
						cout << "Error on the line number " << linenumber << "cause by mismatch of " << data[i] << endl;
						s1.pop();
						error = true;
						continue;
					}
					else if (data[i] == '!' && s1.top() == '!' && ExcCount > 1)
					{
						s1.pop();
						s1.pop();
						continue;
					}
				}
				else if (data[i] == '>') {
					if (data[i - 1] == '?' && linenumber == 1) {
						if (s1.top() == '?') s1.pop();
					}
					if (validInput == true) {
						if (s1.top() != '<') {
							error = true;
							cout << "Error on line number " << linenumber << endl;
						}
						s1.pop();
						validInput = false;
					}
				}
			}
			if (!s1.IsEmpty())
			{
				for (int i = 0; i < s1.getSize(); i++)
				{
					error = true;
					cout << "Error on the line number " << linenumber << " cause by mismatch of " << s1.pop() << endl;
				}
			}
			linenumber++;
		}
		fin.close();
		fin.open("q1.xml");
		Stack<string> s2;
		getline(fin, data, '\n');
		linenumber = 2;
		while (!fin.eof()) {
			bool checkTag = false;
			getline(fin, data, '\n');
			if (data[1] != '!') {
				int startIndex;
				int endIndex;
				string substring;
				if (data[1] != '/') {
					startIndex = Find(data, "<");
					endIndex = Find(data, ">");
					if (startIndex == -1) {
						error = true;
						cout << "Starting tag not found at line number " << linenumber << endl;
						linenumber++;
						continue;
					}
					if (endIndex == -1)
					{
						error = true;
						cout << "Ending tag not found at line number " << linenumber << endl;
						linenumber++;
						continue;
					}
					substring = getSubstring(data, startIndex + 1, endIndex - 1);
					s2.push(substring);
				}

				startIndex = Find(data, "</");
				if (startIndex != -1) {
					endIndex = data.size();
					substring = getSubstring(data, startIndex + 2, endIndex - 2);
					if (s2.top() != substring) {
						cout << "Tag mismatch error on line " << linenumber << "due to tag " << substring << endl;
						error = true;
						linenumber++;
						continue;
					}
					else if (s2.top() == substring) {
						s2.pop();
						linenumber++;
						continue;
					}
				}

			}
			linenumber++;
		}
		while (!s2.IsEmpty())
		{
			error = true;
			cout << "Error on line number " << linenumber++ << " due to missing tag " << s2.pop() << endl;
		}
		if (error == false)
		{
			cout << "No error found " << endl;
		}
	}

};

int main() {
	XMLData d1;
	d1.Check();
}