
Goal: Design algorithm to sort 1TB file on a machine with 1GB main memory.
      The input file contains <Key Value> pairs, duplicates possible.
   Additional info: 
    0. Sort by key.
    1. Key/value are strings.
    2. Disk space is sufficiently large (say 5TB).
    3. Write the sorted data into another file.

Author: Rajesham Gajjela (rajeshamdev@gmail.com).

        Basic Design
       --------------
1. Read 1TB file in chunks of 512MB. As the data is read from disk,
   store into multimap data structure.
   Data struct could be :
       std::multimap<string, string>> kvMap;
   Inserting an element (in this case KV pair) is O(lon N). If we read,
   'M' KV pairs, then the complexity is O(M * log N). Multimap will have
   sorted by keys.

   Another option would be, read into vector, the data structure would be:
       std::vector<pair<string, string>> kvVec;
   Then sort it as:
       std::sort(kvVec.begin(), kv.end();
   This is also O(M*log N).

   Store the sorted vector into a file.

   This results into 1TB/512MB = 1024MB*1024 = 2048 sorted files.

2.
   Open 2048 files. It is assumed that reading 2048 elements in min heap will not exceed
   1GB memory limitation.
   Read one <K V> pair at a time from each file, populate them to list data structture:
   struct ListNode {
       string K;
       string V;
       ofstream chunkedFile; // 500MB file chunk opened for read.
   };
   A min heap is maintained with this list. Top of the min heap is with the smallest
   key. Pop it and write to ondisk file 'fileSorted.txt'. After the pop, use the 'chunkedFile'
   info to read the next element from that file - if this file is empty, it picks up next file
   and so on.

   Step-2 can be abstracted as sorting and merging 'N' lists. The linked code is below.

    struct myStrCmp {
        bool operator()(struct ListNode* l1, struct ListNode* l2)
        {
            return l1->K > l2->K;
        }
    };

    void sortAndMerge(vector<ListNode*> lists)
    {
        auto len = lists.size();
        ofstream sortedFile ("fileSoted.txt"); // open file to write sorted KV pairs.
        if (!sortedFile.is_open())
        {
            cout << "open file failed for fileSorted.txt'\n";
            return;
        }

        priority_queue<ListNode*, vector<ListNode*>, myStrCmp> q; // min heap.
        for (auto i = 0; i < len; i++)
            q.emplace(lists[i]);

        ListNode *next = new (nothrow) ListNode;
        if (nullptr == next) {
            return; // better logging and cleaning up needed.
            sortedFile.close();
        } 
        while (!q.empty()) {
            ListNode *cur= q.top();
            q.pop();
            // write the sorted element to final sorted file.
            sortedFile << cur->K << " " << cur->V << "\n";
            // read the next entry from the just poped entry and push it on to min heap.
            // if this file is empty, proceed to next.
            if (!cur->chunkedFile.eof()) {
                cur->chunkedFile >> next->K;
                cur->chunkedFile >> next->V;
                next->chunkedFile = cur->chunkedFile;
                q.emplace(next);
            }
        }
        sortedFile.close();
        delete next;
    }
