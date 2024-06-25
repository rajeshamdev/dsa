#include <bits/stdc++.h>

using namespace std;

unordered_map<string, unordered_set<string>> empMap;

void createEmpMap(const string &emp, const string &man)
{
     if (emp.empty() || man.empty())  return;
     
     auto iter = empMap.find(man);
     if (iter == empMap.end()) {
         unordered_set<string> tmpSet;
         tmpSet.insert(emp);
         empMap.insert({man, tmpSet}); 
     } else {
         unordered_set<string> empSet = empMap[man];
         if (empSet.find(emp) == empSet.end()) {
             empMap[man].insert(emp);
         }
     }
     return;
}

vector<string> getReportees(const string &man)
{
    vector<string> emp;
    unordered_map<string, unordered_set<string>>::iterator tmp = empMap.find(man);
    if (tmp != empMap.end()) {
         for (string name : empMap[man]) {
             emp.push_back(name);
         }
    }
    return emp;
}

void printOrgChar(void)
{
    for (auto iter : empMap) {
        string a = iter.first;
        cout << a << " - [";
        unordered_set<string> tmp = iter.second;
        for (auto b : tmp) {
            cout << b << ", ";
            if (empMap.find(b) != empMap.end()) {
                vector<string> c = getReportees(b);
            }
        }
        cout << "]" << "\n";
    }

}

int main(void)
{
    string A[][6] = {
                    { "A", "C" },
                    { "B", "C" },
                    { "C", "F" },
                    { "D", "E" },
                    { "E", "F" },
                    { "F", "F" }
                   };

}
