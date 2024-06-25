#include <bits/stdc++.h>

using namespace std;

void reverseWords(string &src)
{
    auto len = src.size();
    if (0 == len) return;
    reverse(src.begin(), src.end());
    auto start = 0;
    while (1) {
        while (src[start] == ' ') {
            start++;
        }
        if (src[start] == '\0') break;
        auto end = start;
        while (src[end] != ' ' && src[end] != '\0') {
            ++end;
        }
        reverse(src.begin()+start, src.begin()+end);
        if (src[end] == '\0') break;
        start = end;
    }
}

int main(void)
{
    string str = "   Hello I am testing    ";
    cout << "Before reverse: " << str << "\n";
    reverseWords(str);
    cout << "After reverse: " << str << "\n";
}
