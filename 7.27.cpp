#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

/*
Question from the book:
7.27 Suppose the recursive quicksort receives an int parameter, depth, from the driver
that is initially approximately 2 log N.
a. Modify the recursive quicksort to call heapsort on its current subarray if the level
of recursion has reached depth. (Hint: Decrement depth as you make recursive
calls; when it is 0, switch to heapsort.)
b. Prove that the worst-case running time of this algorithm is O(N log N).
c. Conduct experiments to determine how often heapsort gets called.
d. Implement this technique in conjunction with tail-recursion removal in
Exercise 7.25.
e. Explain why the technique in Exercise 7.26 would no longer be needed.
*/

int hsCounter = 0; //Part C

//See 7.14 for documentation on PercolateDown
template <typename T>
void PercolateDown(vector<T>& v, int low, int high, int n) {
	int af = low - 1; //AdjustmentFactor

	while ((n - af) * 2 + af <= high) {
		if ((n - af) * 2 + 1 + af <= high) {
			if (v[(n - af) * 2 + 1 + af] > v[(n - af) * 2 + af] && v[n] < v[(n - af) * 2 + 1 + af]) {
				swap(v[n], v[(n - af) * 2 + 1 + af]);
				n = (n - af) * 2 + 1 + af;
			}
			else if (v[n] < v[(n - af) * 2 + af]) {
				swap(v[n], v[(n - af) * 2 + af]);
				n = (n - af) * 2 + af;
			}
			else break;
		}
		else if (v[n] < v[(n - af) * 2 + af]) {
			swap(v[n], v[(n - af) * 2 + af]);
			n = (n - af) * 2 + af;
		}
		else break;
	}
}

//See 7.14 for documentation on heapsort()
template <typename T>
void heapsort(vector<T>& arr, int low, int high) {
	hsCounter++;

	for (int i = (high - low) / 2 + low; i >= low; i--) {
		PercolateDown(arr, low, high, i);
	}

	for (int i = high; i > low; i--) {
		swap(arr[low], arr[i]);
		PercolateDown(arr, low, i - 1, low);
	}
}

//Code copied from book: https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/
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

//Code copied from book and then modified. https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/
/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void quicksort(vector<Comparable>& a, int left, int right, const int depth) {
	if (depth == 0) {
		heapsort(a, left, right); //after pivot is smaller than a certain size
		return;
	}
	else {
		while (left < right) {
			const Comparable& pivot = median3(a, left, right);

			// Begin partitioning
			int i = left, j = right - 1;
			while(i < j ) {
				while (a[++i] < pivot);
				while (pivot < a[--j]);
				if (i < j) swap(a[i], a[j]);
				else break;
			}
			std::swap(a[i], a[right - 1]);  // Restore pivot

			quicksort(a, left, i-1, depth - 1); //tail recursion removal
			left = i + 1;
		}
	}
}

//Copied from book: https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/
/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable>
void quicksort(vector<Comparable>& a)
{
	quicksort(a, 0, a.size() - 1);
}

int main(void) {
	srand(time(NULL));
	int depth = 5;

	std::vector<int> v;
	vector<int> calls;
	for(int j = 0; j < 10000; j++){//10k tests on 100 num vectors
		for (int i = 0; i < 100; i++) v.push_back(rand());
		quicksort(v, 0, v.size() - 1, depth);
		calls.push_back(hsCounter);
		hsCounter = 0;
		v.clear();
	}
	heapsort(calls, 0, calls.size() - 1);
	cout << "for a depth " << depth << endl;
	cout << "least calls: " << calls[0] << " most: " << calls[calls.size() - 1] << " median: " << calls[calls.size()/2];
	
	/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	7.27 e) The optimization in 7.26 caps the number of recursive calls by guaranteeing calls to the smaller array first, eventually hitting the limit.
	The optimization made here caps the number of recursive calls by the depth integer instead.
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

	return 0;
}
