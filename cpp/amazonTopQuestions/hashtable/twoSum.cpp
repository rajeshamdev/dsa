class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        unordered_map<int, int> sumMap;
        
        for (auto i = 0; i < nums.size(); i++) {
            auto iter = sumMap.find(target - nums[i]);
            if ( iter == sumMap.end()) {
                sumMap.emplace(nums[i], i);
            } else {
                return {iter->second, i};
            }
        }
    }
};
