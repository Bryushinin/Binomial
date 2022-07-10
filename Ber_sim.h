#pragma once
#include "R64M.hpp"
#include "SampleGenerator.h"
/**
*  A class inheriting SampleGenerator and overriding virtual simulating method with Bernoulli method.
* There is his brother, MOF_sim class that works faster with probabilities far from 0 or 1.
*/
class Ber_sim :
	public SampleGenerator
{
public:
	/// \brief Set parametrs of the distribution with this constructor.
	Ber_sim(int volume1 = 0, int n1 = 0, double p1 = 0) {
		volume = volume1;
		distr.set_m(n1);
		distr.set_p(p1);
		distr.probabilities();
	}
	/// \brief Set the distribution itself with this constructor.
	Ber_sim(Distribution& d, int volume1 = 0)
	{
		volume = volume1;
		distr = d;
		distr.probabilities();
	}
	/// \brief .simulate(volume) writes "volume" realizations of random value of Bin(m,p) in "sample".
	/// \details Realizations will be modelled by Bernoulli method.
	void simulate() override
	{
		delete[] sample;
		sample = new int[volume];
		int k;
		double alpha;
		for (int j = 0; j < volume; ++j)
		{
			k = 0;
			for (int i = 0; i < distr.get_m(); ++i)
			{
				alpha = rnunif();
				k += int(trunc(alpha + distr.get_p()));
			}
			sample[j] = k;
		}
	}
};

