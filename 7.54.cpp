#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

/*
Question from the book:
7.54 Repeat Exercise 7.53 for four numbers. Try to design an O(N2 log N) algorithm.
(Hint: Compute all possible sums of two elements. Sort these possible sums. Then
proceed as in Exercise 7.53.)
*/

//Finds the sums of every number plus every other number
vector<int> every_double_sum(vector<int>& v) {
	vector<int> sums;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size(); j++) {
			sums.push_back(v[i] + v[j]);
		}
	}
	return sums;
}

//Adapted from the quicksort in the book: https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/
void quicksort(vector<int>& v) {
	if (v.size() > 1) {
		vector<int> smaller;
		vector<int> equal;
		vector<int> larger;

		int chosenItem = v[v.size() / 2];

		for (int& i : v) {
			if (i < chosenItem) smaller.push_back(move(i));
			else if (i > chosenItem) larger.push_back(move(i));
			else equal.push_back(move(i));
		}

		quicksort(smaller);
		quicksort(larger);

		move(begin(smaller), end(smaller), begin(v));
		move(begin(equal), end(equal), begin(v) + smaller.size());
		move(begin(larger), end(larger), end(v) - larger.size());
	}
}

//standard binarySearch algorithm
bool binarySearch(vector<int>& v, int n) {
	int l = 0;
	int h = v.size() - 1;
	int m = ((h - l) / 2) + l;

	while (l <= h) {
		m = ((h - l) / 2) + l;
		if (v[m] == n) return true;
		else if (v[m] < n) l = m + 1;
		else h = m - 1;
	}
	return false;
}

//Adapted from 7.53
void nlogn(vector<int>& v, int k) {
	vector<int> sums = every_double_sum(v);
	quicksort(sums);
	int counter = 0;

	for (int i = 0; i < sums.size(); i++) {
		int key = k - sums[i];
		if (key < 0) continue;
		if (binarySearch(sums, key)) {
			counter++;
		}
	}
	cout << "Found " << counter << " results!" << endl;
}

int main(void) {
	int sum_finding = 52;
	srand(time(NULL)); //rand() seed
	vector<int> input;
	for (int i = 0; i < 500; i++) input.push_back(rand() % 10000);

	nlogn(input, sum_finding);
	
	return 0;
}
