#include <iostream>
#include <Windows.h>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include "Stopwatch.h"

using namespace std;

//void callme1(StringBad &);
//void callme2(StringBad &);
bool cmpWord(char, string&, string&);
void shall(int a[], int n);
void quick(int arr[], int start, int end);
void mergeSort(int arr[], int size);
void merge(int arr[], int temp2[], int start, int size);

int main()
{
	/*
	StringBad bad1;
	{
		StringBad headline1("this is headline1 ");
		StringBad headline2("this is headline2 ");
		StringBad sports("this is sports ");

		cout << "headline1 : " << headline1 << endl;
		cout << "headline2 : " << headline2 << endl;
		cout << "sports : " << sports << endl;

		callme1(headline1);
		cout << "headline1 : " << headline1 << endl;
		callme2(headline2);
		cout << "headline2 : " << headline2 << endl;
		
		cout << "�ϳ��� ��ü�� �ٸ� ��ü�� �ʱ�ȭ : \n";
		
		StringBad sailor = sports;
		cout << "sailor : " << sailor << endl;
		
		cout << "�ϳ��� ��ü�� �ٸ� ��ü�� ����: \n";
		
		StringBad knot;
		knot = headline1;
		cout << "knot : " << knot << endl;
		cout << "�� ����� �������´�\n";
		
	}
	cout << "End of main" << endl;
	*/

	/*
	srand((unsigned int)time(NULL));
	
	vector<string> random = { "hospital", "apple" ,"string" , "random" , "whatthe" };

	int index = rand() % random.size();
	string answer = random[index];
	string nowAnswer;
	int miscount = 0;
	int okcount = 0;
	char charInput;


	for (int i = 0; i < answer.size(); i++)
	{
		nowAnswer.push_back('*');
	}
	while (true)
	{
		while (true) {
			cout << "�ܾ� �� �� ���ڸ� �Է��Ͻÿ� " << nowAnswer << " > ";
			cin >> charInput;
			if (charInput < 97 || charInput > 122)
			{
				cout << "���� �ҹ��ڷ� �Է����ּ���. " << endl;
			}
			else
			{
				break;
			}
		}

		if (cmpWord(charInput, answer, nowAnswer))
		{
			cout << charInput << "�� ǥ���մϴ�." << endl;
			okcount++;
		}
		else 
		{
			cout << "������ ���� �� " << charInput << "�� �������� �ʽ��ϴ�." << endl;
			okcount++;
			miscount++;
		}
			
		rewind(stdin);

		if (nowAnswer == answer)
		{
			cout << "-----------------------------" << endl;
			cout << nowAnswer << " ����!!" << endl;
			cout << "�� Ƚ�� : " << okcount << endl;
			cout << "Ʋ�� Ƚ�� : " << miscount << endl;
			cout << "-----------------------------" << endl;
			break;
		}
	}
	*/

	srand((unsigned int)time(NULL));
	const int size = 100000;
	int arr2[size];
	
	Stopwatch watch;

	for (int i = 0; i < size; i++)
	{
		arr2[i] = rand() % size;
	}

	// ���� �� ���
	/*
	cout << "���� ��" << endl;
	for (int i = 0; i < size; i++)
	{
	cout << arr2[i] << " ";
	}
	cout << endl;
	cout << endl;
	*/

	
	watch.start(); // ��ž��ġ ����

	// ���� �ڵ� start


	/*
	for(int i = size / 2; i > 0 ; i = i / 3 + 1)
	{
		for(int j = i; j < size ; j++)
		{
			int temp = arr2[j];
			int k;
			for (k = j; (k - i) >= 0 && arr2[k - i] > temp; k -= i)
			{
				arr2[k] = arr2[k - i];
			}
			arr2[k] = temp;
		}
		if (i == 1)
			break;
	}
	*/ //�� ����

	//shall(arr2, size);		// �� ��Ʈ
    //quick(arr2, 0, size-1);	// �� ��Ʈ
	mergeSort(arr2, size);		// ���� ��Ʈ

	/*
	for ()
	{
		int i = 0;
		int cursor = size - 1;

		while (arr2[cursor] >= arr2[i])
		{
			cursor--;
		}

		int temp = arr2[i];
		arr2[i] = arr2[cursor];
		arr2[cursor] = temp;
	}
	*/

	// ���� �ڵ� end


	watch.stop();  // ��ž��ġ ��

	// ���� �� ���
	/*
	cout << "���� ��" << endl;
	for (int i = 0; i < size; i++)
	{
	cout << arr2[i] << " ";
	}
	cout << endl;
	*/

	cout << "�ҿ�ð� : " << watch.getEleapsedTime() / 1000.0 << "��" << endl;

	return 0;
}

void merge(int arr[], int temp2[], int start, int size)
{
	//static int* temp2 = new int[size];

	if (size == 1)
		return;

	if (size % 2)
	{
		merge(arr, temp2, start, size / 2);
		merge(arr, temp2, start + size / 2, size / 2 + 1);
	}
	else
	{
		merge(arr, temp2, start, size / 2);
		merge(arr, temp2, start + size / 2, size / 2);
	}

	//cout << start << " " << size << endl;

	int front = start;
	int lear = start + size / 2;
	//int* temp = new int [size];
	int count = 0;

	while (1)
	{
		if ((arr[front] < arr[lear] || lear == (start + size)) && (front < (start + size / 2)))
		{
			//cout << arr[front] << " ";
			temp2[count++] = arr[front];
			front++;
		}
		else
		{
			//cout << arr[lear] << " ";
			temp2[count++] = arr[lear];
			lear++;
		}

		if ((front == (start + size / 2)) && (lear == start + size))
			break;
	}
	int j = start;
	for (int i = 0; i < size; i++)
		arr[j++] = temp2[i];

	//delete[] temp;
	//cout << endl;
}

void mergeSort(int arr[], int size)
{
	static int* temp2 = new int[size];
	merge(arr, temp2, 0, size);
	delete[] temp2;
}

void quick(int arr[], int start, int end)
{
	int cursor = end;
	int i = start;
	while (1)
	{
		while ((arr[cursor] >= arr[i]) && (cursor > i))
			cursor--;

		while ((arr[cursor] <= arr[i]) && (cursor < i))
			cursor++;


		if (cursor != i)
		{
			int temp = arr[i];
			arr[i] = arr[cursor];
			arr[cursor] = temp;
			temp = i;
			i = cursor;
			cursor = temp;
		}
		else
			break;
	}
	if (start < cursor)
		quick(arr, start, cursor - 1);
	if (end > cursor)
		quick(arr, cursor + 1, end);
}

bool cmpWord(char in, string& answer, string& nowAnswer)
{
	bool change = false;
	for (int i = 0; i < answer.size(); i++)
	{
		if (answer[i] == in)
		{
			if (nowAnswer[i] == '*')
			{
				nowAnswer[i] = in;
				change = true;
			}
		}
	}

	if(change)
		return 1;
	else
		return 0;
}

void shall(int a[], int n)
{
	int i, j, h;
	for (h = 1; h < n / 9; h = h * 3 + 1)
		;
	for (; h > 0; h /= 3)
	{
		for (i = h; i < n; i++)
		{
			int tmp = a[i];
			for (j = i - h; j >= 0 && a[j] > tmp; j -= h)
				a[j + h] = a[j];
			a[j + h] = tmp;
		}
	}
}

/*
void callme1(StringBad & rsb) 
{
	cout << "ref StringBad : \n";
	cout << "    \"" << rsb << "\"\n";
}
void callme2(StringBad & sb)
{
	cout << "val StringBad : \n";
	cout << "    \"" << sb << "\"\n";
}
*/