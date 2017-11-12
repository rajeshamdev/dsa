#include <iostream>

using namespace std;
void selectionSort(int A[], int size)
{
    for (int i = 0; i < size-2; i++)
    {
        int iMin = i; // keeps track of min element index.
        for (int j = i+1; j < size-1; j++)
        {
            if (A[j] < A[iMin])
                iMin = j;
        }
        if (iMin != i) // swap the elements.
        {
            int temp = A[i];
            A[i] = A[iMin];
            A[iMin] = temp;
        }
    }
}

int main(void)
{
    int Array[] = {9, 6, 16, 0, -1, 17};
    int len = sizeof(Array)/sizeof(Array[0]);

    cout << "Array before sorting: ";
    for (int i = 0; i < len; i++)
        cout << Array[i] << ", ";
    cout << "\n";

    selectionSort(Array, len);

    cout << "Array after sorting: ";
    for (int i = 0; i < len; i++)
        cout << Array[i] << ", ";
    cout << "\n";
}
