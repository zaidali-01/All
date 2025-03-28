#include<iostream>
#include"wavfile.h"
using namespace std;
void allocateArray(unsigned char*& arr, int size)
{
	arr = new unsigned char[size];
}
void deallocateArray(unsigned char*& arr)
{
	delete[] arr;
	arr = NULL;
}
void print(unsigned char*& arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i];
	}
	cout << endl;
}
unsigned char* doublearray(unsigned char* arr, int size)
{
	unsigned char* doublearr;
	allocateArray(doublearr, size * 2 - 1);
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		doublearr[count] = arr[i];
		count++;
		doublearr[count] = arr[i];
		count++;
	}
	return doublearr;
}
unsigned char* shrinkarray(unsigned char*& arr, int& size)
{
	if (size % 2 == 0)
		size = size / 2;
	else
		size = (size / 2) + 1;
	unsigned char* shrinkarr;
	allocateArray(shrinkarr, size + 1);
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		shrinkarr[i] = arr[count];
		count = count + 2;
	}
	return shrinkarr;
}
void fillmean(unsigned char*& arrin, unsigned char*& arrout, int size, int N)

{
	allocateArray(arrout, size + 1);
	for (int i = 0; i < size; i++)
	{
		int temp = 0, sum = 0;
		for (int j = i - N; j < N + i + 1; j++)
		{
			if (j >= 0 && j < size)
			{
				temp++;
				sum = sum + arrin[j];
			}
		}
		arrout[i] = sum / temp;
	}
}
void play(char pt[])
{
	playWavFile(pt);
}
void upsample()
{
	unsigned char* ptr, * arr;
	char str[50], t[50], pt[50];
	cout << "Enter file name: ";
	cin >> str;
	int size = 100000000, samplerate = 0;
	allocateArray(ptr, size);
	readWavFile(str, ptr, size, samplerate);
	arr = doublearray(ptr, size);
	cout << "Enter name for upsample wave: ";
	cin >> pt;
	writeWavFile(pt, arr, size * 2, samplerate);
	cout << "would u like to play up sampled file? ";
	cin >> t;
	if (!strcmp(t, "yes"))
		play(pt);
	delete[] arr;
	arr = NULL;
	delete[] ptr;
	ptr = NULL;
}
void downsample()
{
	unsigned char* ptr, * arr;
	char str[50], t[50], pt[50];
	cout << "Enter file name: ";
	cin >> str;
	int size = 10000000, samplerate = 0;

	allocateArray(ptr, size);
	readWavFile(str, ptr, size, samplerate);
	arr = shrinkarray(ptr, size);
	cout << "Enter name for downsample wave: ";
	cin >> pt;
	writeWavFile(pt, arr, size / 2, samplerate);
	cout << "would u like to play down sampled file? ";
	cin >> t;
	if (!strcmp(t, "yes"))
		play(pt);
	delete[] arr;
	arr = NULL;
	delete[] ptr;
	ptr = NULL;
}
void movingaverage()
{
	unsigned char* ptr, * arr;
	char str[50], t[50], pt[50];
	cout << "Enter file name: ";
	cin >> str;
	int size = 100000000, samplerate = 0, N;
	allocateArray(ptr, size);

	cout << "Enter moving value: ";
	cin >> N;
	readWavFile(str, ptr, size, samplerate);
	fillmean(ptr, arr, size, N);
	cout << "Enter name for mean wave: ";
	cin >> pt;
	writeWavFile(pt, arr, size, samplerate);
	cout << "would u like to play moving average file? ";
	cin >> t;
	if (!strcmp(t, "yes"))
		play(pt);
	delete[] arr;
	arr = NULL;
	delete[] ptr;
	ptr = NULL;
}
void mix()
{
	unsigned char* ptr, * arr, * mix;
	char str[15], spr[15], t[5], pt[15], pr[15];
	int size1 = 100000000, size2 = 100000000, samplerate1 = 0, samplerate2 = 0;
	cout << "Enter first file name: ";
	cin >> str;
	allocateArray(ptr, size1);
	allocateArray(arr, size2);
	cout << "enter second file name: ";

	cin >> spr;

	readWavFile(str, ptr, size1, samplerate1);
	readWavFile(spr, arr, size2, samplerate2);
	allocateArray(mix, size1 + size2 + 1);
	int i = 0, j = 0, count = 0;
	while (i < size1 && j < size2)
	{
		mix[count] = ptr[i];
		count++;
		i++;
		mix[count] = arr[j];
		count++;
		j++;
	}
	while (i < size1)
	{
		mix[count] = ptr[i];
		count++;
		i++;
	}
	while (j < size2)
	{
		mix[count] = arr[j];
		count++;
		j++;
	}
	cout << "Enter name for first wave: ";
	cin >> pt;
	cout << "Enter name for second wave: ";
	cin >> pr;
	writeWavFile(pt, mix, size1 + size2, samplerate1);
	writeWavFile(pr, mix, size1 + size2, samplerate2);
	cout << "would u like to play mix file? ";
	cin.getline(t, 5);
	cin.ignore();
	if (!strcmp(t, "yes"))
	{
		play(pt);
		play(pr);
	}
	deallocateArray(arr);
	deallocateArray(ptr);
	deallocateArray(mix);
}
int main()
{
	int a;
	cout << "MENU:\n";
	cout << "1.upsample\n";
	cout << "2.downsample\n";
	cout << "3.movingaverage\n";
	cout << "4.mixing audio\n";
	cout << "5.play audio\n";
	cout << endl << "enter your command: ";
	cin >> a;
	if (a == 1)
		upsample();
	if (a == 2)
		downsample();
	if (a == 3)
		movingaverage();
	if (a == 4)
		mix();
	if (a == 5)
	{
		char b[15];
		cout << "Enter file name: ";
		cin >> b;
		play(b);
	}
	cout << endl << "GOOD BYE" << endl;
	return 0;
}