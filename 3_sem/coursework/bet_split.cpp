#include <iostream>
using namespace std;

#include <math.h>
#include <ctime>
#include <cstdlib>

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

int comb(int n, int k) {
	if (k > n) return 0;
	if (k == n || k == 0) return 1;
	if (k == n - 1 || k == 1) return n;
	return comb(n - 1, k - 1) + comb(n - 1, k);
}


int* bet_split_check(int w, int v_1, int v_2) {  // по формуле из книжки

	int* result = new int[2];

	int left_1 = w - v_1;
	int left_2 = w - v_2;

	int cases_dim = left_1 + left_2 - 1;
	int cases_num = pow(2, cases_dim);

	int container = comb(cases_dim, left_1);
	result[0] = container;

	for (int i = left_1 + 1; i <= cases_dim; i++) {
		container = (cases_dim - i + 1) * container / i;
		result[0] += container;
	}

	result[1] = cases_num - result[0];

	int d = gcd(result[0], result[1]);
	result[0] /= d;
	result[1] /= d;

	return result;
}


int bet_split_play(int n, int m) {  // отыгрыш случайной партии до выигрыша
	if (n == 0) return 1;
	if (m == 0) return 0;
	int res = rand() % 2;
	return bet_split_play(n - res, m - (res ^ 1));
}

void bet_split_model(int w, int v_1, int v_2) {

	srand((unsigned)time(nullptr));

	cout << "games to win: " << w << "\n\n";
	cout << "score: " << v_1 << ":" << v_2 << "\n\n";

	int left_1 = w - v_1;
	int left_2 = w - v_2;

	int iter_num = 1000000;
	int checkpoint = 100;
	int* results = new int[iter_num];
	int wins = 0;

	for (int i = 0; i < iter_num; i++) {

		results[i] = bet_split_play(left_1, left_2);
		wins += results[i];

		if (i == checkpoint - 1) {
			cout << "iterations: " << checkpoint << ", result: " << wins / gcd(wins, checkpoint) << ":"
				<< (checkpoint - wins) / gcd(wins, checkpoint) << " ~ " << (double)wins / checkpoint << "\n\n";
			checkpoint *= 10;
		}
	}

	int* split = bet_split_check(w, v_1, v_2);
	cout << "answer: " << split[0] << ":" << split[1] << " ~ " << (double)split[0] / (split[0] + split[1]) << "\n\n";

	return;
}