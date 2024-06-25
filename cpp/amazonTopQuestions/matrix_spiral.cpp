class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        if (matrix.size() == 0) return {};
        int rows = matrix.size();
        int cols = matrix[0].size();
        int rb = 0, re = rows-1; // row begin and end pointers
        int cb = 0, ce = cols-1; // col begin and end pointers
        vector<int> res;
        while (rb <= re && cb <= ce) {
            for (int i = cb; i <= ce; i++)
                res.emplace_back(matrix[rb][i]);
            rb++;
        
            for (int i = rb; i <= re; i++)
                res.emplace_back(matrix[i][ce]);
            ce--;
            
            if (rb > re || cb > ce) break;
        
            for (int i = ce; i >= cb; i--)
                res.emplace_back(matrix[re][i]);
            re--;
        
            for (int i = re; i >= rb; i--)
                res.emplace_back(matrix[i][cb]);
            cb++;
        }
        return res;
    }
};
