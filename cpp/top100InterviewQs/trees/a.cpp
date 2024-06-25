#include <bits/stdc++.h>

using namespace std;
int main(void)
{
    vector<int> V = {7, 3, 8, 2, 4, 1, 9, 5, 20, 6, 10};
    auto i = find(V.begin(), V.end(), 1) - V.begin();
    cout << i << "\n";
    return 0;
}
