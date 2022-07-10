#include "Bin_Distr_Chi_Sq.h"
#include "pch.h"
#include "PROBDIST.h"
#include "R64M.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

typedef int (*Method)(int, double);

using namespace std;

int Bin_MOF_NE(int m, double p)
{
	double q, l, s, t;
	int k = 0;
	if (p > 0.5)
		q = 1. - p;
	else q = p;
	s = pow(1. - q, m);
	t = s;
	l = q / (1 - q);

	double alpha = rnunif();
	while (alpha > s)
	{
		++k;
		t *= (l * (double(m) - k + 1.) / k);
		s += t;
	}
	if (p < 0.5)
		return(k);
	else
		return(m - k);
}

int Bin_Ber_NE(int m, double p)
{
	int k = 0;
	double alpha;
	for (int i = 0; i < m; ++i)
	{
		alpha = rnunif();
		int j = int(trunc(alpha + p));
		k += j;
	}
	return k;
}

int Bin_MOF_VV(int m, double p)
{
	double r, c = p / (1. - p), s;
	int k = 0;
	r = pow(1. - p, m);
	s = r;
	double alpha = rnunif();
	while (alpha > s)
	{
		++k;
		r *= (c * (double(m) - k + 1.) / k);
		s += r;
	}
	return(k);
}

int Bin_Ber_VV(int m, double p)
{
	int k = 0;
	double alpha;
	for (int i = 0; i < m; ++i)
	{
		alpha = rnunif();
		if (alpha < p)
			++k;
	}
	return k;
}

void Bin_Distr(int m, double p, double* a)
{
	double r, c = p / (1. - p);
	r = pow(1. - p, m);
	a[0] = r;
	for (int i = 1; i <= m; ++i)
	{
		r *= (c * (double(m) - i + 1.) / i);
		a[i] = r;
	}
}

int Union(int n_distr, int n_sample, double* Exp_Freq, int* Freq, double* Out_pr, double* Out_fr)
{
	double s =/* n_sample **/ Exp_Freq[0], s_fr = Freq[0]; int m = 0;
	for (int i = 0; i < n_distr; ++i)
	{
		if (s >= 5.)
		{
			Out_pr[m] = s / n_sample;
			Out_fr[m] = s_fr;
			++m;
			s = 0;
			s_fr = 0;
		}
		s += /*n_sample **/ Exp_Freq[i + 1];
		s_fr += Freq[i + 1];
	}

	if (s >= 5.)
	{
		Out_pr[m] = s / n_sample;
		Out_fr[m] = s_fr;
		++m;
	}
	else
	{
		Out_pr[m - 1] += s / n_sample;
		Out_fr[m - 1] += s_fr;
	}
	return(m - 1);
}

int Count_p_vals(double alpha, double step, int n_p_values, double* p_values)
{
	int k = 0;
	for (int i = 0; i < n_p_values; ++i)
		if ((alpha - step) < p_values[i] && p_values[i] < alpha)
			++k;
	return k;
}


void P_value(int n_sample, int n_distr, double p, double& p_value, Method f, int n_dist_0, double p_0)
{
	double* Expected = new double[n_dist_0 + 2];
	Bin_Distr(n_dist_0, p_0, Expected);
	int* Freq = new int[max(n_distr, n_dist_0) + 2];
	for (int i = 0; i <= max(n_distr, n_dist_0); ++i)
		Freq[i] = 0;
	for (int i = 0; i < n_sample; ++i)
		++Freq[f(n_distr, p)];
	double* United_pr = new double[n_dist_0 + 2];
	double* United_fr = new double[max(n_distr, n_dist_0) + 2];
	int freedom = Union(n_dist_0, n_sample, Expected, Freq, United_pr, United_fr);

	double t = 0;
	for (int i = 0; i <= freedom; ++i)
		t += (United_fr[i] - n_sample * United_pr[i]) * (United_fr[i] / (n_sample * United_pr[i]) - 1);
	CHI(1, freedom, t, p_value);
	delete[] Expected;
	delete[] Freq;
	delete[] United_pr;
	delete[] United_fr;
}