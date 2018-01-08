#include <bits/stdc++.h>
using namespace std;

string countSort(const string &str)
{
    if (str.empty()) return "";
    vector<int> dict(26, 0);
    auto len = str.size();
    for (char ch: str)
        ++dict[ch-'a'];
    string res;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j <dict[i]; j++)
            res += (i+'a');
    return res;
}

int main(void)
{
    string str = "rajesham";
    cout << "sorted string: " << countSort(str) << "\n";
}
