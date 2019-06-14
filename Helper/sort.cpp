//
// Created by Hengky Sanjaya on 6/13/2019.
//

#include <iostream>
#include <string>

using namespace std;

template<class T>
class Sorting {
public:

    // function to swap
    void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }


    // function merge sort
    void merge(T &arr, int l, int m, int r, string col) {

        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;

        /* create temp arrays */
        T L, R;

        /* Copy data to temp arrays L[] and R[] */
        for (i = 0; i < n1; i++) {
            //cout << i << endl;
            //cout << arr[l+ i].getName() << endl;
            //L[i] = arr[l + i];
            L.push_back(arr[l + i]);
            //cout << L[i].getName() << endl;
        }

        for (j = 0; j < n2; j++) {
            R.push_back(arr[m + 1 + j]);
            //R[j] = arr[m + 1 + j];
        }

        /* Merge the temp arrays back into arr[l..r]*/
        i = 0; // Initial index of first subarray
        j = 0; // Initial index of second subarray
        k = l; // Initial index of merged subarray
        while (i < n1 && j < n2) {

            if (col == "name") {
                string a, b;
                a = L[i].getName();
                b = R[j].getName();

                if (a <= b) {
                    arr[k] = L[i];
                    i++;
                } else {
                    arr[k] = R[j];
                    j++;
                }
                k++;

            } else if (col == "author") {
                string a, b;
                a = L[i].getAuthor();
                b = R[j].getAuthor();

                if (a <= b) {
                    arr[k] = L[i];
                    i++;
                } else {
                    arr[k] = R[j];
                    j++;
                }
                k++;
            } else if (col == "stock") {
                int a, b;
                a = L[i].getStock();
                b = R[j].getStock();

                if (a <= b) {
                    arr[k] = L[i];
                    i++;
                } else {
                    arr[k] = R[j];
                    j++;
                }
                k++;
            }


        }

        /* Copy the remaining elements of L[], if there
           are any */
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        /* Copy the remaining elements of R[], if there
           are any */
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    /* l is for left index and r is right index of the
       sub-array of arr to be sorted */
    void mergeSort(T &arr, int l, int r, string col) {
        if (l < r) {
            // Same as (l+r)/2, but avoids overflow for
            // large l and h
            int m = l + (r - l) / 2;

            // Sort first and second halves
            mergeSort(arr, l, m, col);
            mergeSort(arr, m + 1, r, col);

            merge(arr, l, m, r, col);
        }
    }
};


