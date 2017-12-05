#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int> &nums, int target)
{
    if (nums.size() == 0) return {};

    unordered_map<int, int> numMap;
    vector<int> res(2);

    for (int i = 0; i < nums.size(); i++) {
        int a  = target - nums[i];
        auto iter = numMap.find(a);
        if (iter != numMap.end()) {
            res[0] = iter->second;
            res[1] = i;
            break;
        } else {
            numMap[nums[i]] = i;
        }
    }
    return res;
}


int main(void)
{
    vector <int> nums = {2, 7, 11, 15};
    vector<int> res = twoSum(nums, 9);
    cout << res[0] << ", " << res[1] << "\n";

}
