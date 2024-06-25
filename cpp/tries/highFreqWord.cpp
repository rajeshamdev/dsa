#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
struct Trie {
    unordered_map<char, Trie*> sibs;
    int count;
    string key;
    Trie(void) : count(0), key("") { }
};

void insert(Trie* &head, string &str)
{
    Trie *temp = head;
    for (char ch : str) {
        if (temp->sibs.find(ch) == temp->sibs.end()) {
            temp->sibs[ch] = new Trie;
        }
        temp = temp->sibs[ch];
    }
    temp->key = str;
    temp->count += 1;
}

void mostFreqWord(Trie *head, int &maxCount, string &word)
{
    if (!head) return;
    Trie *tmp = head;
    for (auto &node : tmp->sibs) {
        if (node.second->count > maxCount) {
            maxCount = node.second->count;
            word = node.second->key; 
        }
        mostFreqWord(node.second, maxCount, word);
    }
}

int main(void)
{
    string arr[] = {"geeks", "for", "geeks", "a", 
                    "portal", "to", "learn", "can", "be", 
                    "computer", "science", "zoom", "yup", 
                    "fire", "in", "be", "data", "geeks" };
    Trie *root = new Trie;
    int numOfWords = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < numOfWords; i++) {
        insert(root, arr[i]); 
    }
    int cnt = 0;
    string word;
    mostFreqWord(root, cnt, word);
    cout << "high frequency word: " << word << ", repeated count : " << cnt << "\n";
    return 0;
}
