#include <iostream>
using namespace std;
#include <math.h>

int coin_flip(double p) {
	double result = (rand() % 1000) / 1000.0;
	return (result < p) ? 1 : 0;
}

double value_spread(double* values, int size, double p) {
	double max_deviation = 0;
	double deviation;
	for (int i = 0; i < size; i++) {
		deviation = abs(values[i] - p);
		if (deviation > max_deviation) max_deviation = deviation;
	}
	return max_deviation;
}

int* zero_array_set(int n) {
	int* result = new int[n];
	memset(result, 0, n * sizeof(int));
	return result;
}

void bernoulli_model() {
	srand((unsigned)time(nullptr));

	double p = 0.5;  // вероятность выпадения решки

	int tests_num = 5;
	int coinflip_num = 1000000;
	int checkpoint = 10;
	int buffer;

	int* tails = zero_array_set(tests_num);
	int* heads = zero_array_set(tests_num);
	int* heads_max = zero_array_set(tests_num);

	double* results = new double[tests_num];

	cout << "number of tests: " << tests_num << "\nexpected result: " << p << "\n\n";

	for (int i = 0; i < coinflip_num; i++) {
		for (int j = 0; j < tests_num; j++) {
			buffer = coin_flip(p);
			tails[j] += buffer;
			if (buffer) {
				heads[j] = 0;
			}
			else if ((++heads[j]) > heads_max[j]) {
				heads_max[j] = heads[j];
			}
		}
		if (i == checkpoint - 1) {	
			cout << "coin flips number: " << checkpoint << "\nresults:";
			for (int k = 0; k < tests_num; k++) {
				results[k] = ((double)tails[k]) / checkpoint;
				cout << "  " << results[k];
			}
			cout << "\nmax series of heads:";
			for (int k = 0; k < tests_num; k++) {
				cout << "  " << heads_max[k];
			}
			buffer = log2(checkpoint);
			cout << "\nvalue spread: " << value_spread(results, tests_num, p) <<
			     "\nmax series expected: " << buffer << "-" << buffer + 1 << "\n\n";
			checkpoint *= 10;
		}
	}
}