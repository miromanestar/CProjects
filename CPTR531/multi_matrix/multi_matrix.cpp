#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;
using Matrix = vector<vector<int>>;

int main();
Matrix genMatrix (int r, int c);
Matrix multiMatrix(Matrix &a, Matrix &b);
Matrix singleMatrix(Matrix &a, Matrix &b);
void printMatrix(const Matrix &a);

int main() {
    auto a = genMatrix(3, 3);
    auto b = genMatrix(3, 3);

    printMatrix(a);
    cout << "-----------------" << endl;
    printMatrix(b);
    cout << "-----------------" << endl;
    printMatrix(singleMatrix(a, b));
}

Matrix genMatrix (int r, int c) {
    Matrix matrix;
    for (int i = 0; i < r; i++) {
        vector<int> row;
        for (int j = 0; j < c; j++) {
            row.push_back(rand() % 10);
        }
        matrix.push_back(row);
    }
    return matrix;
}

Matrix singleMatrix(Matrix &a, Matrix &b) {
    Matrix matrix;

    for (int i = 0; i < (int) a.size(); i++) {
        vector<int> row;
        for (int j = 0; j < (int) b[0].size(); j++) {
            int sum = 0;
            for (int k = 0; k < (int) b.size(); k++) {
                sum += a[i][k] * b[k][j];
            }
            row.push_back(sum);
        }
        matrix.push_back(row);
    }

    return matrix;
}

void printMatrix(const Matrix &a)
{
    for (int i = 0; i < (int) a.size(); i++)
    {
        for (int j = 0; j < (int) a[i].size(); j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}