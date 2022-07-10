#pragma once
/**
* A class containing parametrs of the binomial distribution.
*/
class Distribution
{
	int m;
	double p;
	int count;
public:
	int get_m() { return m; }
	void set_m(int m1) { m = m1; this->probabilities();}
	void null_count() { count = 0; }
	double get_p() { return p; }
	void set_p(double p1) { p = p1; this->probabilities();}
	double* expected_prob;
	/// \brief Default constructor will make a Bin(0,0) Distribution object.
	Distribution(int n1 = 1, double p1 = 0.1) : m(n1), p(p1), expected_prob(nullptr) { this->probabilities(); }
	//Distribution(Distribution& d) = delete;
	Distribution(Distribution *d) : m(d->get_m()), p(d->get_p()), expected_prob(nullptr) { this->probabilities(); }
	~Distribution(){delete[] expected_prob;}
	/**
	* Method .probabilities() will write a (m+1) theoretical probability of the Bin(m,p) in the "expected_prob".
	*/
	void probabilities()
	{
		delete[] expected_prob;
		count = -1;
		expected_prob = new double[m + 2];
		while (count <= m)
			expected_prob[count] = (this->next());
	}
	/*void probabilities()
	{
		delete[] expected_prob;
		expected_prob = new double[m + 1];
		double r, c = p / (1. - p);
		r = pow(1. - p, m);
		expected_prob[0] = r;
		for (int i = 1; i <= m; ++i)
		{
			r *= (c * (double(m) - double(i) + 1.) / i);
			expected_prob[i] = r;
		}
	}*/
	double next()
	{
		if (count<0)
		{
			++count;
			return(pow(1. - p, m));
		}
		else
		{
			double c = p / (1. - p);
			++count;
			return(expected_prob[count - 1] * (c * (double(m) - double(count) + 1.) / (double(count))));
		}
	}
	double Nnext(double q, double p0)
	{
		double c = q / (1. - q);
		++count;
		return(p0 * (c * (double(m) - double(count) + 1.) / (double(count))));
	}
};

