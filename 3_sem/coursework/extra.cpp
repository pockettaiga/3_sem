#include <iostream>

#include <math.h>


int* splitting_bets_2(int w, int v_1, int v_2) {  // считаем выигрышные исходы для каждого игрока

	int* result = new int[2];
	result[0] = result[1] = 0;

	int left_1 = w - v_1;
	int left_2 = w - v_2;

	int cases_dim = left_1 + left_2 - 1;         // здесь можно брать число фиктивных партий больше чем n+k-1
	int cases_num = pow(2, cases_dim);

	int temp, game_res, counter_1, counter_2;

	for (int i = 0; i < cases_num; i++) {         // 0 - победа первого игрока, 1 - победа второго игрока
		temp = i;
		counter_1 = counter_2 = 0;

		for (int j = 0; j < cases_dim; j++) {
			game_res = temp & 1;

			if (!game_res) ++counter_1;
			else ++counter_2;

			if (counter_1 == left_1) {
				++result[0];
				break;
			}

			if (counter_2 == left_2) {
				++result[1];
				break;
			}

			temp >>= 1;
		}
	}

	return result;
}