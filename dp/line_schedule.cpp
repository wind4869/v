#include <iostream>
using namespace std;

// 存放结果的全局变量

int f[2][6];
int l[2][6];
int f_, l_;

void fastest_way(int a[][6], int t[][5], int e[], int x[], int n)
{
    f[0][0] = e[0] + a[0][0];
    f[1][0] = e[1] + a[1][0];

    for (int j = 1; j < n; j++) {
        if (f[0][j - 1] <= f[1][j - 1] + t[1][j - 1]) {
            f[0][j] = f[0][j - 1] + a[0][j];
            l[0][j] = 1;
        } else {
            f[0][j] = f[1][j - 1] + t[1][j - 1] + a[0][j];
            l[0][j] = 2;
        }

        if (f[1][j - 1] <= f[0][j - 1] + t[0][j - 1]) {
            f[1][j] = f[1][j - 1] + a[1][j];
            l[1][j] = 2;
        } else {
            f[1][j] = f[0][j - 1] + t[0][j - 1] + a[1][j];
            l[1][j] = 1;
        }
    }    

    if (f[0][n - 1] + x[0] <= f[1][n - 1] + x[1]) {
        f_ = f[0][n - 1] + x[0];
        l_ = 1;
    } else {
        f_ = f[1][n - 1] + x[1];
        l_ = 2;
    }
}

// 逆序输出

void print_station(int l[][6], int l_, int n)
{
    int i = l_;
    cout << "line " << i << ", station " << n << endl;
    for (int j = n - 1; j > 0; j--) {
        i = l[i - 1][j];
        cout << "line " << i << ", station " << j << endl;
    }
}

// 顺序输出

void print_station_recursive(int l[][6], int i, int j)
{
    if (j == 0) return;
    print_station_recursive(l, l[i - 1][j - 1], j - 1);
    cout << "line " << i << ", station " << j << endl;
}

int main()
{
    int a[2][6] = {
        {7, 9, 3, 4, 8, 4},
        {8, 5, 6, 4, 5, 7}
    };

    int t[2][5] = {
        {2, 3, 1, 3, 4},
        {2, 1, 2, 2, 1}
    };

    int e[2] = {2, 4};
    int x[2] = {3, 2};

    fastest_way(a, t, e, x, 6);

    // print_station(l, l_, 6);
    print_station_recursive(l, l_, 6);

    return 0;
}
