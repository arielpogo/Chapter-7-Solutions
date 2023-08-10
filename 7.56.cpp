#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include<chrono>
using namespace std;

/*
Question from book:
7.56 Consider the following strategy for percolateDown: We have a hole at node X. The
normal routine is to compare X’s children and then move the child up to X if it is
larger (in the case of a (max)heap) than the element we are trying to place, thereby
pushing the hole down; we stop when it is safe to place the new element in the
hole. The alternative strategy is to move elements up and the hole down as far as
possible, without testing whether the new cell can be inserted. This would place
the new cell in a leaf and probably violate the heap order; to fix the heap order,
percolate the new cell up in the normal manner. Write a routine to include this
idea, and compare the running time with a standard implementation of heapsort.
*/

//This is the improved version of PercolateDown
template <typename T>
void PercolateDown(vector<T>& v, int low, int high, int n) { //builds max heap
	int af = low - 1; //AdjustmentFactor, since binary heaps start at index 0 we compensate so the equations for children/parents still work

	while ((n - af) * 2 + af <= high) { //while(children)
		//if right child and right child greater than left child and righ child greater than parent
		if ((n - af) * 2 + 1 + af <= high && v[(n - af) * 2 + 1 + af] > v[(n - af) * 2 + af] && v[n] < v[(n - af) * 2 + 1 + af]) {
			swap(v[n], v[(n - af) * 2 + 1 + af]); //swap with parent
			n = (n - af) * 2 + 1 + af; //move index/"pointer" to right child, thus percolating down
		}
		//otherwise if left child is greater than parent (do not need to compare with right since last if failed, this is the improvement)
		else if (v[n] < v[(n - af) * 2 + af]) { 
			swap(v[n], v[(n - af) * 2 + af]); //swap left child with right child
			n = (n - af) * 2 + af; //move index/"pointer" down to left child, thus percolating down
		}
		else break;
	}
}

//This is the same but without left and right and thus no adjustment factor
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

//See 7.14 for documentation
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
}

//This is the percolate down suggested in the problem, no checks besides array bounds
//My version includes returning the index stopped at
template <typename T>
int AlternatePercolateDown(vector<T>& v, int n) {
	while (n * 2 <= v.size() - 1) {
		swap(v[n], v[n * 2]);
		n *= 2;
		if (n == 0) break;
	}
	return n;
}

//This percolates up values, comparing with their parents
template <typename T>
void PercolateUp(vector<T>& v, int n) {
	int i = n;
	for (; v[i] > v[i / 2]; i /= 2) 
		swap(v[i], v[i / 2]);
}

//See 7.14 for documentation
template <typename T>
void AlternateHeapsort(vector<T>& arr, int low, int high) {
	for (int i = high; i >= low; i--) {
		PercolateUp(arr, AlternatePercolateDown(arr, i)); //Alternative percolate down, then using the index stopped at, percolate it up
	}

	for (int i = high; i > low; i--) {
		swap(arr[low], arr[i]);
		PercolateDown(arr, low, i - 1, low); //we essentially make the heap smaller and smaller, percolating the top value down
	}
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
