#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
using namespace std;




vector<int> every_double_sum(vector<int>& v) {
	vector<int> sums;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size(); j++) {
			sums.push_back(v[i] + v[j]);
		}
	}
	return sums;
}

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

void nlogn(vector<int>& v, int k) {
	vector<int> sums = every_double_sum(v);
	quicksort(sums);
	int counter = 0;
	for (int i = 0; i < v.size(); i++) { //compare every single number with every double sum = triple sum
		int key = k - v[i];
		if (key < 0) continue;
		if (binarySearch(sums, key)) {
			cout << "double sum " << key << " and " << v[i] << " equals " << k << endl;
			counter++;
		}
	}
	cout << "Found " << counter << " results!" << endl;
}

int main(void) {
	int sum_finding = 42;
	srand(time(NULL)); //rand() seed
	vector<int> input;

	for (int i = 0; i < 500; i++) input.push_back(rand() % 100);

	nlogn(input, sum_finding);
	
	return 0;
}