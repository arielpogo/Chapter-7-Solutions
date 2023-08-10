#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <chrono>
using namespace std;

void nsquared(vector<int>& v, int k) { //n^2 algorithim: take each number (n), compare to every other number (n). If their sum == k, success. (n*n = n^2)
	int combos = 0;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size(); j++) {
			if (v[i] + v[j] == k) {
				//cout << v[i] << " + " << v[j] << " = " << k << endl;
				combos++;
				break;
			}
		}
	}
	cout << "RESULTS: " << combos << endl;
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
	int h = v.size();
	int m = h / 2;
	
	while (l <= h) {
		if (v[m] == n) return true;
		else if (v[m] < n) {
			l = m + 1;
			m = ((h - l) / 2) + l;
		}
		else {
			h = m - 1;
			m = ((h - l) / 2) + l;
		}
	}
}

void nlogn(vector<int>& v, int k) {//nlogn algorithim: take each number (n), figure out k-num, find if that number is in the vector using binary search (log n) = nlogn
	int combos = 0;
	vector<int> temp = v;
	quicksort(temp);
	for (int i = 0; i < v.size(); i++) {
		int key = k - v[i];
		if (key < 0) continue;
		if (binarySearch(temp, key) == true) {
			//cout << v[i] << " + " << key << " = " << k << endl;
			combos++;
		}
	}
	cout << "RESULTS: " << combos << endl;
}

int main(void) {
	int sum_finding = 6;

	srand(time(NULL)); //rand() seed
	vector<int> input;
	for (int i = 0; i < 10000; i++) input.push_back(rand() % 1000);

	cout << "n^2 results:" << endl;
	auto nsquared_start = std::chrono::high_resolution_clock::now(); //gets the current time
	nsquared(input, sum_finding);
	auto nsquared_end = std::chrono::high_resolution_clock::now(); //gets the current time
	std::chrono::duration<double> nsquared_duration = nsquared_end - nsquared_start;
	cout << "Time: " << nsquared_duration.count() * 1000000 << " microseconds" << endl;

	cout << "--------" << endl;

	cout << "nlogn results:" << endl;
	auto nlogn_start = std::chrono::high_resolution_clock::now(); //gets the current time
	nlogn(input, sum_finding);
	auto nlogn_end = std::chrono::high_resolution_clock::now(); //gets the current time
	std::chrono::duration<double> nlogn_duration = nlogn_end - nlogn_start;
	cout << "Time: " << nlogn_duration.count() * 1000000 << " microseconds" << endl;

	return 0;
}