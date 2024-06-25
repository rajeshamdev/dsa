#include <iostream>
#include <map>
using namespace std;
map<string, int> contactsMap;

void
addName(string name)
{
    for (int i = 1; i <= name.size(); i++) {
        string sub = name.substr(0, i);
        if (contactsMap.find(sub) == contactsMap.end()) contactsMap[sub] = 1;
        else contactsMap[sub]++;
    }
}

int
findPartial(string part)
{
    map<string, int>::iterator iter = contactsMap.find(part);
    if (iter == contactsMap.end()) return 0;
    else return iter->second;
}

int
main(void)
{
    int ops; cin >> ops;
    while(ops--) {
        string opt, name; cin >> opt >> name;
        if (opt == "add") addName(name);
        else if (opt == "find") cout << findPartial(name) << "\n";
    }
}
