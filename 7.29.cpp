#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

/*
Question from book, with my comments in [brackets]
7.29 Write a program to implement the selection algorithm [mentioned in the book, section 7.7.6].
*/

//See 7.16 for documentation on insertionSort
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

//Copied from the book: https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/
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

//Quicksort copied from the book then modified into quickselect: https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/
/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
Comparable quickselect(vector<Comparable>& a, int left, int right, int k) {
	if (left + 10 <= right) {
		insertionSort(a, left, right);
		return a[k-1]; //return the kth value
	}
	else {
		const Comparable& pivot = median3(a, left, right);

		// Begin partitioning
		int i = left, j = right - 1;
		for (;; ) {
			while (a[++i] < pivot);
			while (pivot < a[--j]);
			if (i < j) swap(a[i], a[j]);
			else break;
		}
		std::swap(a[i], a[right - 1]);  // Restore pivot

		//this is the change from quicksort
		if(k <= i) quickselect(a, left, i-1,k); //quickselect (aka quicksort) the left array, if the kth value in the left array
		else if(k > i + 1) quickselect(a, i+1, right, k); //quickselect the right array, if the kth value is in the right array
	}
}

//Copied from the book: https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/
/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable>
Comparable quickselect(vector<Comparable>& a, int k)
{
	return quickselect(a, 0, a.size() - 1, k);
}

int main(void) {
	srand(time(NULL));
	std::vector<int> v;

	int k = 5;

	for (int i = 0; i < 100; i++) v.push_back(rand());

	cout << k << "th smallest is: " << quickselect(v, k) << endl;
	insertionSort(v, 0, v.size() - 1);
	cout << "verification from sorting: " << v[k - 1] << endl;

	return 0;
}
