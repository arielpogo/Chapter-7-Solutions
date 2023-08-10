#include <iostream>
#include <vector>
#include <stdlib.h>
#include<time.h>
#include <cmath>
using namespace std;
#define p 3 //the pivot where we do insertion sort

/*
Question from book:
Continuing from Exercise 7.25, after part (a),
a. Perform a test so that the smaller subarray is processed by the first recursive call,
while the larger subarray is processed by the second recursive call.
b. Remove the tail recursion by writing a while loop and altering left or right, as
necessary
*/

//See 7.16 for documentation on insertionSort
void insertionSort(vector<int>& v, int left, int right) {
    int lowestIndex = 0;

    for (int i = left; i <= right; i++) {
        lowestIndex = i;
        for (int j = i; j <= right; j++) {
            if (v[j] < v[lowestIndex]) lowestIndex = j;
        }
        swap(v[i], v[lowestIndex]);
    }
}

//This code was directly copied from the book: https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/
/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable>
const Comparable& median3(vector<Comparable>& a, int left, int right)
{
    int center = (left + right) / 2;

    if (a[center] < a[left])
        std::swap(a[left], a[center]);
    if (a[right] < a[left])
        std::swap(a[left], a[right]);
    if (a[right] < a[center])
        std::swap(a[center], a[right]);

    // Place pivot at position right - 1
    std::swap(a[center], a[right - 1]);
    return a[right - 1];
}

//This code was copied from the book, then modified: https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/
/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void quicksort(vector<Comparable>& a, int left, int right) {
    if (left + 5 > right) {
        insertionSort(a, left, right); //after pivot is smaller than a certain size
        return;
    }
    else {
        int ogleft = -1; //original left
        int ogright = -1; //original right
        while (true) {
            int i, j;
            Comparable pivot;

            if (ogleft != -1) { //not first loop, left was sorted, sort right
                right = left - 2;
                left = ogleft;
                ogleft = -1;
                if (right - left > 1)goto sort; //don't sort right twice
                else break;
            }
            if (ogright != -1) { //not first loop, right was sorted, sort left
                left = right + 2;
                right = ogright;
                ogright = -1;
                if (right - left > 1)goto sort; //dont sort left twice
                else break;
            }

            pivot = median3(a, left, right);

            // Begin partitioning
            i = left, j = right - 1;
            for (; ; ) {
                while (a[++i] < pivot);
                while (pivot < a[--j]);
                if (i < j) swap(a[i], a[j]);
                else break;
            }
            std::swap(a[i], a[right - 1]);  // Restore pivot

            if (right - i > i - left) { //if right side smaller, adjust left and right so it's sorted first
                ogright = right;
                right = i - 1;
            }
            else { //else, do the same for left instead
                ogleft = left;
                left = i + 1;
            }
            sort:
                quicksort(a, left, right); //Read the comment on compiler optimization in 7.25
        }
    }
}

//This code was copied from the book: https://users.cs.fiu.edu/~weiss/dsaa_c++4/code/
/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable>
void quicksort(vector<Comparable>& a)
{
    quicksort(a, 0, a.size() - 1);
}


int main(void) {
    srand(time(NULL)); //rand() seed
    vector<int> input;

    for (int j = 0; j < 1000; j++) input.push_back(rand());
    quicksort(input);

    return 0;
}
