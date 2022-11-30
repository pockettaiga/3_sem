#pragma once

int gcd(int a, int b);
int comb(int n, int k);
int* zero_array_set(int n);

//bet_split
int* bet_split_check(int games_to_win, int wins_1, int wins_2);
int bet_split_play(int n, int m);
void bet_split_model(int games_to_win, int wins_1, int wins_2);

//transitivity_paradox
void transitivity_model();

//Bernoulli
int coin_flip(double p);
double value_spread(double* values, int size, double p);
void bernoulli_model();