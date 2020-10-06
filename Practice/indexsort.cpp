#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

vector<int> index_sort(vector<int> v);
void print_vec(vector<int> v);
std::ostream& operator<<(std::ostream& os, const vector<int>& v);

int main() {

    //Build vector with v_size random numbers
    int v_size = 10'000'000;
    vector<int> v(v_size);
    auto f = [v_size]() -> int { return rand() % v_size; };
    generate(v.begin(), v.end(), f);

    //Start timer for time measurement
    auto start = high_resolution_clock::now();

    //Sort vector v
    vector<int> sorted = index_sort(v);

    //Stop timer and calculate duration
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    //print_vec(sorted);
    cout << "\nProgram finished in " << duration.count()/1000 << "ms";
}

vector<int> index_sort(vector<int> v) {
    //Find max value in v
    int max = 0;
    for (int val : v) {
        if(val > max) {
            max = val;
        }
    }

    //Create new vector with a corresponding index for each number in the array
    //Then set each corresponding index to "1" if it has an equivalent 
    vector<int> temp(max + 1);
    for(int val : v) {
        //Counts the number of times if there's a duplicate
        temp[val] += 1;
    }

    //Create new array composed if the indexes from temp that contained values greater than 0
    vector<int> sorted;
    for(int i = 0; i < temp.size(); i++) {
        if(temp[i] != 0) {
            sorted.push_back(i);
        }
    }

    return sorted;
}

void print_vec(vector<int> v) {
    for(int val : v)
        cout << val << ' ';
}

std::ostream& operator<<(std::ostream& os, const vector<int>& v) {
    for (auto val : v) {
        os << val << ' ';
    }
    return os;
}
