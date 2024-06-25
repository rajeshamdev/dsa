class Solution {
public:
    uint32_t reverseBitsV1(uint32_t x)
    {
        int i = 0;
        int j = 31;
        while (i < j) {
            bool a = x&(1<<i);
            bool b = x&(1<<j);
            if (a != b) { // swap only if both ends not same
                x = x^(1 << i); // flip ith bit;
                x = x^(1 << j); // flip jth bit;
            }
            ++i, --j;
        }
        return x;
    }
    
    uint32_t reverseBits(uint32_t x)
    {
        uint32_t m = 0;
        for (int i = 0; i < 32; i++) {
            m <<= 1;
            m |= (x & 1);
            x >>= 1;
        }
        return m;
    }
};
