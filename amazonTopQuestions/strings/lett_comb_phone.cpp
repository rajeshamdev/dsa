class Solution {
public:
    vector<string> letterCombinations(string digits)
    {
        auto len = digits.size();
        if (0 == len) return {};
        vector<string> keyMap = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> res = {""};
        for (auto i = 0; i < len; i++) {
            // if (!isdigit(digits[i])) return {};
            int vecIndex = digits[i] - '0';
            if (0 == vecIndex || 1 == vecIndex) continue;
            string str = keyMap[vecIndex];
            vector<string>tmp;
            for (auto j = 0; j < str.size(); j++) {
                for (auto k = 0; k < res.size(); k++) {
                    tmp.push_back(res[k] + str[j]);
                }
            }
            res.swap(tmp);
        }
        return res;
    }
};
