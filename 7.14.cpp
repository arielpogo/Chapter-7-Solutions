#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

/*
Question wording from the book, my comments are in [brackets]:
7.14 Rewrite heapsort [provided in the text] so that it sorts only items that are in the range low to high, which
are passed as additional parameters
*/

//!!!!NOTE: See 7.56 for a more optimized version of PercolateDown
template <typename T>
void PercolateDown(vector<T>& v, int low, int high, int n) { //builds a max heap
	int af = low - 1; //AdjustmentFactor, since binary heaps start at index 0 we compensate so the equations for children/parents still work

	while ((n-af) * 2 + af <= high) { //while(children)
		if ((n - af) * 2 + 1 + af <= high) { //if right child
			if (v[(n - af) * 2 + 1 + af] > v[(n - af) * 2 + af] && v[n] < v[(n - af) * 2 + 1 + af]) { //if right child greater than left && greater than parent
				swap(v[n], v[(n - af) * 2 + 1 + af]); //swap
				n = (n - af) * 2 + 1 + af; //set index to right child (thus percolating down)
			}
			else if (v[n] < v[(n - af) * 2 + af]) { //otherwise if left if greater than parent (no need to check right child if it DNE)
				swap(v[n], v[(n - af) * 2 + af]); //swap
				n = (n - af) * 2 + af; //set index to left child (thus percolating down)
			}
			else break;
		}
		else if (v[n] < v[(n - af) * 2 + af]) { //otherwise if left if greater than parent (no need to check right child if it DNE)
			swap(v[n], v[(n - af) * 2 + af]); //swap
			n = (n - af)* 2 + af; //set index to left child (thus percolating down)
		}
		else break;
	}
}

template <typename T>
void heapsort(vector<T>& arr, int low, int high) {
	//we percolate down every value in the tree to build a heap, however we skip the bottom most row because it can't percolate down anywhere, thus i=(high-low)/2
	for (int i = (high - low) / 2 + low; i >= low; i--) {
		PercolateDown(arr, low, high, i);
	}

	for (int i = high; i > low; i--) {
		swap(arr[low], arr[i]); //place the highest value at the end
		PercolateDown(arr, low, i-1, low); //we essentially made the heap smaller now, and we percolate the top (low) value down
	}
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
