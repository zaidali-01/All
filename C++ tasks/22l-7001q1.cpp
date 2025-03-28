#include<SFML/Graphics.hpp>
#include<iostream>
#include <cmath>
using namespace std;
class queue
{
	int* arr;
	int maxsize;
	int front;
	int rear;
	int size;
public:
	queue(int s = 10)
	{
		maxsize = s;
		arr = new int[maxsize];
		size = 0;
		front = 0;
		rear = 0;
	}
	bool isfull()
	{
		if (size == maxsize)
			return true;
		return false;
	}
	bool isempty()
	{
		if (size == 0)
			return true;
		return false;
	}
	int getsize()
	{
		return size;
	}
	bool enqueue(int a)
	{
		if (this->isfull())
			return false;
		else
		{
			arr[rear] = a;
			size++;
			rear = (rear + 1) % maxsize;
			return true;
		}
	}
	bool dequeue(int& a)
	{
		if (this->isempty())
			return false;
		else
		{
			a = arr[front];
			front = (front + 1) % maxsize;
			size--;
			return true;
		}
	}
	void circle(int k)
	{
		int a;
		for (int i = 0; i < k; i++)
		{
			bool flag;
			flag = this->dequeue(a);
			if (i != k - 1 && flag)
				flag = this->enqueue(a);
		}
	}
	~queue()
	{
		delete[] arr;
	}
};
int main()
{
	int k, n;
	cout << "Enter size: ";
	cin >> n;

	queue q1(n);

	for (int i = 0; i < n; i++) 
	{
		int a;
		cout << "Enter element: ";
		cin >> a;
		q1.enqueue(a);
	}

	cout << "Enter the value of k: ";
	cin >> k;

	sf::RenderWindow window(sf::VideoMode(1440, 1080), "Queue Visualization");
	sf::Texture ptexture;
	if (!ptexture.loadFromFile("image1.jpg")) {
		cerr << "Image file not found!" << endl;
		return -1;
	}

	sf::Sprite playerimage;
	playerimage.setTexture(ptexture);

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		cerr << "Font file not found!" << endl;
		return -1;
	}

	int temp;
	float scaleFactor = 0.05;
	float radius = 200.0;
	float centerX = window.getSize().x / 2;
	float centerY = window.getSize().y / 2;
	float angle = 0.0;

	while (q1.getsize() > 0)
	{
		window.clear();
		for (int i = 0; i < q1.getsize(); i++)
		{
			q1.dequeue(temp);
			q1.enqueue(temp);

			float x = centerX + radius * cos(angle);
			float y = centerY + radius * sin(angle);

			playerimage.setScale(scaleFactor, scaleFactor);
			playerimage.setPosition(x, y);


			sf::Text numberText(to_string(temp), font, 20);
			numberText.setFillColor(sf::Color::White);
			numberText.setPosition(x - 10, y - 10);

			window.draw(playerimage);
			window.draw(numberText);

			angle += 2 * 3.14159265 / q1.getsize();
		}

		q1.circle(k);

		window.display();
		sf::sleep(sf::milliseconds(3000));

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}
	system("pause");
	return 0;
}