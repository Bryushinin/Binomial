#pragma once
#include "PROBDIST.h"
#include "Disrtibution.h"
#include "Bin_Distr_Chi_Sq.h"
/**
* A class made for convenient calculating of statistics of the chi-square criterion including computing of
* expected probabilities and frequencies, degree of freedom and p-level.
* All fields except "d", "n" and "sample" will be calculated.
*/
class Chi_sq
{
public:
	int k;
	/// \brief Sample size that must be given.
	int n; 
	/// \brief Distribution that must be given. It will provide expected probabilities and frequencies.
	//Distribution d; 
	/// \brief Sample that must be given.
	//int* sample; 
	//double* ExpectedPr;
	double* ExpectedFr;
	/// \brief Empirical frequencies that will be calculated with the sample in basis.
	int* hist;	
	/// \brief The value of statistics of the chi-square criterion that will be calculated.
	double chi_sq; 

	/// \brief Maximum of the empirical frequencies that will be calculated.
	int max_h; 
	/// \brief Maximum of the expected frequencies that will be calculated.
	double max_ex_fr; 

	double p_level; 
	int freedom_degree;

	/// \brief Empty constructor. Fill the data in with the next method.
	Chi_sq();
	/// \brief Method for filling fields that will not be calculated.
	void Set_Data(int* sample1, int n1, Distribution &d0); 

	/// \brief Method that calculates all the other fields.
	void Calc_chi_sq(); 

	~Chi_sq();
};