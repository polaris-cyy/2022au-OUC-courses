#include<iostream>
#include<algorithm>
#include<ctime>
using namespace std;
const int MAXSIZE = 1e5 + 7;

int arr[MAXSIZE];
int temp[MAXSIZE];

void BubbleSort(int a[], int n)
{
	int i, j, temp;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}

void QuickSort(int a[], int left, int right)
{
	if (left >= right)   return;
	int i = left, j = right, key = a[left];
	while (i < j) {
		while (i < j && key <= a[j]) j--;
		a[i] = a[j];
		while (i < j && key >= a[i]) i++;
		a[j] = a[i];
	}
	a[i] = key;
	QuickSort(a, left, i - 1);
	QuickSort(a, i + 1, right);
}

void BubbleTimer(int a[], int n) {
	clock_t start, end;
	for (int i = 0; i < MAXSIZE; ++i) {
		temp[i] = a[i];
	}
	start = clock();
	BubbleSort(temp, n);
	end = clock();
	cout << "排序时间: " << end - start << "ms" << endl;
}

void QSTimer(int a[], int left, int right) {
	clock_t start, end;
	for (int i = 0; i < MAXSIZE; ++i) {
		temp[i] = a[i];
	}
	start = clock();
	QuickSort(temp, left, right);
	end = clock();
	cout << "排序时间: " << end - start << "ms" << endl;
}

int main() {
	srand(time(0));
	for (int i = 0; i < MAXSIZE; ++i) {
		arr[i] = rand();
	}
	QSTimer(arr, 0, MAXSIZE - 1);
	BubbleTimer(arr, MAXSIZE);
	return 0;
}