#include <iostream>
using namespace std;

void merge(int L[], int lsize, int R[], int rsize, int A[])
{
    int i = 0, j = 0, k = 0;
    while (i < lsize && j < rsize)
        A[k++] = (L[i] <= R[j]) ? L[i++]: R[j++];

    while (i < lsize)
        A[k++] = L[i++];
    while (j < rsize)
        A[k++] = R[j++];
}

void mergeSort(int A[], int size, int *temp)
{
    if (size < 2) return;
    int mid = size/2;
    mergeSort(A, mid, temp);
    mergeSort(A+mid, size-mid, temp);
    merge(A, mid, A+mid, size-mid, temp);
    for (int i = 0; i < size; i++) A[i] = temp[i];
}

int main(void)
{
    int Array[] = { 19, -1, 0, 10, 2, 7, 5};
    int len = sizeof(Array)/sizeof(Array[0]);

    cout << "Array before sorting: ";
    for (int i = 0; i < len; i++)
        cout << Array[i] << ", ";
    cout << "\n";

    int *temp = new int[len];
    mergeSort(Array, len, temp);

    cout << "Array after sorting: ";
    for (int i = 0; i < len; i++)
        cout << Array[i] << ", ";
    cout << "\n";
    delete[] temp;

}
