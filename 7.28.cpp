#include <iostream>
#include <vector>
#include <stdlib.h>
#include<time.h>
using namespace std;

/*
Question from book:
7.28 When implementing quicksort, if the array contains lots of duplicates, it may
be better to perform a three-way partition (into elements less than, equal to,
and greater than the pivot) to make smaller recursive calls. Assume three-way
comparisons.
a. Give an algorithm that performs a three-way in-place partition of an N-element
subarray using only N − 1 three-way comparisons. If there are d items equal
to the pivot, you may use d additional Comparable swaps, above and beyond
the two-way partitioning algorithm. (Hint: As i and j move toward each other,
maintain five groups of elements as shown below):
EQUAL SMALL UNKNOWN LARGE EQUAL
           i       j
*/

//See 7.14 for documentation on insertionSort()
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

//Returns the median on the first, last, and middle element as an approximate median for the whole array
int medianOf3(vector<int>& v){
	int size = v.size();
	vector<int> arr;
	arr.push_back(v[0]);
	arr.push_back(v[size/2]);
	arr.push_back(v[size-1]);
	insertionSort(arr); //this is slow, this is changed in later solutions when I realized
	return arr[1];
}

void quicksortPatritionAlgorithim(vector<int>& v) {
	int pivot = medianOf3(v);
	cout << "pivot: " << pivot << endl;
	int i = 0, l = 0; //l is the boundary of the left side equals group
	int j = v.size() - 1, r = j; //r is the boundary of the right side equals group
	while (i < j) {
		while (v[i] < pivot && i < j) i++; //skip values in the correct side of the pivot
		while (v[j] > pivot && i < j) j--; //ditto
		if (v[i] == pivot) {
			swap(v[i++], v[l++]); //put in left equal group and increment bounds
			continue; //go back and redo the i while loop
		}
		if (v[j] == pivot) { //put in right equal group and increment bounds
			swap(v[j--], v[r--]);
			continue; //go back and redo the j while loop
		}
		else if (i < j) { 
			swap(v[i], v[j]); //swap the values to their correct sides
			continue;
		}
	}

	for (int z = 0; z < v.size(); z++) { //this is just for demonstration/debug
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
