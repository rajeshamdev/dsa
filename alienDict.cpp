The code is lengthy, but the idea is straightforward.

1.convert words vector into a graph.

2.simply get the result by topological sort.

bool dfs(unordered_map<char, unordered_set<char>>& g, unordered_set<char>& visited, unordered_set<char>& rec, string& order, char n) {
	if (rec.count(n)) return false;
	if (visited.count(n)) return true;

	visited.insert(n);
	rec.insert(n);

	for (auto iter = g[n].begin(); iter != g[n].end(); ++iter)
		if (dfs(g, visited, rec, order, *iter) == false)
			return false;

	rec.erase(rec.find(n));
	order += string(1, n);

	return true;
}

string topsort(unordered_map<char, unordered_set<char>>& g) {
	unordered_set<char> visited;
	unordered_set<char> rec;
	string order;

	for (auto iter = g.begin(); iter != g.end(); ++iter) {
		if (dfs(g, visited, rec, order, iter->first) == false)
			return "";
	}

	reverse(order.begin(), order.end());
	return order;
}

string alienOrder(vector<string>& words) {
	if (words.size() == 1) return words.front();

	unordered_map<char, unordered_set<char>> g;
	for (int i = 1; i < words.size(); i++) {
		string t1 = words[i - 1];
		string t2 = words[i];			
		bool found = false;
		for (int j = 0; j < max(t1.length(), t2.length()); j++) {
			if (j < t1.length() && g.count(t1[j]) == 0)
				g.insert(make_pair(t1[j], unordered_set<char>()));
			if (j < t2.length() && g.count(t2[j]) == 0)
				g.insert(make_pair(t2[j], unordered_set<char>()));
			if (j < t1.length() && j < t2.length() && t1[j] != t2[j] && !found) {
				g[t1[j]].insert(t2[j]);
				found = true;
			}
		}
	}
	
	return topsort(g);
}




==================================================================================================



class Solution { 
public:
    string alienOrder(vector<string> &words){
        string ans;
        if(!words.size()) return ans; 
        
        vector<vector<int>> graph(26, vector<int>()); // directed graph
        unordered_map<int, int> degree; // incoming degree
        if (!buildGraph(words, graph, degree)) return "";           
        // topological sorting
        queue<int> Que; 
        for(auto elem: degree){
            if(!elem.second) Que.push(elem.first);
        }
        
        while(!Que.empty()){
            int v = Que.front(); Que.pop();
            ans.push_back(v + 'a');
            for(auto vv: graph[v]){
                degree[vv]--;
                if(!degree[vv]) Que.push(vv);
            }
        }
        
        for(auto d: degree){ // more edges after topo sort -> circle 
            if(d.second > 0) return "";
        }
        
        return ans;
    }
    
    bool buildGraph(vector<string> &words, vector<vector<int>> &graph, unordered_map<int, int> &degree){
        for(auto w: words)
            for(auto c: w) degree[c - 'a'] = 0;
        
        for(int i = 1; i < (int)words.size(); i++){
            string pre = words[i - 1], cur = words[i];
            int pre_sz = (int)pre.size(), cur_sz = (int)cur.size(), j = 0;

            while(j < pre_sz && j < cur_sz && pre[j] == cur[j]){ j++;} 
            if(j < pre_sz && j == cur_sz) return false; // e.g. “eb” appears before “e” is invalid
            if(j < cur_sz && j < pre_sz){
                graph[pre[j] - 'a'].push_back(cur[j] - 'a'); // add directed edge to graph
                degree[cur[j] - 'a']++; 
            } 
        }
        
        return true;
    }
};

============================================================================================================
