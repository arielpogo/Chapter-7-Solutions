#include <iostream>
#include <vector>
#include <stdlib.h>
#include<time.h>
using namespace std;

void insertionSort(vector<int>& v) {
	int lowestIndex = 0;

	for (int i = 0; i < v.size(); i++) {
		lowestIndex = i;
		for (int j = i; j < v.size(); j++) {
			if (v[j] < v[lowestIndex]) lowestIndex = j;
		}
		swap(v[i], v[lowestIndex]);
	}
}

int medianOf3(vector<int>& v){
	int size = v.size();
	vector<int> arr;
	arr.push_back(v[0]);
	arr.push_back(v[size/2]);
	arr.push_back(v[size-1]);
	insertionSort(arr);
	return arr[1];
}

void quicksortPatritionAlgorithim(vector<int>& v) {
	int pivot = medianOf3(v);
	cout << "pivot: " << pivot << endl;
	int i = 0, l = 0;
	int j = v.size() - 1, r = j;
	while (i < j) {
		while (v[i] < pivot && i < j) i++;
		while (v[j] > pivot && i < j) j--;
		if (v[i] == pivot) {
			swap(v[i++], v[l++]);
			continue;
		}
		if (v[j] == pivot) {
			swap(v[j--], v[r--]);
			continue;
		}
		else if (i < j) {
			swap(v[i], v[j]);
			continue;
		}
	}

	for (int z = 0; z < v.size(); z++) {
		cout << v[z];
		if (z == i) cout << " <--- i";
		if (z == j) cout << " <--- j";
		if (z == l) cout << " <--- left equal bound";
		if (z == r) cout << " <--- right equal bound";
		cout << endl;
	}
}

int main(void) {
	srand(time(NULL)); //rand() seed
	vector<int> input;
	for (int i = 0; i < 500; i++) input.push_back(rand() % 25);

	quicksortPatritionAlgorithim(input);
	return 0;
}

/*

*/