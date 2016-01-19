#include <iostream>
#include<limits>
using namespace std;

#define NUM 6

int m[NUM][NUM];
int s[NUM][NUM];

void matrix_chain_order(int p[], int n)
{
    for (int i = 0; i < n; i++) m[i][i] = 0;

    for (int l = 2; l <= n; l++)
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            m[i][j] = numeric_limits<int>::max();
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
}

void print_optimal_parens(int s[][NUM], int i, int j)
{
    if (i == j) cout << "A" << i;
    else {
        cout << "(";
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int main()
{
    int p[] = {30, 35, 15, 5, 10, 20, 25};
    matrix_chain_order(p, NUM);
    print_optimal_parens(s, 0, NUM - 1);
    cout << endl;

    return 0;

}
