#pragma once
#include "SampleGenerator.h"
#include "R64M.hpp"
/**
*  A class inheriting SampleGenerator and overriding virtual simulating method with inverse function method.
* There is his brother, Ber_sim class that works faster with probabilities close to 0 or 1.
*/
class MOF_sim :
	public SampleGenerator
{
public:
	/// \brief Set parametrs of the distribution with this constructor.
	MOF_sim(int volume1 = 0, int n1 = 0, double p1 = 0) {
		volume = volume1;
		distr.set_m(n1);
		distr.set_p(p1);
		distr.probabilities();
	}
	/// \brief Set the distribution itself with this constructor.
	MOF_sim(Distribution& d, int volume1 = 0)
	{
		volume = volume1;
		distr = d;
		distr.probabilities();
	}

	void simulate() override
	{
		delete[] sample;
		sample = new int[volume];
		double q, l, s, t;
		int k;
		if (distr.get_p() > 0.5)
			q = 1. - distr.get_p();
		else q = distr.get_p();
		for (int j = 0; j < volume; ++j)
		{
			distr.null_count();
			if (distr.get_p() > 0.5)
				s = pow(1. - q, distr.get_m());
			else
				s = distr.expected_prob[0];
			k = 0;
			t = s;
			l = q / (1. - q);

			double alpha = rnunif();
			while (alpha > s)
			{
				++k;
				t = distr.Nnext(q, t);
				s += t;
			}
			if (distr.get_p() < 0.5)
				sample[j] = k;
			else
				sample[j] = distr.get_m() - k;
		}
	}


	/// \brief .simulate(volume) writes "volume" realizations of random value of Bin(m,p) in "sample".
	/// \details Realizations will be modelled by inverse function method.
	/*void simulate() override
	{
		delete[] sample;
		sample = new int[volume];
		double q, l, s, t;
		int k;
		if (distr.get_p() > 0.5)
			q = 1. - distr.get_p();
		else q = distr.get_p();
		for (int j = 0; j < volume; ++j)
		{
			s = pow(1. - q, distr.get_m());
			k = 0;
			t = s;
			l = q / (1. - q);

			double alpha = rnunif();
			while (alpha > s)
			{
				++k;
				t *= (l * (double(distr.get_m()) - k + 1.) / k);
				s += t;
			}
			if (distr.get_p() < 0.5)
				sample[j] = k;
			else
				sample[j] = distr.get_m() - k;
		}
	}*/
};