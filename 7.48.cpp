#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include<cmath>
#include <chrono>
using namespace std;

/*
Question from book, with my comments in [brackets]:
7.48 Write an efficient version of Shellsort and compare performance when the following
increment sequences are used:
a. Shell’s original sequence
b. Hibbard’s increments
c. Knuth’s increments [LaTeX formula]
d. Gonnet’s increments [LaTeX formula]
e. Sedgewick’s increments
*/

//see 7.16 for documentation on insertionSort
void insertionSort(vector<int>& v, int increment) { //increment parameter makes this shell sort
	int lowestIndex = 0;

	for (int i = 0; i < v.size(); i+=increment) {
		lowestIndex = i;
		for (int j = i; j < v.size(); j+=increment) {
			if (v[j] < v[lowestIndex]) lowestIndex = j;
		}
		swap(v[i], v[lowestIndex]);
	}
}

void sss(vector<int>& a){ //shell
	for (int h = a.size() / 2; h > 0; h /= 2) insertionSort(a, h);
}

void ssh(vector<int>& a) { //hibbard
	int k = (int)log2(a.size()); //gets the upper bound for 2^k-1 for an array size k; size 15 gives 3, 2^3-1 = 7, but 16 gives 4, 2^4 - 1 = 15, which is fine.
	for (; k > 0; k--) insertionSort(a, pow(2, k) - 1);
}

void ssk(vector<int>& a) { //knuth
	int i = 1;
	while (0.5 * (pow(3, i) + 1) <= a.size() - 1) i++;
	i--;
	for (; i >= 0; i--) insertionSort(a, 0.5 * (pow(3, i) + 1));
}

void ssg(vector<int>& a) { //gonnet
	for (int h = a.size() / 2.2; h > 0; h /= 2.2) {
		insertionSort(a, h);
		if (h == 2) h = 3; //so h/2.2 = 1
	}
}
void sssedge(vector<int>& a) { //sedgewick
	vector<int> sequence;
	sequence.push_back(1);
	int result = 0;
	for (int i = 1; ; i++) {
		/*
		These formulas are from Wikipedia, which cites the paper from Sedgewick.
		The formulas in the book don't give the sequence provided, or maybe I'm doing something wrong.
		In any case, this does provide the sequence 1, 5, 19, 41, 109,...
		*/

		if (i % 2 == 0) result = 9 * (pow(2, i) - pow(2, i / 2)) + 1; 
		else result = 8 * pow(2, i) - 6 * pow(2,(i+1)/2) + 1;

		if (a.size() > result) sequence.push_back(result);
		else break;
	}
	for(int i = 0; i < sequence.size(); i++) insertionSort(a, sequence[i]);
}

int main(void) {
    vector<int> input;
    srand(time(NULL));

	const int ints = 10000;
    
	for (int i = 0; i < ints; i++) input.push_back(rand());
	auto s = std::chrono::high_resolution_clock::now(); //gets the current time
    sss(input);
	auto e = std::chrono::high_resolution_clock::now(); //gets the current time
	input.clear();
	std::chrono::duration<double> d = e - s;
	cout << "Shell: " << d.count() * 1000 << " miliseconds" << endl;
	cout << "------------------" << endl;
	
	for (int i = 0; i < ints; i++) input.push_back(rand());
	s = std::chrono::high_resolution_clock::now(); //gets the current time
	ssh(input);
	e = std::chrono::high_resolution_clock::now(); //gets the current time
	input.clear();
	d = e - s;
	cout << "Hibbard: " << d.count() * 1000 << " miliseconds" << endl;
	cout << "------------------" << endl;

	for (int i = 0; i < ints; i++) input.push_back(rand());
	s = std::chrono::high_resolution_clock::now(); //gets the current time
	ssk(input);
	e = std::chrono::high_resolution_clock::now(); //gets the current time
	input.clear();
	d = e - s;
	cout << "Knuth: " << d.count() * 1000 << " miliseconds" << endl;
	cout << "------------------" << endl;

	for (int i = 0; i < ints; i++) input.push_back(rand());
	s = std::chrono::high_resolution_clock::now(); //gets the current time
	ssg(input);
	e = std::chrono::high_resolution_clock::now(); //gets the current time
	input.clear();
	d = e - s;
	cout << "Gonnet: " << d.count() * 1000 << " miliseconds" << endl;
	cout << "------------------" << endl;

	for (int i = 0; i < ints; i++) input.push_back(rand());
	s = std::chrono::high_resolution_clock::now(); //gets the current time
	sssedge(input);
	e = std::chrono::high_resolution_clock::now(); //gets the current time
	input.clear();
	d = e - s;
	cout << "Sedgewick: " << d.count() * 1000 << " miliseconds" << endl;

    return 0;
}
