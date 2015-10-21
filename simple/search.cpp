#include <iostream>
using namespace std;

int BinarySearch(int a[], int low, int high, int val)
{
	if (low <= high) {
		int mid = low + ((high - low) >> 1);
		if (val == a[mid]) return mid;
		else if (val > a[mid]) low = mid + 1;
		else high = mid - 1;
	}
	return -1;
}

int RecursiveBS(int a[], int low, int high, int val)
{
	if (low <= high) {
		int mid = low + ((high - low) >> 1);
		if (val == a[mid]) return mid;
		else if (val > a[mid]) return RecursiveBS(a, mid + 1, high, val);
		else return RecursiveBS(a, low, mid - 1, val);
	}
	return -1;
}

int LowerBound(int a[], int left, int right, int val)
{
	int low = left - 1, high = right + 1;
	while (low < high - 1) {
		int mid = low + ((high - low) >> 1);
		if (a[mid] < val) low = mid;
		else high = mid;
	}

	if (high <= right && a[high] == val) return high;
	else return -high;
}

int UpperBound(int a[], int left, int right, int val)
{
	int low = left - 1, high = right + 1;
	while (low < high - 1) {
		int mid = low + ((high - low) >> 1);
		if (a[mid] <= val) low = mid;
		else high = mid;
	}

	if (low >= left && a[low] == val) return low;
	else return -(low + 1);
}

int MinInOrder(int a[], int low, int high)
{
	int result = a[low];
	for (int i = low + 1; i <= high; ++i)
		if (a[i] < result) result = a[i];
	return result;
}

int FindMinInRotatedArray(int a[], int n)
{
	int low = 0, high = n - 1;
	if (a[low] < a[high]) return a[0]; // no rotating

	while (low < high - 1) {
		int mid = low + ((high - low) >> 1);

		if (a[low] == a[high] && a[low] == a[mid])
			return MinInOrder(a, low, high);

		if (a[mid] >= a[low]) low = mid;
		else high = mid;
	}

	return a[high];
}

bool FindInRotatedArray(int a[], int n, int val)
{
	int low = 0, high = n - 1;
	while (low <= high) {
		int mid = low + ((high - low) >> 1);

		if (a[mid] == val) return true;

		if (a[mid] == a[high]) {
			for (int i = low; i <= high; ++i) {
				if (a[i] == val)
					return true;
			}
			return false;
		} else if (a[mid] < a[high]) {
			if (val > a[mid] && val <= a[high])
				low = mid + 1;
			else
				high = mid - 1;
		} else {
			if (val < a[mid] && val >= a[low])
				high = mid - 1;
			else
				low = mid + 1;
		}
	}
	return false;
}

int main()
{
	int a[] = {1, 1, 1, 0, 1};
	// cout << FindMinInRotatedArray(a, 5) << endl;
	cout << FindInRotatedArray(a, 5, 0) << endl;
}