#include <bits/stdc++.h>

using namespace std;

class LRUCache {
    private:
        int size;
        list<int> lrucache;
        unordered_map<int, list<int>::iterator> cmap;
    public:
        LRUCache(int s) : size(s) { }

        int get(int k) {
            auto iter = cmap.find(k);
            if (iter == cmap.end())
                return -1;
            lrucache.erase(iter->second); // delete from list.
            lrucache.push_front(k); // bring it to front.
            cmap[k] = lrucache.begin(); // update map.
            return iter->first;
        }

        void put(int k, int v) {
            auto iter = cmap.find(k);
            // if in cache, update and return.
            if (iter != cmap.end()) {
                lrucache.erase(iter->second); // delete from list.
                lrucache.push_front(k); // bring it to front.
                cmap[k] = lrucache.begin(); // update map.
            } else if (lrucache.size() < size) { // not in cache and cache is not full.
                lrucache.push_front(k);
                cmap[k] = lrucache.begin();
            } else { // cache is full.
                lrucache.pop_back(); // evict old entry.
                lrucache.push_front(k);
                cmap[k] = lrucache.begin(); // update map.
            }
        }
};

int main(void)
{
    LRUCache lruCache(10);
}
