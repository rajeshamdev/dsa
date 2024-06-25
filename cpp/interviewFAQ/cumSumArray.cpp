#include <iostream>
#include <string>
#include <vector>
using namespace std;

// A = {1, 2, 3, 4, 5, 6, 7, 8}
// w = 3
// [1, 2, 3,
//  4, 5, 6,
//  7, 8, 9]
// for  index = 6 is A(2,0) row = index/w, col = index % w.
// o = { 1, 3, 6, 5, 12, 21, 12, 27, _}
void printVector(const vector<int>& v)
{
    for (const auto& val : v)
    {
        cout << val << '\t';
    }

    cout << '\n';
}

vector<int> cumSum(const vector<int>& input, int w)
{
    size_t len = input.size();
    if (len == 0 || len < w) {
      return {};
    }

    vector<int> resVec(len);
    for (auto i = 0; i < len; i++) {
        auto row = i / w;
        auto col = i % w;
        if (row == 0 && col == 0) {
            resVec[i] = input[i];
            continue;
        }

        if (row == 0) {
            resVec[i] = resVec[i-1] + input[i];
            continue;
        }

        if (col == 0) {
            resVec[i] = resVec[i-w]+ input[i];
            continue;
        }

        resVec[i] = resVec[i-1] + resVec[i-w] + input[i] - resVec[i - w - 1];
    }
    
    return resVec;
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6};
    printVector(v);
    auto output = cumSum(v, 3);
    printVector(output);
    return 0;
}
