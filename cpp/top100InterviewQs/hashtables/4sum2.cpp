class Solution {
public:
    
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D)
    {   
        unordered_map<int, int> sum1;
        for (auto &a : A)
            for (auto &b : B)
                sum1[a+b]++;
        auto count = 0;
        for (auto &c : C)
            for (auto &d : D) {
                auto iter = sum1.find(-c-d);
                if (iter != sum1.end()) {
                    count += iter->second;
                }
            }
        return count;
    }
};
