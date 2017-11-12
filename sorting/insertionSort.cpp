#include <iostream>


using namespace std;

void insertionSort(int A[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int j = i;
        int temp = A[i];
        while (j > 0 && A[j-1] > temp)
        {
            A[j] = A[j-1];
            --j;
        }
        A[j] = temp;
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

    insertionSort(Array, len);

    cout << "Array after sorting: ";
    for (int i = 0; i < len; i++)
        cout << Array[i] << ", ";
    cout << "\n";
}
