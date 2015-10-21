#include <iostream>
#include <set>
using namespace std;

void BubbleSort(int a[], int n) 
{
	for (int i = n - 1; i > 0; --i)
		for (int j = 0; j < i; ++j)
			if (a[j] > a[j + 1])
				swap(a[j], a[j + 1]);
}

void InsertSort(int a[], int n)
{
	for (int i = 1; i < n; ++i) {
		int key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key) {
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = key;
	}
}

int RandomInRange(int low, int high)
{ 
	return low + rand() % (high - low + 1); // [low, high]
}

int Partition(int a[], int low, int high)
{
	int mid = low - 1;
	swap(a[RandomInRange(low, high)], a[high]);
	for (int i = low; i <= high; ++i)
		if (a[i] <= a[high])
			swap(a[++mid], a[i]);
	return mid;
}

void QuickSort(int a[], int low, int high)
{
	if (low < high) {
		int mid = Partition(a, low, high);
		QuickSort(a, low, mid - 1);
		QuickSort(a, mid + 1, high);
	}
}

void Merge(int a[], int low, int mid, int high)
{
	int *temp = new int[high - low + 1];
	int i = low, j = mid + 1, k = 0;

	while (i <= mid && j <= high) {
		if (a[i] <= a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}

	while (i <= mid) temp[k++] = a[i++];
	while (j <= high) temp[k++] = a[j++];

	for (int i = 0; i < k; ++i)
		a[low + i] = temp[i];

	delete [] temp;
}

void MergeSort(int a[], int low, int high)
{
	if (low < high) {
		int mid = low + ((high - low) >> 1);
		MergeSort(a, low, mid);
		MergeSort(a, mid + 1, high);
		Merge(a, low, mid, high);
	}
}

void MaxHeapify(int a[], int n, int i)
{
	int left = (i << 1) + 1;
	int right = left + 1;
	int largest = i;

	while (left < n || right < n) {
		if (left < n && a[left] > a[largest]) largest = left;
		if (right < n && a[right] > a[largest]) largest = right;

		if (largest != i) {
			swap(a[i], a[largest]);
			left = (largest << 1) + 1;
			right = left + 1;
		} else break;
	}
}

void HeapSort(int a[], int n)
{
	for (int i = n / 2 - 1; i >= 0; --i)
		MaxHeapify(a, n, i);

	for (int i = n - 1; i > 0; --i) {
		swap(a[i], a[0]);
		MaxHeapify(a, i, 0);
	}
}

int MoreThanHalfNum(int a[], int n)
{
	int mid = n >> 1;
	int low = 0, high = n - 1;
	int index = Partition(a, low, high);

	while (index != mid) {
		if (index > mid) high = index - 1;
		else low = index + 1;

		index = Partition(a, low, high);
	}

	return a[mid];
}

// void GetLeastNumbers(int a[], int n, int k)
// {
// 	int low = 0, high = n - 1;
// 	int index = Partition(a, low, high);

// 	while (index != k - 1) {
// 		if (index > k - 1) high = index - 1;
// 		else low = index + 1;

// 		index = Partition(a, low, high);
// 	}

// 	for (int i = 0; i < k; ++i)
// 		cout << a[i] << endl;
// }

// void GetLeastNumbers(int a[], int n, int k)
// {
// 	multiset<int, greater<int>> leastNumbers;
// 	for (int i = 0; i < n; ++i) {
// 		if (leastNumbers.size() < k)
// 			leastNumbers.insert(a[i]);
// 		else {
// 			auto iter = leastNumbers.begin();
// 			if (a[i] < *iter) {
// 				leastNumbers.erase(iter);
// 				leastNumbers.insert(a[i]);
// 			}
// 		}
// 	}

// 	for (auto &i : leastNumbers)
// 		cout << i << endl;
// }

void GetLeastNumbers(int a[], int n, int k)
{
	int *leastNumbers = new int[k];
	for (int i = 0; i < k; ++i)
		leastNumbers[i] = a[i];
	for (int i = k / 2 - 1; i >= 0; --i)
		MaxHeapify(leastNumbers, k, i);
	for (int i = k; i < n; ++i) {
		if (a[i] < leastNumbers[0]) {
			leastNumbers[0] = a[i];
			MaxHeapify(leastNumbers, k, 0);
		}
	}
	for (int i = 0; i < k; ++i)
		cout << leastNumbers[i] << endl;
}

bool IsContinuous(int a[], int n)
{
	QuickSort(a, 0, n - 1);

	int numberOfZero = 0;
	for (int i = 0; i < n && a[i] == 0; ++i)
		++numberOfZero;

	int numberOfGap = 0;
	int low = numberOfZero, high = low + 1;
	while (high < n) {
		if (a[low] == a[high])
			return false;

		numberOfGap += a[high] - a[low] - 1;
		++low;
		++high;
	}

	return (numberOfGap <= numberOfZero) ? true : false;
}

int main()
{
	// int a[] = {5, 3, 4, 1, 2};
	// QuickSort(a, 0, 4);
	// for (int i = 0; i < 5; ++i)
		// cout << a[i] << endl;
	// int a[] = {2, 2, 1, 3};
	// cout << MoreThanHalfNum(a, 4) << endl;
	int a[] = {5, 3, 4, 1, 2};
	// GetLeastNumbers(a, 5, 3);
	cout << IsContinuous(a, 5) << endl;
}