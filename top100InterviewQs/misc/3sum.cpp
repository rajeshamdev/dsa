class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        auto len = nums.size();
        if (len < 2) return {};
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        int i = 0;
        while (i < len-2) {
            int target = -nums[i];
            int j = i+1;
            int k = len-1;
            while (j < k) {
                int twoSum = nums[j] + nums[k];
                if (target == twoSum) {
                    res.emplace_back(vector<int>{nums[i], nums[j], nums[k]});
                    do {j++;} while (j < k && nums[j] == nums[j-1]);
                    do {--k;} while (j < k && nums[k] == nums[k+1]);
                } else if (twoSum < target ) {
                    do {j++;} while (j < k && nums[j] == nums[j-1]);
                } else {do {--k;} while (j < k && nums[k] == nums[k+1]);
                }
            }
            do {++i;} while (i < len-2 && nums[i] == nums[i-1]);
        }
        return res;
    }
};
