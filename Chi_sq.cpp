#include "pch.h"
#include "Chi_sq.h"

Chi_sq::Chi_sq()/* : d(2, 0.2)*/ {
	/*d.probabilities();
	sample = nullptr;
	ExpectedPr = nullptr;*/
	ExpectedFr = nullptr;
	hist = nullptr;
	k = 0; n = 0; chi_sq = -1.; freedom_degree = -1;
	max_h = -1; max_ex_fr = -1.; p_level = -1.; chi_sq = -1;
}

void Chi_sq::Set_Data(int* sample1, int n1, Distribution &d0)
{
	n = n1; /*d.set_m(d0.get_m()); d.set_p(d0.get_p()); d.probabilities();*/ chi_sq = -1.; freedom_degree = -1;
	max_h = -1; max_ex_fr = -1.; p_level = -1.; k = d0.get_m();

	//sample = sample1;
	delete[] hist;
	delete[] ExpectedFr;
	//delete[] ExpectedPr;
	//ExpectedPr = new double[d.get_m() + 2];
	ExpectedFr = new double[k + 2];
	hist = new int[k + 2];

	delete[] d0.expected_prob;
	d0.expected_prob = nullptr;
	d0.probabilities();
	for (int i = 0; i < k + 1; ++i)
	{
		ExpectedFr[i] = n * d0.expected_prob[i];
		hist[i] = 0;
		/*ExpectedFr[i] = n * ExpectedPr[i];*/
	}
	for (int i = 0; i < n; ++i)
	{
		++hist[sample1[i]];
	}
}

void Chi_sq::Calc_chi_sq()
{
	for (int i = 0; i < k + 1; ++i)
	{
		if (max_h < hist[i])
			max_h = hist[i];
		if (max_ex_fr < ExpectedFr[i])
			max_ex_fr = ExpectedFr[i];
	}
	double* United_pr = new double[k+ 2];
	double* United_fr = new double[k + 2];
	freedom_degree = Union(k, n, ExpectedFr, hist, United_pr, United_fr);
	chi_sq = 0;
	for (int i = 0; i <= freedom_degree; ++i)
		chi_sq += (United_fr[i] - n * United_pr[i]) * (United_fr[i] / (n * United_pr[i]) - 1);
	CHI(1, freedom_degree, chi_sq, p_level);
	delete[] United_fr;
	delete[] United_pr;
}

Chi_sq::~Chi_sq()
{
	delete[] hist;
	delete[] ExpectedFr;
	//delete[] ExpectedPr;
}