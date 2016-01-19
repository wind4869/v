#include <iostream>
using namespace std;

int LIS(int a[], int n)
{
    int* length = new int[n];
    int* record = new int[n];
    for (int i = 0; i < n; i++) {
        length[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (a[i] < a[j] && length[j] + 1 > length[i]) {
                length[i]  = length[j] + 1;
                record[i] = j;
            }
        }
    }

    int maxIndex, max = length[0];
    for (int i = 0; i < n; ++i) {
        if (length[i] > max) {
            max = length[i];
            maxIndex = i;
        }
    }
    int maxLength = length[maxIndex];
    int* temp = new int[maxLength];

    temp[maxLength - 1] = maxIndex;
    for (int i = maxLength - 2; i >= 0; --i) {
        temp[i] = record[temp[i + 1]];
    }

    for (int i = 0; i < maxLength; ++i)
        cout << a[temp[i]] << ' ';
    cout << endl;

    delete[] length;
    delete[] record;
    delete[] temp;

    return maxLength;
}

int main()
{
    int a[] = {9, 4, 3, 2, 5, 4, 3, 2};
    cout << LIS(a, 8) << endl;
}
