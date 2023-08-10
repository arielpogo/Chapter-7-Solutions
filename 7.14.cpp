#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

template <typename T>
void PercolateDown(vector<T>& v, int low, int high, int n) {
	int af = low - 1; //AdjustmentFactor

	while ((n-af) * 2 + af <= high) {
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
			n = (n - af)* 2 + af;
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
		PercolateDown(arr, low, i-1, low); //we essentially make the heap smaller and smaller, percolating the top value down
	}

	//for (int i = low; i < high; i++) arr[i] = heap.deleteMin();
}

int main(void) {
	srand(time(NULL));

	std::vector<int> v;
	for (int i = 0; i < 100; i++) v.push_back(rand() % 100);

	int start = 20, end = 42;

	heapsort(v, start, end);

	cout << v[0] << endl;
	for (int i = 1; i < v.size(); i++) {
		cout << i << ": " << v[i];
		if (v[i - 1] <= v[i])cout << " ok";
		if (i == start) cout << " <-- Start";
		if (i == end) cout << " <-- End";
		cout << endl;
	}
	return 0;
}