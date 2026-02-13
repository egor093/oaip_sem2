#include <iostream>
using namespace std;


void bubbleSort(int a[], int n) {
    int t;
    for (int i = 1; i < n; i++)
        for (int j = n - 1; j >= i; j--)
            if (a[j - 1] > a[j]) {
                t = a[j - 1];
                a[j - 1] = a[j];
                a[j] = t;
            }
}


int getHoarBorder(int A[], int sm, int em) {
    int i = sm - 1, j = em + 1;
    int brd = A[sm], buf;
    while (i < j) {
        do { j--; } while (A[j] > brd);
        do { i++; } while (A[i] < brd);
        if (i < j) {
            buf = A[j];
            A[j] = A[i];
            A[i] = buf;
        }
    }
    return j;
}


void sortHoar(int A[], int sm, int em) {
    if (sm < em) {
        int hb = getHoarBorder(A, sm, em);
        sortHoar(A, sm, hb);
        sortHoar(A, hb + 1, em);
    }
}

int main() {
    setlocale(LC_ALL, ""); 

    const int MAX_SIZE = 100;
    int A[MAX_SIZE], B[MAX_SIZE];
    int n, bSize = 0;

    cout << "Введите количество элементов в массиве A: ";
    cin >> n;

    cout << "Введите элементы массива A:\n";
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    int maxIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (A[i] > A[maxIndex]) {
            maxIndex = i;
        }
    }

    for (int i = maxIndex + 1; i < n; ++i) {
        if (i % 2 == 0) {
            B[bSize++] = A[i];
        }
    }

    bubbleSort(B, bSize);
    cout << "Массив B после пузырьковой сортировки: ";
    for (int i = 0; i < bSize; i++)
        cout << B[i] << " ";
    cout << endl;

    sortHoar(B, 0, bSize - 1);
    cout << "Массив B после быстрой сортировки Хоара: ";
    for (int i = 0; i < bSize; i++)
        cout << B[i] << " ";
    cout << endl;

    return 0;
}
