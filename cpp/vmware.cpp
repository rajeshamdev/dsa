#include <bits/stdc++.h>

using namespace std;

struct iovec {
    void *base;
    size_t len;
};

// Basic idea: Since iovec is sorted by 'base' address,
// we just need to walk leanearly and find the adjancent vecs.
// Keep track of index 'last' where we are accumulating all adjacent
// iovecs. If the 'base' of last index is not same as current, then
// proceed to next iovec.
int coalesce(struct iovec *iov, int numElem)
{
    if (nullptr == iov || 0 == numElem) return 0;
    if (1 == numElem) return numElem;

    auto i = 1;
    auto last = 0;
    // coalesce adjacent iovecs.
    while (i < numElem) {
        // accumulate adjacent iovec into 'last'
        if (iov[last].base + iov[last].len == iov[i].base) {
            iov[last].len += iov[i].len;
            iov[i].base = 0, iov[i].len = 0;
        } else {
            last = i;
        }
        ++i;
    }

    i = 0;
    auto count = 0;
    // get hold off iov with len zero, then walk until a valid
    // vec. then compact them. This code is slightly messy.
    while (i < numElem) {
        if (iov[i].len != 0) { // 
            i++, count++; continue;
        }
        auto j = i+1;
        while (j < numElem) {
            if (iov[j].len == 0) {
                j++; continue;
            } else {
                iov[i] = iov[j];
                iov[j].base = 0;
                iov[j].len = 0;
                ++i, count++;
                break;
            }
        }
        ++i;
    }
    cout << "count: " << count << "\n";
    return count;
}

int main(void)
{
    struct iovec iov[6] = {
        {(void*)0x1000, 0x200},
        {(void*)0x1200, 0x100},
        {(void*)0x1600, 0x100},
        {(void*)0x1700, 0x200},
        {(void*)0x1800, 0x200},
        {(void*)0x2100, 0x200}};

    auto res = coalesce(iov, 6);
}
