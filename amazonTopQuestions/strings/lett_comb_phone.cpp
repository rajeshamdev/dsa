class Solution {
public:
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty()) return {};
        vector<string> keyMap = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> res = {""};
        for (char &key : digits) {
            if (!isdigit(key)) return {};
            int index = key-'0';
            if (0 == index || 1 == index) continue;
            vector<string> tmp;
            for (char &ch: keyMap[index]) {
                for (string &str: res) {
                    tmp.emplace_back(str + ch);
                }
            }
            res = tmp;
        }
        return res;
    }
};
