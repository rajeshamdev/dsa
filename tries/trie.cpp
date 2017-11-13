#include <iostream>
#include <unordered_map>
using namespace std;

struct Trie {
    unordered_map<char, Trie*> siblings;
    bool isEndOfWord;
    Trie() {isEndOfWord = false;}
};

void
insert(Trie* head, string name)
{
    Trie* node = head;
    for (auto ch : name) {
        if (!node->siblings.count(ch)) {
            node->siblings[ch] = new Trie;
        }
        node = node->siblings[ch];
    }
    node->isEndOfWord = true;
}

bool
search(Trie* head, string word)
{
    Trie* node = head;
    for (auto ch: word) {
        if (node->siblings.find(ch) == node->siblings.end()) {
            return false;
        }
        node = node->siblings[ch];
    }
    return node && node->isEndOfWord;
}

int
main(void)
{
    string keys[] = {"the", "a", "there",
                    "answer", "any", "by",
                     "bye", "their" };
    int n = sizeof(keys)/sizeof(keys[0]);
 
    struct Trie *root = new Trie;
    root->isEndOfWord = false;
 
    for (int i = 0; i < n; i++)
        insert(root, keys[i]);

    search(root, "raj") ? cout << "raj found\n" : cout << "raj not found\n";
    search(root, "any") ? cout << "any found\n" : cout << "any not found\n";
    return 0;
}
