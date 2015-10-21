#include <iostream>
#include <cstring>
using namespace std;

void ReplaceBlank(char *str, int length)
{
	if (str == NULL || length <= 0)
		return;

	int originalLength = 0;
	int numberOfBlank = 0;
	while (str[originalLength] != '\0') {
		if (str[originalLength] == ' ')
			++numberOfBlank;
		++originalLength;
	}

	int newLength = originalLength + numberOfBlank * 2;
	if (newLength > length)
		return;

	int indexOfOriginal = originalLength;
	int indexOfNew = newLength;
	while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal) {
		if (str[indexOfOriginal] == ' ') {
			str[indexOfNew--] = '0';
			str[indexOfNew--] = '2';
			str[indexOfNew--] = '%';
		} else {
			str[indexOfNew--] = str[indexOfOriginal];
		}
		--indexOfOriginal;
	}
}

bool Increment(char *number)
{
	int carray = 1;
	bool isOverflow = false;
	int length = strlen(number);

	for (int i = length - 1; i >= 0; --i) {
		int sum = number[i] - '0' + carray;
		if (sum >= 10) {
			if (i == 0)
				isOverflow = true;
			else {
				number[i] = '0' + sum - 10;
				carray = 1;
			}
		} else {
			number[i] = '0' + sum;
			carray = 0;
		}
	}

	return isOverflow;
}

void PrintNumber(char *number)
{
	int length = strlen(number);
	int start = 0;
	while (start < length && number[start] == '0')
		++start;

	for (int i = start; i < length; ++i)
		cout << number[i];
	cout << endl;
}

void Print1ToMaxOfNDigits(int n)
{
	if (n <= 0)
		return;

	char *number = new char[n + 1];
	memset(number, '0', n);
	number[n] = '\0';

	while (!Increment(number)) {
		PrintNumber(number);
	}

	delete [] number;
}

void Permutation(char *str, char *begin)
{
	if (*begin == '\0')
		cout << str << endl;
	else {
		for (char *p = begin; *p != '\0'; ++p) {
			swap(*p, *begin);
			Permutation(str, begin + 1);
			swap(*p, *begin);
		}
	}
}

void Permutation(char *str)
{
	if (str == NULL)
		return;

	Permutation(str, str);
}

void Combination(char *begin, int m, string &result)
{
	if (m == 0)
		cout << result << endl;
	else if (*begin != '\0') {
		result.push_back(*begin);
    	Combination(begin + 1 , m - 1, result);
    	result.pop_back();
    	Combination(begin + 1 , m, result);
	}
}

void Combination(char *str)
{
	if (str == NULL)
		return;

	string result;
	for (int m = 1; m <= strlen(str); ++m)
		Combination(str, m, result);
}

void Reverse(char *begin, char *end)
{
	if (begin == NULL || end == NULL)
		return;

	while (begin < end) {
		swap(*begin, *end);
		++begin;
		--end;
	}
}

void ReverseSentence(char *str)
{
	if (str == NULL)
		return;

	char *begin = str, *end = str;
	while (*end != '\0')
		++end;
	--end;


	Reverse(begin, end);
	end = str;

	while (*begin != '\0') {
		if (*begin == ' ') {
			++begin;
			++end;
		} else if (*end == ' ' || *end == '\0') {
			Reverse(begin, --end);
			begin = ++end;
		} else ++end;
	}
}

void LeftRotate(char *str, int n)
{
	if (str == NULL || n <= 0)
		return;

	int length = 0;
	while (str[length] != '\0') {
		++length;
	}

	n %= length;

	Reverse(str, str + length - 1);
	Reverse(str, str + length - n - 1);
	Reverse(str + length - n, str + length - 1);
}

bool isValid = true;

long long StrToIntCore(const char *str, bool minus)
{
	long long num = 0;
	while (*str != '\0') {
		if (*str >= '0' && *str <= '9') {
			int flag = minus ? -1 : 1;
			num = num * 10 + flag * (*str - '0');

			if ((!minus && num > INT_MAX)
				|| (minus && num < INT_MIN)) {
				num = 0;
				break;
			}
		} else {
			num = 0;
			break;
		}

		++str;
	}

	if (*str == '\0')
		isValid = true;

	return num;
}

int StrToInt(const char *str)
{
	isValid = false;
	long long num = 0;

	if (str != NULL && *str != '\0') {
		bool minus = false;
		if (*str == '+')
			++str;
		else if (*str == '-') {
			++str;
			minus = true;
		}

		if (*str != '\0')
			num = StrToIntCore(str, minus);
	}

	return (int)num;
}

int main()
{
	// char str[20] = "We are happy.";
	// ReplaceBlank(str, 20);
	// cout << str << endl;
	// Print1ToMaxOfNDigits(2);
	char str[] = "abcdef";
	// Permutation(str);
	// Combination(str);
	// ReverseSentence(str);
	// LeftRotate(str, 2);
	// cout << str << endl;
	cout << StrToInt("1234567890") << endl;
	cout << isValid << endl;
}