#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
class Solution {
public:
    vector<int> anagramMappings(vector<int>& A, vector<int>& B)
    {
        auto Alen = A.size();
        auto Blen = B.size();
        if (Alen != Blen || Alen == 0 || Blen == 0) return {};
        unordered_map<int, int> Bmap;
        for (auto i = 0; i < B.size(); i++) {
            Bmap.emplace(B[i], i);;
        }
        vector<int> res;
        for (auto i = 0; i < A.size(); i++) {
            res.push_back(Bmap[A[i]]);
        }
        return res;
    }
};

int main(void)
{
    vector<int> A = {12,28,46,32,50};
    vector<int> B = {50,12,32,46,28};
    Solution s;
    vector<int> C = s.anagramMappings(A, B);
    for (auto &i : C)
       cout << " " << i ;
}
