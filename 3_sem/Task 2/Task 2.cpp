#include <iostream>
using namespace std;

int array_sum(int* l, int* r) {
	int* p = l;
	int sum = 0;
	while (p <= r) {
		sum += *p;
		++p;
	}
	return sum;
}

void search_max(int* A, int** l, int** r, int n) {
	int curr_sum = array_sum(*l, *r);
	int max_sum = curr_sum;
	int* p1 = *l;
	int* p2 = *r;
	for (int i = 0; i < n; i++) {
		++p2;
		if (curr_sum < 0) {
			p1 = p2;
		}
		curr_sum = array_sum(p1, p2);
		if (curr_sum > max_sum) {
			max_sum = curr_sum;
			(*l) = p1;
			(*r) = p2;
		}
	}
}

void print_index(int* A, int* l, int* r) {
	int count = 0;
	int* p = A;
	while (p) {
		if (p == l)
			cout << "l=" << count << "\n";
		if (p == r) {
			cout << "r=" << count << "\n";
			break;
		}
		++p;
		++count;
	}
}

int main() {
	int n = 11;
	int* A = new int[n] { -1, 10, -7, -1, 12, 3, 1, -24, 17, -2, -5 };
	int* l = A;
	int* r = A;
	search_max(A, &l, &r, n);
	cout << "max sum=" << array_sum(l, r) << "\n";
	print_index(A, l, r);
	
	//delete[] A;

	return 0;
}