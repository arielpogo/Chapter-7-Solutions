#include <iostream>
#include <vector>
#include <stdlib.h>
#include<time.h>
using namespace std;
#define p 3 //the pivot where we do insertion sort

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

void mergeSort(vector<int>& v) {
	vector<vector<int>> splitV; //a vector of the original vector split up

	//split the vector so each smaller vector is size p
	for (int i = 0; i < 1+((v.size()-1) / p); i++) { //integer ciel division, so 10/3 = 4, 10/4 = 3 etc.
		vector<int> temp;
		for (int j = i*p; j < i*p+p && j < v.size(); j++) {
			temp.push_back(v[j]);
		}
		splitV.push_back(temp);
	}
	
	//sort each smaller chunk
	for (int i = 0; i < splitV.size(); i++) insertionSort(splitV[i]);

	//merge by taking the last two
	vector<int> temp;
	while (splitV.size() > 1) {
		int svs = splitV.size(); //splitV size
		int stl = 0; //second to last vector iterator
		int stl_max = splitV[svs - 2].size(); //stl's limit, the size of the second-to-last vector
		int l = 0; //last vector iterator
		int l_max = splitV[svs - 1].size(); //l's limit, the size of the last vector
		while (stl < stl_max || l < l_max) {
			if ((l < l_max && stl == stl_max) || (l < l_max &&splitV[svs - 1][l] <= splitV[svs - 2][stl]) ) { //second-to-last vector exhuasted or last is lower
				temp.push_back(splitV[svs - 1][l]);
				l++;
			}
			else if ((stl < stl_max && l == l_max) || (stl < stl_max && splitV[svs - 2][stl] <= splitV[svs - 1][l])) { //last vector exhausted or stl is lower
				temp.push_back(splitV[svs - 2][stl]);
				stl++;
			}
		}
		splitV.pop_back(); //remove the two merged
		splitV.pop_back();
		splitV.push_back(temp); //push their merged counterpart
		temp.clear(); //refresh temp
	}
	v = splitV[0];
}

int main(void) {
	srand(time(NULL)); //rand() seed
	vector<int> input;
	for (int i = 1000; i > 0; i--) input.push_back(rand()); //1000 random numbers

	mergeSort(input);

	for(int i = 0; i < input.size(); i++) cout << input[i] << endl; //print results
	return 0;
}