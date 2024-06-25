class Solution {
public:
    bool isAnagram(string s, string t)
    {
        auto len = s.size();
        if (len != t.size()) return false;
        
        unordered_map<char, int> anaMap;
        for (auto i = 0; i < len; i++) {
            anaMap[s[i]-'a']++;
            anaMap[t[i]-'a']--;
        }
        for (auto &iter : anaMap) {
            if (iter.second) return false;
        }
        return true;
    }
};
