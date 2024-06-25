
#include <bits/stdc++.h>

using namespace std;

/**
 *    T(n) = 2T(n-1) + 1
           = 2[2T(n-2) + 1] + 1
           = 2^2 T(n-2) + 2^2 - 1
           = 2^3 T(n-3) + 2^3 - 1
           = 2^k T(n-k) + 2^k - 1
       when (n-k) = 1, T(1) = 1
       then k = n-1

           = 2^(n-1) + 2^(n-1) -1
           = 2^n - 1
 */
void Hanai(const int &n, const char &A, const char &B, const char &C, int &moves)
{
    if (n == 1) {
        ++moves;
        cout << "Step-" << moves << ": move disk 1 from " << A << " to " << B << "\n";
        return;
    }
    Hanai(n-1, A, C, B, moves);
    ++moves;
    cout << "Step-" << moves << ": move disk " << n << " from " << A << " to " << B << "\n";
    
    Hanai(n-1, C, B, A, moves);
}

int main(void)
{
    int moves = 0;
    Hanai(3, 'A', 'B', 'C', moves);
    cout << "Total number of moves: " << moves << "\n";
}
