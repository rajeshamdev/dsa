class Solution {
public:
    int longestConsecutive(vector<int>& nums)
    {
        auto len = nums.size();
        if (0 == len) return 0;
        unordered_set<int> numSet(nums.begin(), nums.end());
        int maxlen = 1;
        for (int &num : nums) {
            if (numSet.find(num-1) != numSet.end()) continue;
            int seqlen = 1;
            while (numSet.find(++num) != numSet.end()) seqlen++;
            maxlen = max(maxlen, seqlen);
        }
        return maxlen;
    }
};
