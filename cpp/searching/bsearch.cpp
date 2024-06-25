#include <iostream>
using namespace std;

int bsearch(int A[], int start, int end, int element)
{

    if (start > end) return -1;
    int mid = (start+end)/2;
    if (A[0] == element) return 0;
    if (A[mid] == element) return mid;
    if (A[end] == element) return end;
    if (element < A[mid]) {
        return bsearch(A, start, mid-1, element);
    } else {
        return bsearch(A, mid+1, end, element);
    }

    return -1;
}

int main(void)
{
   int arr[] = {2, 3, 4, 10, 40};
   int n = sizeof(arr)/ sizeof(arr[0]);
   int x = 4;
   int result = bsearch(arr, 0, n-1, x);
   if (result == -1) cout << "Element is not present in array\n";
   else cout << "Element is present at index " << result << "\n";
   return 0;
}
