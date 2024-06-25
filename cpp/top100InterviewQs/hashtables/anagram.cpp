class Solution {
public:
    string countSort(const string &s)
    {
        if (0 == s.length()) return {};
        int A[26] = {0};
        for (auto &ch : s)
            A[ch-'a']++;
        
        string r(s.length(), 'a');
        auto k = 0;
        for (auto i = 0; i < 26; i++)
            for (auto j = 0; j < A[i]; j++)
                r[k++] += i;
        return r;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        if (0 == strs.size()) return {};
        unordered_map<string, vector<string>> anaMap;
        
        for (string &str : strs) {
            auto sortedS = countSort(str);
            anaMap[sortedS].emplace_back(str);
        }
        
        vector<vector<string>> res;
        for (auto strvec : anaMap) {
            vector<string>ana(strvec.second.begin(), strvec.second.end());
            res.emplace_back(ana);
        }
        return res;
    }
};
