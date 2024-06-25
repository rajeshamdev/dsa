
/**
 * There are a total of n courses you have to take, labeled from 0 to n - 1.
 * Some courses may have prerequisites, for example to take course 0 you have
 * to first take course 1, which is expressed as a pair: [0,1]
 *
 * Given the total number of courses and a list of prerequisite pairs,
 * is it possible for you to finish all courses?
 */

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites)
    {
        vector<int> indegree(numCourses, 0);
        vector<vector<int>> coursesGraph(numCourses);
        
        //step-1: construct the graph and indegree for each course.
        for (auto &courseOrder: prerequisites) {
            coursesGraph[courseOrder.second].emplace_back(courseOrder.first);
            indegree[courseOrder.first]++;
        }
        // create a queue with indegree zero courses.
        queue<int> q;
        for (auto i = 0; i < numCourses; i++) {
            if (0 == indegree[i]) {q.push(i);}
        }
        int cnt = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop(); ++cnt;
            for (auto &v : coursesGraph[u]) {
                if (--indegree[v] == 0) {q.push(v);}
        }
        return cnt == numCourses;
        
    }
};
