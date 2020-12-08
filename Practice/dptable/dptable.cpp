#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> make_table(string s1, string s2) {
    vector<vector<int>> table(s2.length() + 1, vector<int>(s1.length() + 1, 0));

    for (int i = 0; i < (int) s2.length(); i++) {
        for (int j = 0; j < (int) s1.length(); j++) {
            if (s1[i] == s2[j])
                table[i + 1][j + 1] = table[i][j] + 1;
            else
                table[i + 1][j + 1] = (table[i + 1][j] > table[i][j + 1]) ? table[i + 1][j] : table[i][j + 1];
        }
    }

    cout << '\t';
    for (int i = 0; i < (int) table.size(); i++) {
        cout << "\t" << s1[i];
    }
    cout << '\n';
    for (int i = 0; i < (int) table.size(); i++) {
        if (i > 0)
            cout << s2[i - 1] << '\t';
        else
            cout << "\t";
        for (int j = 0; j < (int) table[i].size(); j++) {
            cout << table[i][j] << '\t';
        }
        cout << '\n';
    }

    return table;
}

int main() {
    vector<vector<int>> table = make_table("CATTCAA", "ATCTGCTA");
}