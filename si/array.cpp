#include <iostream>
using namespace std;

bool FindInMatrix(int **matrix, int rows, int columns, int val)
{
	if (matrix == NULL || rows <= 0 || columns <= 0)
		return false;

	int row = 0;
    int column = columns - 1;

	while (row < rows && column >= 0) {
		if (val == matrix[row][column])
			return true;
		else if (val > matrix[row][column]) ++row;
		else --column;
	}

	return false;
}

void PrintMatrixInCircle(int **matrix, int rows, int columns, int start)
{
	int rowEnd = rows - 1 - start;
	int columnEnd = columns - 1 - start;

	for (int i = start; i <= columnEnd; ++i)
		cout << matrix[start][i] << endl;

	if (start < rowEnd)
		for (int i = start + 1; i <= rowEnd; ++i)
			cout << matrix[i][columnEnd] << endl;

	if (start < rowEnd && start < columnEnd)
		for (int i = columnEnd - 1; i >= start; --i)
			cout << matrix[rowEnd][i] << endl;

	if (start < rowEnd - 1 && start < columnEnd)
		for (int i = rowEnd - 1; i >= start + 1; --i)
			cout << matrix[i][start] << endl;
}

void PrintMatrixClockwisely(int **matrix, int rows, int columns)
{
	if (matrix == NULL || rows <= 0 || columns <= 0)
		return;

	int start = 0;
	while (rows > 2 * start && columns > 2 * start) {
		PrintMatrixInCircle(matrix, rows, columns, start);
		++start;
	}
}

void Test(int columns, int rows)
{
	int **matrix = new int*[rows];
	for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[columns];
        for(int j = 0; j < columns; ++j) {
            matrix[i][j] = i * columns + j + 1;
        }
    }

    PrintMatrixClockwisely(matrix, columns, rows);
    // cout << FindInMatrix(matrix, rows, columns, 17) << endl;

    for (int i = 0; i < rows; ++i)
        delete [] (int*)matrix[i];

    delete[] matrix;
}

int MoreThanHalfNum(int *numbers, int length)
{
	int result, count;
	for (int i = count = 0; i < length; ++i) {
		if (count == 0) {
			result = numbers[i];
			count = 1;
		} else {
			if (numbers[i] == result)
				++count;
			else
				--count;
		}
	}

	return result;
}

void FindNumsAppearOnce(int *numbers, int length)
{
	if (numbers == NULL || length <= 0)
		return;

	int resultXor = 0;
	for (int i = 0; i < length; ++i)
		resultXor ^= numbers[i];

	int indexOf1 = 0;
	while ((resultXor & 1) == 0 && indexOf1 < 8 * sizeof(int)) {
		resultXor >>= 1;
		++indexOf1;
	}

	int num1 = 0, num2 = 0;
	for (int i = 0; i < length; ++i) {
		if ((numbers[i] >> indexOf1) & 1)
			num1 ^= numbers[i];
		else
			num2 ^= numbers[i];
	}

	cout << num1 << " " << num2 << endl;
}

bool TwoSum(int *numbers, int length, int sum)
{
	bool found = true;
	if (numbers == NULL || length <= 1)
		return false;

	int low = 0, high = length - 1;
	while (low < high) {
		int currentSum = numbers[low] + numbers[high];
		if (currentSum == sum) {
			cout << numbers[low] << " " << numbers[high] << endl;
			return true;
		} else if (currentSum > sum) --high;
		else ++low;
	}

	return false;
}

void AnyContinuousSum(int *numbers, int length, int sum)
{
	if (numbers == NULL || length <= 1)
		return;

	int low = 0, high = 1;
	int currentSum = numbers[low] + numbers[high];

	while (low < high && high < length) {
		if (currentSum > sum) {
			currentSum -= numbers[low];
			++low;
		} else {
			if (currentSum == sum) {
				for (int i = low; i <= high; ++i)
					cout << numbers[i] << " ";
				cout << endl;
			}

			++high;
			currentSum += numbers[high];
		}
	}
}

int main()
{
	// Test(4, 4);
	// int numbers[] = {2, 2, 3, 1, 2};
	// cout << MoreThanHalfNum(numbers, 5) << endl;
	// int numbers[] = {1, 2, 3, 3, 4, 4, 5, 5};
	// FindNumsAppearOnce(numbers, 8);
	int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8};
	// cout << TwoSum(numbers, 5, 7) << endl;
	AnyContinuousSum(numbers, 8, 15);
}
