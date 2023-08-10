#include <iostream>
#include <vector>
#include <time.h>
#include <random>
using namespace std;

template <typename T>
void quicksort(vector<T>& v) {
	if (v.size() > 1) {
		vector<T> smaller;
		vector<T> equal;
		vector<T> larger;

		T chosenItem = v[v.size() / 2];

		for (T& i : v) {
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

class point {
public:
    int x;
    int y;
    point(int a = 0, int b = 0) {
        x = a;
        y = b;
    }
};

double slope(point a, point b) {
    return (a.y - b.y) / (double)(a.x - b.x);
}

class pointSlopeCombo {
public:
	point* pt;
	double slope;
	pointSlopeCombo(point* p, double s) {
		pt = p;
		slope = s;
	}
};

bool operator>(const pointSlopeCombo& a, const pointSlopeCombo& b) {
	return (a.slope > b.slope);
}
bool operator<(const pointSlopeCombo& a, const pointSlopeCombo& b) {
	return (a.slope < b.slope);
}

void findcolinear(vector<point> pts) {
    vector<pointSlopeCombo> slopes;
	//for each point
    for (int i = 0; i < pts.size(); i++) {
		//produce a point - slope combo with every other point
        for (int j = 0; j < pts.size(); j++) {
            if (i == j) continue;
            slopes.push_back(pointSlopeCombo(&pts[j], slope(pts[i], pts[j])));
        }

		//sort the slopes, by slope (defined in the operator section)
		quicksort(slopes);

		//print out when there are 3+ in a row which have the same slope
		int colinearityCounter = 0;
		double colinearitySlope = slopes[0].slope;
		const int slopesSize = slopes.size();
		for (int z = 0; z < slopesSize + 1; z++) { //dont want to count the 0th one twice, and if the last element is colinear with 3+ it will print too
			if (z < slopesSize && slopes[z].slope == colinearitySlope) {
				colinearityCounter++;
				continue;
			}
			else if (colinearityCounter >= 3) { //point we're counting is counted too
				cout << "Co-linear points: (" << pts[i].x << ", " << pts[i].y << ")";
				for (; colinearityCounter > 0; colinearityCounter--) cout << " (" << slopes[z-colinearityCounter].pt->x << ", " << slopes[z-colinearityCounter].pt->y << ")";
				cout << endl;
			}
			if(z < slopesSize) colinearitySlope = slopes[z].slope;
			colinearityCounter = 0;
		}
		slopes.clear();
    }
}

int main() {
    srand(time(NULL));
    vector<point> points;

    for (int i = 0; i < 10; i++) points.push_back(point(i,i));

    findcolinear(points);
	cout << "Some results may be repeated, but in a different order." << endl;
    return 0;
}
