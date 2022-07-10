#pragma once
#include "R64M.hpp"
#include "Disrtibution.h"
/**
* An abstract class containing Distribution and built for convenient polymorphism of the modelling methods.
*/
class SampleGenerator
{
protected:
	Distribution distr;
public:
	int* sample;
	int volume;
	/// \brief Method to be overridden by inherits.
	/// \details .simulate(volume) writes "volume" realizations of random value of Bin(m,p) in "sample".
	virtual void simulate() = 0; 
	void set_vol(int vol1)
	{
		volume = vol1;
	}
	SampleGenerator(int volume1 = 0, int n1 = 0, double p1 = 0.)
	{
		distr.set_m(n1);
		distr.set_p(p1);
		sample = nullptr;
		volume = volume1;
		//distr.expected_prob = nullptr;
		distr.probabilities();
	}

	SampleGenerator(SampleGenerator &sg)
	{
		distr.set_m(sg.distr.get_m());
		distr.set_p(sg.distr.get_p());
		volume = sg.volume;
		delete[] sample;
		sample = new int[volume];
		for (int i = 0; i < volume; ++i)
			sample[i] = sg.sample[i];
		//distr.expected_prob = nullptr;
		distr.probabilities();
	}
	virtual ~SampleGenerator() { delete[] sample; }
};

