#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>
using namespace std;

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

template <typename T>
void heapsort(vector<T>& arr, int low, int high) {
	for (int i = (high - low) / 2 + low; i >= low; i--) {
		PercolateDown(arr, low, high, i);
	}

	for (int i = high; i > low; i--) {
		swap(arr[low], arr[i]);
		PercolateDown(arr, low, i - 1, low);
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

template <typename Comparable>
const Comparable& median5(vector<Comparable>& a, int left, int right)
{
	int size = right - left;

	int b[5] = { left, size / 5 + left, left + size / 2,(3 * size) / 4 + left, right }; //first, second, third (median median), fourth, fifth medians where 1st & 5th are 1st and last

	for (int i = 0; i < 5; i++) {
		for (int j = i+1; j < 5; j++) {
			if (a[b[i]] > a[b[j]]) swap(a[b[i]], a[b[j]]); //every combination (0,1), (0,2), (0,3), (0,4), (0,5), (1,2) etc.
		}
	}

	// Place pivot at position right - 1
	std::swap(a[left+size/2], a[right - 1]);
	return a[right - 1];
}

template <typename Comparable>
const Comparable& first(vector<Comparable>& a, int left, int right)
{
	return a[left];
}

template <typename Comparable>
const Comparable& middle(vector<Comparable>& a, int left, int right)
{
	return a[(left+right)/2];
}

template <typename Comparable>
const Comparable& random(vector<Comparable>& a, int left, int right)
{
	return a[rand() % (right-left) + left];
}



/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void quicksort(vector<Comparable>& a, int left, int right, int cutoff, const Comparable&(*pivotfn)(vector<Comparable>&, int, int)) {
	if (left + cutoff > right) {
		heapsort(a, left, right); //after pivot is smaller than a certain size
		return;
	}
	else if (left == right) return;
	else {
		const Comparable& pivot = pivotfn(a, left, right);
		
		// Begin partitioning
		int i = left, j = right - 1;
		while (i < j) {
			while (i < j && a[++i] < pivot);
			while (i < j && pivot < a[--j]);
			if (i < j) swap(a[i], a[j]);
			else break;
		}
		std::swap(a[i], a[right - 1]);  // Restore pivot

		quicksort(a, left, i - 1, cutoff, pivotfn); //tail recursion removal
		quicksort(a, i+1, right, cutoff, pivotfn); //tail recursion removal
	}
}

int main(void) {
	srand(time(NULL));

	int num_elements = 10000;
	int max_cutoff = 20;

	std::vector<int> og;
	for (int i = 0; i < num_elements; i++) og.push_back(rand());

	auto s = std::chrono::high_resolution_clock::now(); //gets the current time
	auto e = std::chrono::high_resolution_clock::now(); //gets the current time
	std::chrono::duration<double> d = e - s;

	vector<int> copy;
	for (int i = 0; i <= max_cutoff; i++) {
		copy = og;
		s = std::chrono::high_resolution_clock::now();
		quicksort(copy, 0, copy.size() - 1, i, first);
		e = std::chrono::high_resolution_clock::now();
		d = e - s;
		cout << "First with cutoff " << i << " took: " << d.count() * 1000000 << " microseconds" << endl;

		copy = og;
		s = std::chrono::high_resolution_clock::now();
		quicksort(copy, 0, copy.size() - 1, i, middle);
		e = std::chrono::high_resolution_clock::now();
		d = e - s;
		cout << "Middle with cutoff " << i << " took: " << d.count() * 1000000 << " microseconds" << endl;

		copy = og;
		s = std::chrono::high_resolution_clock::now();
		quicksort(copy, 0, copy.size() - 1, i, random);
		e = std::chrono::high_resolution_clock::now();
		d = e - s;
		cout << "Random with cutoff " << i << " took: " << d.count() * 1000000 << " microseconds" << endl;

		copy = og;
		s = std::chrono::high_resolution_clock::now();
		quicksort(copy, 0, copy.size() - 1, i, median3);
		e = std::chrono::high_resolution_clock::now();
		d = e - s;
		cout << "Median3 with cutoff " << i << " took: " << d.count() * 1000000 << " microseconds" << endl;

		copy = og;
		s = std::chrono::high_resolution_clock::now();
		quicksort(copy, 0, copy.size() - 1, i, median5);
		e = std::chrono::high_resolution_clock::now();
		d = e - s;
		cout << "Median5 with cutoff " << i << " took: " << d.count() * 1000000 << " microseconds" << endl;

		cout << "--------------------------------------" << endl;
	}

	cout << "RESULTS FOR IDENTICAL ARRAY, WITH SIZE " << num_elements << endl;
	return 0;
}