#include <iostream>
#include <unordered_set>

using namespace std;

int
main(void)
{
    array<int, 6> A = {1, 5, 7, -1}; 
    unordered_set<int> arraySet;
    bool found = false;
    int pair_sum = 6;
    for (int i : A) {
        auto iter = arraySet.find(pair_sum - i);
        if (iter != arraySet.end()) {
            cout << "Pair with sum " << pair_sum << " is (" << *iter << "," << i << ")" << "\n";
            found = true;
        } else  arraySet.insert(i);
    }
    if (!found) {
        cout << "pair not found " << "\n";
    }
}
