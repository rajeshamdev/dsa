#include <iostream>
#include <string>

using namespace std;

string strReverse0(string str)
{
    string revStr;
    for (auto iter = str.rbegin(); iter != str.rend(); iter++)
        revStr += *iter;
    return revStr;
}

/* Walks through entire string. Slightly inefficient */
string strReverse1(string str)
{
    string name;
    int len = str.size()-1;
    while (len >= 0) {
        name += str[len--];
    }
    return name;
}

/* Walks through about half size of the string. Better compared to above. */
void strReverse2(string &str)
{
    int len = str.size()-1;
    int i = 0;
    for (int i = 0; i < len; i++, --len) {
         char a = str[i];
         str[i] = str[len];
         str[len] = a;
    }
}

int main(void)
{
    string name = "Veritas interview";
    string name1 = strReverse1(name);
    cout << "Reverse string: " + name1 + "\n";

    strReverse2(name1);
    cout << "Reverse of reverse : " + name1 + "\n";

    name1 = strReverse0(name);
    cout << "Reverse string: " + name1 + "\n";
    name1 = strReverse0(name1);
    cout << "Reverse of reverse: " + name1 + "\n";
}
