#include<iostream>;
#include"ConsoleFunctions.h";
#include<fcntl.h>
#include<io.h>
using namespace std;
#include <string.h>
ConsoleFunctions::ConsoleFunctions()
{
	//mode = 0;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &original_mode);
	SetConsoleMode(hOut, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);// | ENABLE_PROCESSED_INPUT | ENABLE_EXTENDED_FLAGS ); //| ENABLE_QUICK_EDIT_MODE
	SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);// | ENABLE_EXTENDED_FLAGS | ENABLE_PROCESSED_INPUT);
	GetConsoleScreenBufferInfo(hOut, &csbi);
	original_attributes = csbi.wAttributes;
}

void ConsoleFunctions::setConsoleTitle(const char* title)
{
	int len = strlen(title);
	wchar_t* str = new wchar_t[len + 1];

	for (int i = 0; i < len; i++)
		str[i] = title[i];
	str[len] = '\0';

	SetConsoleTitle(LPCWSTR(str));
	//SetConsoleTitle(TEXT("some title"));
}

void ConsoleFunctions::SetCursorAt(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hOut, coord);
}

char ConsoleFunctions::ReadFrom(int x, int y)
{
	//char* str = new char[10];  //Buffer of 10 char size
	char str[10];
	DWORD nLength = 1;     //The number of chars to read, we need to read one character only!
	COORD readFromCoord;   //Co-ordinates from where to read
	readFromCoord.X = x;
	readFromCoord.Y = y;
	DWORD num_read = 0;      //Will be set to no. of charaters actually read

	ReadConsoleOutputCharacter(hOut, (LPTSTR)str, nLength, readFromCoord, (LPDWORD)&num_read);

	return str[0];
}

void ConsoleFunctions::DetectEvent()
{
	DWORD count = 0;
	GetNumberOfConsoleInputEvents(hIn, &count);
	if (count > 0)
	{
		DWORD nLength = 1;     //The number of records to read, we need to read one record only!
		DWORD num_read = 0;      //Will be set to no. of input records actually read
		ReadConsoleInput(hIn, &InRec, nLength, &num_read);
		FlushConsoleInputBuffer(hIn);
		//cout << "Num Read " << (int)num_read << " now";
	}
}

bool ConsoleFunctions::getMousePosition(point& p)
{
	//cout << InRec.EventType;
	//if(InRec.EventType == MOUSE_EVENT)
	//	cout<<InRec.Event.MouseEvent.dwEventFlags;

	if (InRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
	{
		p.x = InRec.Event.MouseEvent.dwMousePosition.X;
		p.y = InRec.Event.MouseEvent.dwMousePosition.Y;

		return true;
	}
	return false;

}

bool ConsoleFunctions::IsMouseLeftClickEvent(point& p)
{
	if (InRec.EventType == MOUSE_EVENT && InRec.Event.MouseEvent.dwEventFlags == 0 && InRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		p.x = InRec.Event.MouseEvent.dwMousePosition.X;
		p.y = InRec.Event.MouseEvent.dwMousePosition.Y;
		InRec.Event.MouseEvent.dwButtonState = 0;

		return true;
	}
	return false;
}

bool ConsoleFunctions::IsMouseRightClickEvent(point& p)
{
	if (InRec.EventType == MOUSE_EVENT && InRec.Event.MouseEvent.dwEventFlags == 0 && InRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
	{
		p.x = InRec.Event.MouseEvent.dwMousePosition.X;
		p.y = InRec.Event.MouseEvent.dwMousePosition.Y;
		InRec.Event.MouseEvent.dwButtonState = 0;
		return true;
	}
	return false;
}

bool ConsoleFunctions::IsKeyPressEvent(char& key)
{
	if (InRec.EventType == KEY_EVENT && InRec.Event.KeyEvent.bKeyDown)
	{
		//cout << (int)InRec.Event.KeyEvent.wRepeatCount;
		key = InRec.Event.KeyEvent.uChar.AsciiChar;
		InRec.EventType = 0;
		return true;
	}
	return false;
}



bool ConsoleFunctions::IsKeyReleaseEvent(char& key)
{
	if (InRec.EventType == KEY_EVENT && !InRec.Event.KeyEvent.bKeyDown)
	{

		key = InRec.Event.KeyEvent.uChar.AsciiChar;
		return true;
	}
	return false;
}

int ConsoleFunctions::getTextColor()
{
	GetConsoleScreenBufferInfo(hOut, &csbi);
	int a = csbi.wAttributes;
	return a % 16;
}

int ConsoleFunctions::getBackColor()
{
	GetConsoleScreenBufferInfo(hOut, &csbi);
	int a = csbi.wAttributes;
	return (a / 16) % 16;
}

void ConsoleFunctions::SetColor(ConsoleColor textcol, ConsoleColor backcol)
{
	SetColor(int(textcol), int(backcol));
}

void ConsoleFunctions::SetColor(int textcol, int backcol)
{
	bool textcolorprotect = true; //for future use
	/*doesn't let textcolor be the same as backgroung color if true*/
	if (textcolorprotect)
	{
		if ((textcol % 16) == (backcol % 16))textcol++;
	}
	textcol %= 16;
	backcol %= 16;
	unsigned short wAttributes = (unsigned)textcol | ((unsigned)backcol << 4);
	SetConsoleTextAttribute(hOut, wAttributes);

}

void ConsoleFunctions::getConsoleWindowSize(int& rows, int& columns)
{
	//CHECK
	GetConsoleScreenBufferInfo(hOut, &csbi);
	//columns = csbi.dwMaximumWindowSize.X;
	//columns = csbi.dwSize.X-1;
	//rows = csbi.dwSize.Y-1;
	columns = csbi.srWindow.Right;
	rows = csbi.srWindow.Bottom;
	//columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	//rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

}

void ConsoleFunctions::setConsoleWindowAndBufferSize(int rows, int columns)
{
	COORD new_size;
	new_size.Y = rows + 1;
	new_size.X = columns + 1;
	//SetConsoleActiveScreenBuffer(hOut);
	//SetConsoleScreenBufferSize(hOut, new_size);

	SMALL_RECT rect;  rect.Left = 0; rect.Top = 0; rect.Right = columns; rect.Bottom = rows;
	//SetConsoleScreenBufferSize(hOut, new_size);

	SetConsoleWindowInfo(hOut, true, &rect);
	SetConsoleScreenBufferSize(hOut, new_size);

}

void cls(HANDLE hConsole, WORD original_attributes)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	// Scroll the rectangle of the entire buffer.
	scrollRect.Left = 0;
	scrollRect.Top = 0;
	scrollRect.Right = csbi.dwSize.X;
	scrollRect.Bottom = csbi.dwSize.Y;

	// Scroll it upwards off the top of the buffer with a magnitude of the entire height.
	scrollTarget.X = 0;
	scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

	// Fill with empty spaces with the buffer's default text attribute.
	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes =
		fill.Attributes = original_attributes;

	// Do the scroll
	ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

	// Move the cursor to the top left corner too.
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}
void ConsoleFunctions::clearConsole()
{
	SetConsoleMode(hOut, original_mode);
	SetConsoleTextAttribute(hOut, original_attributes);
	cls(hOut, original_attributes);

}


void ConsoleFunctions::writeStringOnConsole(char* str)
{
	DWORD Written;
	int len = strlen(str);
	wchar_t* mystr = new wchar_t[len + 1];

	for (int i = 0; i < len; i++)
		mystr[i] = str[i];
	mystr[len] = '\0';
	WriteConsole(hOut, mystr, len, &Written, NULL);
}

void ConsoleFunctions::writeCharOnConsole(char c)
{
	DWORD Written;
	//int len = strlen(str);
	wchar_t* mystr = new wchar_t[1];
	mystr[0] = c;
	//mystr[len] = '\0';
	WriteConsole(hOut, mystr, 1, &Written, NULL);

}

ConsoleFunctions::~ConsoleFunctions()
{
	SetConsoleMode(hOut, original_mode);
	SetConsoleTextAttribute(hOut, original_attributes);
}



//Old Version, Ignore
//void ConsoleFunctions::clearConsole()
//{
//
//	
//	// Get the number of character cells in the current buffer. 
//
//	COORD coordScreen = { 0, 0 };    // home for the cursor 
//	DWORD cCharsWritten;
//	//CONSOLE_SCREEN_BUFFER_INFO csbi; 
//	DWORD dwConSize;
//
//	// Get the current text attribute.
//	if( !GetConsoleScreenBufferInfo( hOut, &csbi ))
//	{
//		return;
//	}
//	unsigned short wAttributes = csbi.wAttributes;  //saving text attributes
//
//
//	SetColor(black,black);
//	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;	 
//
//	// Fill the entire screen with blanks.
//
//	if( !FillConsoleOutputCharacter( hOut,        // Handle to console screen buffer 
//		(TCHAR) ' ',     // Character to write to the buffer
//		dwConSize,       // Number of cells to write 
//		coordScreen,     // Coordinates of first cell 
//		&cCharsWritten ))// Receive number of characters written
//	{
//		return;
//	}
//
//	// Get the current text attribute.
//	//if( !GetConsoleScreenBufferInfo( hOut, &csbi ))
//	//{
//	//	return;
//	//}
//
//
//	////// Set the buffer's attributes accordingly.
//
//	//if( !FillConsoleOutputAttribute( hOut,         // Handle to console screen buffer 
//	//	csbi.wAttributes, // Character attributes to use
//	//	dwConSize,        // Number of cells to set attribute 
//	//	coordScreen,      // Coordinates of first cell 
//	//	&cCharsWritten )) // Receive number of characters written
//	//{
//	//	return;
//	//}
//
//	// Put the cursor at its home coordinates.
//	SetConsoleTextAttribute(hOut,wAttributes);
//	SetConsoleCursorPosition( hOut, coordScreen );
//
//
//
//}
class playingcard
{
	int rank, suit;
	char color;
	wstring symbol;
	bool top, faceup;
public:
	static const int diamond;
	static const int heart;
	static const int spade;
	static const int clubs;
	playingcard(int r = 1, int s = 0) : top(true), faceup(true)
	{
		if (r >= 1 && r <= 13)
		{
			rank = r;
		}
		else
		{
			cout << "INVALID rank!!!";
			system("pause");
			exit(0);
		}
		if (s >= 0 && s <= 3)
		{
			suit = s;
			if (suit == 0)
			{
				color = 'r';
				symbol = L"\u2666";
			}
			else if (suit == 1)
			{
				color = 'r';
				symbol = L"\u2665";
			}
			else if (suit == 2)
			{
				color = 'b';
				symbol = L"\u2660";
			}
			else
			{
				color = 'b';
				symbol = L"\u2663";
			}
		}
		else
		{
			cout << "INVALID suit!!!";
			system("pause");
			exit(0);
		}
	}
	char getcolor()
	{
		return color;
	}
	int getrank()
	{
		return rank;
	}
	int getsuit()
	{
		return suit;
	}
	bool isfaceup()
	{
		return faceup;
	}
	void setfaceup(bool a)
	{
		faceup = a;
	}
	bool istop()
	{
		return top;
	}
	void settop(bool a)
	{
		top = a;
	}
	void display(int x, int y)
	{
		ConsoleFunctions d;
		if (faceup)
		{
			if (color == 'b')
				d.SetColor(0, 15);
			if (color == 'r')
				d.SetColor(4, 15);
		}
		else
		{
			d.SetColor(0, 12);
		}
		int c;
		if (top)
			c = 6;
		else
			c = 2;
		for (int i = 0; i < c; i++)
		{
			bool flag = false;
			if (i == 5 && rank == 10)
				flag = true;
			d.SetCursorAt(x, y + i);
			for (int j = 0; j < 8; j++)
			{
				if (flag)
				{
					flag = false;
					j++;
				}
				if (((i == 0 && j == 0) || (i == 5 && j == 7)) && faceup)
				{
					if (rank == 1)
						cout << "A";
					else if (rank == 11)
						cout << "J";
					else if (rank == 12)
						cout << "Q";
					else if (rank == 13)
						cout << "K";
					else
						cout << rank;
				}
				else if (((i == 0 && j == 1) || (i == 5 && j == 6)) && faceup)
				{
					_setmode(_fileno(stdout), _O_U8TEXT);
					wcout << symbol;
					_setmode(_fileno(stdout), _O_TEXT);
					if (rank == 10 && i == 0)
						j++;
				}
				else
				{
					if (top || i != 1)
					{
						cout << " ";
					}
					else
					{
						if (faceup)
						{
							d.SetColor(0, 15);
						}
						cout << "_";
					}
				}
			}
		}
		d.SetColor(15, 0);
	}
};
const int playingcard::diamond = 0;
const int playingcard::heart = 1;
const int playingcard::spade = 2;
const int playingcard::clubs = 3;
class pileofcards
{
	playingcard* pile;
	int top, size;
	point startpt, endpt;
public:
	pileofcards(int s)
	{
		startpt.x = 0;
		startpt.y = 0;
		endpt.x = 0;
		endpt.y = 0;
		size = s;
		top = -1;
		pile = new playingcard[size];
	}
	bool isempty()
	{
		if (top == -1)
			return true;
		return false;
	}
	bool isfull()
	{
		if (top == size - 1)
			return true;
		return false;
	}
	playingcard peek()
	{
		return pile[top];
	}
	void add(playingcard& p)
	{
		if (this->isfull())
		{
			cout << endl << "Card " << p.getrank() << " of ";
			if (p.getsuit() == 0)
				cout << "diamond";
			else if (p.getsuit() == 1)
				cout << "heart";
			else if (p.getsuit() == 2)
				cout << "spade";
			else
				cout << "club";
			cout << " cannot be added as the pile is full" << endl;
		}
		else
		{
			pile[++top] = p;
			pile[top].settop(true);
			if (top > 0)
			{
				pile[top - 1].settop(false);
			}
		}
	}
	playingcard remove()
	{
		playingcard temp;
		if (this->isempty())
		{

			cout << endl << "Card cannot be removed as pile is empty" << endl;
		}
		else
		{
			temp = pile[top--];
			if (top >= 0)
			{
				pile[top].settop(true);
			}
		}
		return temp;
	}
	int gettop()
	{
		return top;
	}
	void setstartpt(int x, int y)
	{
		startpt.x = x;
		startpt.y = y;
	}
	point getstartpt()
	{
		return startpt;
	}
	void setendpt(int x, int y)
	{
		endpt.x = x;
		endpt.y = y;
	}
	point getendpt(int x, int y)
	{
		return endpt;
	}
	pileofcards& operator = (const pileofcards& obj)
	{
		delete[] pile;
		size = obj.size;
		top = obj.top;
		startpt = obj.startpt;
		endpt = obj.endpt;
		pile = new playingcard[size];
		for (int i = 0; i <= top; i++)
		{
			pile[i] = obj.pile[i];
		}
	}
	playingcard viewcard(int i)
	{
		return pile[i];
	}
	void simpledisplay()
	{
		if (this->isempty())
		{
			ConsoleFunctions d;
			d.SetColor(15, 2);
			for (int i = 0; i < 6; i++)
			{
				d.SetCursorAt(startpt.x, startpt.y + i);
				for (int j = 0; j < 8; j++)
				{
					cout << " ";
				}
			}
			d.SetColor(15, 0);
		}
		else
		{
			pile[top].display(startpt.x, startpt.y);
		}
	}
	void cascadingdisplay()
	{
		if (this->isempty())
		{
			ConsoleFunctions d;
			d.SetColor(15, 2);
			for (int i = 0; i < 6; i++)
			{
				d.SetCursorAt(startpt.x, startpt.y + i);
				for (int j = 0; j < 8; j++)
				{
					cout << " ";
				}
			}
			d.SetColor(15, 0);
		}
		else
		{
			int a = 0;
			for (int i = 0; i <= top; i++)
			{
				pile[i].display(startpt.x, startpt.y + a);
				a += 2;
			}
		}
	}
	~pileofcards()
	{
		delete[] pile;
		pile = nullptr;
	}
};
class Deck
{
	playingcard* deck[52];
	int size;
public:
	Deck()
	{
		size = 52;
		int j = 0;
		for (int i = 0; i < 13; i++)
		{
			deck[j] = new playingcard(i + 1, playingcard::diamond);
			j++;
		}
		for (int i = 0; i < 13; i++)
		{
			deck[j] = new playingcard(i + 1, playingcard::heart);
			j++;
		}
		for (int i = 0; i < 13; i++)
		{
			deck[j] = new playingcard(i + 1, playingcard::spade);
			j++;
		}
		for (int i = 0; i < 13; i++)
		{
			deck[j] = new playingcard(i + 1, playingcard::clubs);
			j++;
		}
	}
	int getsize()
	{
		return size;
	}
	bool isempty()
	{
		if (size == 0)
			return true;
		return false;
	}
	playingcard remove(int i)
	{
		playingcard temp;

		/*for (int k = 0; k < size; k++)
		{
			if (k == i)
			{
				temp = *deck[k];
				for (int j = k; j < size; j++)
				{
					if (j == k)
					{
						delete deck[j];
					}
					if (j != size - 1)
					{
						deck[j] = deck[j + 1];
					}
					else
					{
						deck[j] = nullptr;
					}
				}
			}
		}*/
		if (this->isempty())
		{
			cout << "Deck is already empty so cannot remove a card";
		}
		else if (i >= size)
		{
			cout << "There are only " << size << " cards so cannot remove the " << i + 1 << "th card";
		}
		else
		{
			temp = *deck[i];
			delete deck[i];
			for (int j = i; j < size; j++)
			{
				if (j != size - 1)
				{
					deck[j] = deck[j + 1];
				}
				else
				{
					deck[j] = nullptr;
				}
			}
			size--;
		}
		return temp;
	}
	~Deck()
	{
		for (int i = 0; i < 52; i++)
		{
			delete deck[i];
		}
	}
};
class solitaire
{
	Deck deckofcards;
	pileofcards stock, waste, home[4], playingpile[7];
	ConsoleFunctions cf;
public:
	solitaire() : stock(52), waste(52), home{ 13,13,13,13 }, playingpile{ 14,15,16,17,18,19,20 }
	{
		int x1 = 1, x2 = 8;
		stock.setstartpt(x1, 1);
		x1 += 10;
		stock.setendpt(x2, 6);
		x2 += 10;
		waste.setstartpt(x1, 1);
		x1 += 10;
		waste.setendpt(x2, 6);
		x2 += 10;
		for (int i = 0; i < 4; i++)
		{
			x1 += 10;
			x2 += 10;
			home[i].setstartpt(x1, 1);
			home[i].setendpt(x2, 6);
		}
		x1 = 1;
		x2 = 6;
		int y2 = 17;
		for (int i = 0; i < 7; i++)
		{
			playingpile[i].setstartpt(x1, 12);
			playingpile[i].setendpt(x2, y2);
			x1 += 10;
			x2 += 10;
			y2 += 2;
		}
	}
	void shuffle()
	{
		int i;
		while (!deckofcards.isempty())
		{
			i = rand() % deckofcards.getsize();
			playingcard c = deckofcards.remove(i);
			c.setfaceup(false);
			stock.add(c);
		}
	}
	void dealtoplayingpiles()
	{
		for (int i = 0; i < 7; i++)
		{
			playingcard temp;
			for (int j = 0; j <= i; j++)
			{
				temp = stock.remove();
				if (j == i)
					temp.setfaceup(true);
				playingpile[i].add(temp);
			}
		}
	}
	void displaygame()
	{
		stock.simpledisplay();
		waste.simpledisplay();
		for (int i = 0; i < 7; i++)
		{
			if (i < 4)
			{
				home[i].simpledisplay();
			}
			playingpile[i].cascadingdisplay();
		}
	}
};
int main()
{
	while (1)
	{
		solitaire a;
		a.shuffle();
		a.dealtoplayingpiles();
		a.displaygame();
		system("pause");
	}
	return 0;
}