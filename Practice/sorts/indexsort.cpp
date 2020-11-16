#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <conio.h>

using namespace std;
using namespace std::chrono;

vector<int> index_sort(vector<int> v);
void print_vec(vector<int> v);
std::ostream& operator<<(std::ostream& os, const vector<int>& v);

int main() {

    cout << "Enter array size\n";
    int v_size;
    cin >> v_size;

    //Build vector with v_size random numbers, range: -v_size < x < v_size
    vector<int> v(v_size);
    auto f = [v_size]() -> int {
        int val = rand() % 100;
        if(val <= 50)
            return rand() % v_size;
        else
            return rand() % v_size * -1;
    };
    cout << "Print vector on finish? Y/N\n";
    char doPrint;
    cin >> doPrint;
    cout << "Generating array....\n";

    generate(v.begin(), v.end(), f);

    //Start timer for time measurement
    cout << "Sorting....\n";
    auto start = high_resolution_clock::now();

    //Sort vector v
    vector<int> sorted = index_sort(v);

    //Stop timer and calculate duration
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    if(doPrint == 'Y' || doPrint == 'y') {
        cout << "\n---------- UNSORTED VECTOR ----------\n";
        print_vec(v);
        cout << "\n---------- SORTED VECTOR ----------\n";
        print_vec(sorted);
    }

    cout << "\nArray sorted in " << duration.count() << " microseconds, " << duration.count()/1000 << " milliseconds, " 
         << duration.count()/1'000'000 << " seconds.";

    cout << "\n\nPress any key to exit\n";
    getch();
}

vector<int> index_sort(vector<int> v) {
    //Find max/min value in vector v
    int max = 0;
    int min = 0;
    for (int val : v) {
        if(val > max)
            max = val;
        if(val < min)
            min = val;
    }

    //Create new vector with a corresponding index for each number in the array
    //If min < 0, increase size by min and use it as offset for negative values; i.e. index '0' would represent -1 if the min is -1
    //Then set each corresponding index to "1" if it has an equivalent 
    vector<int> temp((min * -1) + max + 1);
    for(int val : v) {
        //Counts the number of times if there's a duplicate
        temp[val + (min * -1)] += 1;
    }

    //Create new array composed if the indexes from temp that contained values greater than 0
    //Preserves duplicates
    vector<int> sorted;
    for(int i = 0; i < (int) temp.size(); i++) {
        if(temp[i] != 0) {
            for(int k = 0; k < temp[i]; k++) {
                sorted.push_back(i - (min * -1));
            }
        }
    }

    return sorted;
}

void print_vec(vector<int> v) {
    for(int val : v)
        cout << val << ' ';
    cout << '\n';
}

std::ostream& operator<<(std::ostream& os, const vector<int>& v) {
    for (auto val : v) {
        os << val << ' ';
    }
    return os;
}
