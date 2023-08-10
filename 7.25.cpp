#include <iostream>
#include <vector>
#include <stdlib.h>
#include<time.h>
#include <cmath>
using namespace std;
#define p 3 //the pivot where we do insertion sort

void insertionSort(vector<int>& v, int left, int right) {
	int lowestIndex = 0;

	for (int i = left; i <= right; i++) {
		lowestIndex = i;
		for (int j = i; j <= right; j++) {
			if (v[j] < v[lowestIndex]) lowestIndex = j;
		}
		swap(v[i], v[lowestIndex]);
	}
}
/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable>
const Comparable& median3(vector<Comparable>& a, int left, int right)
{
    int center = (left + right) / 2;

    if (a[center] < a[left])
        std::swap(a[left], a[center]);
    if (a[right] < a[left])
        std::swap(a[left], a[right]);
    if (a[right] < a[center])
        std::swap(a[center], a[right]);

    // Place pivot at position right - 1
    std::swap(a[center], a[right - 1]);
    return a[right - 1];
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void quicksort(vector<Comparable>& a, int left, int right) {
    if (left + 10 > right) {
        insertionSort(a, left, right); //after pivot is smaller than a certain size
        return;
    }
    else{
        while (left < right) {
            const Comparable& pivot = median3(a, left, right);

            // Begin partitioning
            int i = left, j = right - 1;
            for (; ; ) {
                while (a[++i] < pivot);
                while (pivot < a[--j]);
                if (i < j) swap(a[i], a[j]);
                else break;
            }
            std::swap(a[i], a[right - 1]);  // Restore pivot

            quicksort(a, left, i);
            left = i + 1;
        }
	}
}

/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable>
void quicksort(vector<Comparable>& a)
{
    quicksort(a, 0, a.size() - 1);
}


int main(void) {
	srand(time(NULL)); //rand() seed
	vector<int> input;
	for (int i = 500; i > 0; i--) input.push_back(rand()%255);

	quicksort(input);

    for (int i = 0; i < input.size(); i++) {
        cout << input[i]; //print results
        if (i > 0 && input[i] >= input[i - 1]) cout << " good";
        cout << endl;
    }
	return 0;
}