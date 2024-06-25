#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    unordered_map<char, set<char>> Graph;
    unordered_map<char, bool> visited;
    stack<char> stk;
    
    void addEdge(const char &a, const char &b)
    {
        Graph[a].emplace(b);
        visited[a] = 0;
        visited[b] = 0;
        cout << "Rajesham1 : " << a << "->" << b << "\n";
    }
    
    void dfs(const char &ch)
    {
        cout << "dfs : " << ch << "\n";
        visited[ch] = 1;
        for (auto &sib : Graph[ch]) {
            if (!visited[sib]) {
                dfs(sib);
            }
        }
        stk.push(ch);
    }
    
    void toposort(void)
    {
        unordered_map<char, set<char>>::iterator node = Graph.begin();
        //for (; node != Graph.end(); node++) {
        for (auto &node: visited) {
            cout << "Rajesham " << node.first << "\n";
            if (!visited[node.first]) {
                dfs(node.first);
            }
        }
    }
    string alienOrder(vector<string>& words)
    {
        auto len = words.size();
        if (0 == len) return "";
        
        for (int i = 0; i < len-1; i++) {
            string word1 = words[i];
            string word2 = words[i+1];
            for (auto j = 0; j < min(word1.size(), word2.size()); j++) {
                if (word1[j] != word2[j]) {
                    addEdge(word1[j], word2[j]);
                    break;
                }
            }
        }
        toposort();
        string res;
        while (!stk.empty()) {
            res += stk.top();
            stk.pop();
        }
        return res;
    }
};

int main(void)
{
    vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};
    Solution s;
    string res = s.alienOrder(words);
    cout << "order : " << res << "\n";
}
