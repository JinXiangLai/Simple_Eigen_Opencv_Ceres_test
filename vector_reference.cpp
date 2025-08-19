#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> a{1, 2};
    vector<vector<int>& >b(1);
    b[0] = a;
    a.push_back(3);
    for(const int n : b) {
        cout << n << " ";
    }
    cout << endl;
    return 0;
}
