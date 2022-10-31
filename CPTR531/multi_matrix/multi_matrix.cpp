#include <thread>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "stopwatch.h"


using namespace std;
using Matrix = vector<vector<int>>;

int main();
Matrix genMatrix (int r, int c);
Matrix multiMatrix(Matrix &a, Matrix &b, int numThreads);
void multiply(Matrix &a, Matrix &b, Matrix &result, int start, int end);
Matrix singleMatrix(Matrix &a, Matrix &b);
void printMatrix(const Matrix &a);

int main() {
    int r = 20;
    int c = 20;
    int numThreads = 4;

    string in;
    cout << "Enter max number of threads (Default: 4): ";
    getline(cin, in);
    if (!in.empty())
        numThreads = stoi(in);
    cout << "Enter number of rows and columns (Default: 20): ";
    getline(cin, in);
    if (!in.empty()) {
        r = stoi(in);
        c = stoi(in);
    }

    auto a = genMatrix(r, c);
    auto b = genMatrix(r, c);

    Stopwatch timer;

    // printMatrix(a);
    // cout << "-----------------" << endl;
    // printMatrix(b);
    // cout << "-----------------" << endl;
    cout << "Beginning single thread multiplication" << endl;
    timer.start();
    //printMatrix(singleMatrix(a, b));
    singleMatrix(a, b);
    timer.stop();
    double single_time = timer.elapsed();

    timer.reset();
    
    //cout << "-----------------" << endl;
    cout << "Beginning multi thread multiplication" << endl;
    timer.start();
    //printMatrix(multiMatrix(a, b));
    multiMatrix(a, b, numThreads);
    timer.stop();
    double multi_time = timer.elapsed();

    cout << "-----------------" << endl;
    cout << "Single thread time: " << single_time << "s." << endl;
    cout << "Multi thread time: " << multi_time << "s." << endl;
}

Matrix multiMatrix(Matrix &a, Matrix &b, int numThreads) {
    int r = a.size();
    int c = b[0].size();
    Matrix result(r, vector<int>(c, 0));

    vector<thread> threads;

    // This creates a thread for each row
    // for (int i = 0; i < r; i++) {
    //     threads.push_back(thread([&a, &b, &result, i] {
    //         for (int j = 0; j < (int) b[0].size(); j++) {
    //             for (int k = 0; k < (int) a[0].size(); k++) {
    //                 result[i][j] += a[i][k] * b[k][j];
    //             }
    //         }
    //     }));
    //     cout << "Thread " << i << " created." << endl;
    // }

    // This creates threads according to the max thread constant
    int remainder = r % numThreads;
    int count = r / numThreads;
    for (int t = 0; t < numThreads; t++) {
        threads.push_back(thread([&a, &b, &result, t, count, remainder, numThreads] {
            if (t == numThreads - 1) {
                multiply(a, b, result, t * count, (t + 1) * count + remainder);
            } else {
                multiply(a, b, result, t * count, (t + 1) * count);
            }
        }));
        cout << "Thread " << t << " created." << endl;
    }

    cout << "Awaiting threads to finish" << endl;
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

void multiply(Matrix &a, Matrix &b, Matrix &result, int start, int end) {
    for (int i = start; i < end; i++) {
        for (int j = 0; j < (int) b[0].size(); j++) {
            for (int k = 0; k < (int) a[0].size(); k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

Matrix genMatrix(int r, int c) {
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