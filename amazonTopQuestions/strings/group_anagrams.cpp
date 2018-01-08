class Solution {
public:
    
    string countSort(const string &str)
    {
        if (str.empty()) return "";
        vector<int> dict(26, 0);
        auto len = str.size();
        for (char ch: str)
            ++dict[ch-'a'];
        string res;
        for (int i = 0; i < 26; i++)
            for (int j = 0; j <dict[i]; j++)
                res += i+'a';
        return res;
    }
    
    vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        if (strs.empty()) return {};
        unordered_map<string, vector<string>> anaMap;
        for (string &str : strs) {
            string str1 = countSort(str);
            anaMap[str1].emplace_back(str);
        }
        vector<vector<string>> res;
        for (auto &iter : anaMap) 
            res.emplace_back(vector<string>(iter.second.begin(), iter.second.end()));
        return res;
    }
};
