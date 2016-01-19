#include <iostream>
#include <cstring>
using namespace std;

int c[10][10];
int b[10][10];

void lcs_length(char *x, char *y)
{
    int m = strlen(x) - 1, n = strlen(y) - 1;

    for (int i = 1; i <= m; i++) c[i][0] = 0;
    for (int j = 1; j <= n; j++) c[0][j] = 0;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (x[i] == y[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 0;
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = 1;
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = 2;
            }
        }
}

void print_lcs(int b[][10], char *x, int i, int j)
{
    if (i == 0 || j == 0) return;
    if (b[i][j] == 0) {
        print_lcs(b, x, i - 1, j - 1);
        cout << x[i] << " ";
    } 
    else if (b[i][j] == 1)
        print_lcs(b, x, i - 1, j);
    else
        print_lcs(b, x, i, j - 1);
}

int main()
{
    char *x = " ABCBDAB";
    char *y = " BDCABA";

    lcs_length(x, y);
    print_lcs(b, x, 7, 6);
    cout << endl;

    return 0;
}
