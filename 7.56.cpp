#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include<chrono>
using namespace std;

template <typename T>
void PercolateDown(vector<T>& v, int low, int high, int n) {
	int af = low - 1; //AdjustmentFactor

	while ((n - af) * 2 + af <= high) {
		if ((n - af) * 2 + 1 + af <= high && v[(n - af) * 2 + 1 + af] > v[(n - af) * 2 + af] && v[n] < v[(n - af) * 2 + 1 + af]) {
			swap(v[n], v[(n - af) * 2 + 1 + af]);
			n = (n - af) * 2 + 1 + af;
		}
		else if (v[n] < v[(n - af) * 2 + af]) {
			swap(v[n], v[(n - af) * 2 + af]);
			n = (n - af) * 2 + af;
		}
		else break;
	}
}

template <typename T>
void PercolateDown(vector<T>& v, int n) {
	while (n * 2  <= v.size()-1) {
		if (n * 2 + 1  <= v.size() - 1 && v[n * 2 + 1 ] > v[n * 2 ] && v[n] < v[n * 2 + 1 ]) {
			swap(v[n], v[n * 2 + 1 ]);
			n = n * 2 + 1 ;
		}
		else if (v[n] < v[n * 2 ]) {
			swap(v[n], v[n * 2 ]);
			n = n * 2 ;
		}
		else break;
	}
}

template <typename T>
void heapsort(vector<T>& arr, int low, int high) {
	//BinaryHeap<T> heap(arr, low, high);

	for (int i = (high - low) / 2 + low; i >= low; i--) {
		PercolateDown(arr, low, high, i);
	}

	for (int i = high; i > low; i--) {
		swap(arr[low], arr[i]);
		PercolateDown(arr, low, i - 1, low); //we essentially make the heap smaller and smaller, percolating the top value down
	}

	//for (int i = low; i < high; i++) arr[i] = heap.deleteMin();
}

template <typename T>
int AlternatePercolateDown(vector<T>& v, int n) {
	while (n * 2 <= v.size() - 1) {
		swap(v[n], v[n * 2]);
		n *= 2;
		if (n == 0) break;
	}
	return n;
}

template <typename T>
void PercolateUp(vector<T>& v, int n) {
	int i = n;
	for (; v[i] > v[i / 2]; i /= 2) 
		swap(v[i], v[i / 2]);
	//if (i % 2 == 0 && i + 1 < v.size() - 1 && v[i] < v[i + 1]) swap(v[i], v[i + 1]);
	//if (i > 1 && i % 2 == 1 && v[i] > v[i - 1]) swap(v[i], v[i - 1]);
}

template <typename T>
void AlternateHeapsort(vector<T>& arr, int low, int high) {
	//BinaryHeap<T> heap(arr, low, high);

	for (int i = high; i >= low; i--) {
		PercolateUp(arr, AlternatePercolateDown(arr, i));
	}

	for (int i = high; i > low; i--) {
		swap(arr[low], arr[i]);
		PercolateDown(arr, low, i - 1, low); //we essentially make the heap smaller and smaller, percolating the top value down
	}

	//for (int i = low; i < high; i++) arr[i] = heap.deleteMin();
}

int main(void) {
	srand(time(NULL));

	std::vector<int> v;
	for (int i = 0; i < 10000; i++) v.push_back(rand());

	vector<int> copy = v;

	int start = 0, end = v.size()-1;
	auto s = std::chrono::high_resolution_clock::now(); //gets the current time
	heapsort(copy, start, end);
	auto e = std::chrono::high_resolution_clock::now(); //gets the current time
	std::chrono::duration<double> d = e - s;

	cout << "heapsort: " << d.count() * 1000000 << " microseconds" << endl;

	s = std::chrono::high_resolution_clock::now(); //gets the current time
	AlternateHeapsort(v, start, end);
	e = std::chrono::high_resolution_clock::now(); //gets the current time
	d = e - s;
	cout << "alt heapsort: " << d.count() * 1000000 << " microseconds" << endl;

	return 0;
}