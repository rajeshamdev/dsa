#include <iostream>
#include <vector>
using namespace std;

// the same result can be achieved by STL copy_if and lambda,
// but I prefer the below approach for simplicity and efficieny
// reasons.
vector<int> get_odd_numbers(const vector<int> &A)
{
    if (A.size() == 0) {
        return {}; // return empty vec
    }
    vector<int> oddNumsVec;
    for (const auto &i : A) {
        if (i%2) {
           oddNumsVec.push_back(i); 
        }
    }
    return oddNumsVec; // perfectly OK to return local vector.
}
