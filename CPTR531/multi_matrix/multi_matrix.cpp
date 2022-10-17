#include <thread>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "stopwatch.h"

using namespace std;
using Matrix = vector<vector<int>>;

int main();
Matrix genMatrix (int r, int c);
Matrix multiMatrix(Matrix &a, Matrix &b);
Matrix singleMatrix(Matrix &a, Matrix &b);
void printMatrix(const Matrix &a);

int main() {
    int r = 1000;
    int c = 1000;
    auto a = genMatrix(r, c);
    auto b = genMatrix(r, c);

    Stopwatch timer;

    // printMatrix(a);
    // cout << "-----------------" << endl;
    // printMatrix(b);
    // cout << "-----------------" << endl;
    cout << "Beginning single thread multiplication" << endl;
    timer.start();
    // printMatrix(singleMatrix(a, b));
    singleMatrix(a, b);
    timer.stop();
    double single_time = timer.elapsed();

    timer.reset();
    
    //cout << "-----------------" << endl;
    cout << "Beginning multi thread multiplication" << endl;
    timer.start();
    // printMatrix(multiMatrix(a, b));
    multiMatrix(a, b);
    timer.stop();
    double multi_time = timer.elapsed();

    cout << "\n\n-----------------" << endl;
    cout << "Single thread time: " << single_time << " ms." << endl;
    cout << "Multi thread time: " << multi_time << " ms." << endl;
}

Matrix multiMatrix(Matrix &a, Matrix &b) {
    int r = a.size();
    int c = b[0].size();
    Matrix result(r, vector<int>(c, 0));

    vector<thread> threads;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            threads.push_back(thread([&a, &b, &result, i, j] {
                for (int k = 0; k < (int) a[0].size(); k++) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }));
        }
    }

    for (auto &t : threads) {
        t.join();
    }

    return result;
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