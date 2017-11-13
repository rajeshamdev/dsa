#include <iostream>
#include <unordered_map>

using namespace std;
struct Trie {
    unordered_map<char, Trie*> trieMap;
    bool isWord;
    Trie() : isWord(false) {}
};

bool
isPrefix(Trie *trie, string name)
{
    Trie *head = trie;
    bool newWord = false;
    for (char ch : name) {
        if (head->trieMap.find(ch) == head->trieMap.end()) {
            head->trieMap[ch] = new Trie;
            newWord = true;
        }
        head = head->trieMap[ch];
        if (head->isWord == true) return true;
    }
    head->isWord = true;
    if (!newWord) return true;
    return false;
}

int
main(void)
{
    int N; cin >> N;
    Trie *trieRoot = new Trie;
    bool done = false;
    string badstring;
    while (N--) {
        string str; cin >> str;
        if (done) continue;
        if (done = isPrefix(trieRoot, str)) badstring = str;
    }
    if (done) cout << "BAD SET\n" << badstring << "\n";
    else cout << "GOOD SET\n";
    return 0;
}
