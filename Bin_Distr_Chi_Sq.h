#pragma once
/**
* A set of functions for modelling random values, uniting states during chi-square computing, calculating p-values.
*/
typedef int (*Method)(int, double);

int Bin_MOF_NE(int m, double p);

int Bin_Ber_NE(int m, double p);

int Bin_MOF_VV(int m, double p);

int Bin_Ber_VV(int m, double p);

void Bin_Distr(int m, double p, double* a);

int Union(int n_distr, int n_sample, double* Exp, int* Freq, double* Out_pr, double* Out_fr);

int Count_p_vals(double alpha, double step, int n_p_values, double* p_values);

void P_value(int n_sample, int n_distr, double p, double& p_value, Method f, int n_dist_0, double p_0);
