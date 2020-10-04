#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> index_sort(vector<int> v);
void print_vec(vector<int> v);
std::ostream& operator<<(std::ostream& os, const vector<int>& v);

int main() {
    vector<int> v{5, 30, 9, 8, 15, 22, 6};
    vector<int> sorted = index_sort(v);
    print_vec(sorted);
}

vector<int> index_sort(vector<int> v) {
    int max = 0;
    for (int val : v) {
        if(val > max) {
            max = val;
        }
    }

    vector<int> temp(max);
    for(int val : v) {
        temp[val] = 1;
    }

    vector<int> sorted;
    for(int val : temp) {
        if(val != 0) {
            sorted.push_back(val);
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
