#pragma once
#include "MOF_sim.h"
#include "Bin_Distr_Chi_Sq.h"
#include "Chi_sq.h"
#include "PROBDIST.h"
#include "Ber_sim.h"
#include "CFormatDlg.h"
#include "CplevelsDlg.h"
#include "CpowerDlg.h"
class CHistogramDoc : public CDocument
{
protected:
	CHistogramDoc() noexcept;
	DECLARE_DYNCREATE(CHistogramDoc)

public:
	/// \brief It is present for accsess to the "simulate" method.
	SampleGenerator* generator; 
	/// \brief Distribution of the null hypothesis of agreement with the type of distribution.
	Distribution h0; 
	/// \brief Distribution of the alternative hypothesis.
	Distribution h1; 

	/// \brief It is present for convenient calculating of the chi-square and much more. Read comments in "Chi_sq.h" for more.
	Chi_sq CHI_c;	

	/// \brief It is present to remember sample size that user will enter into dialogues.
	int form_n;	
	/// \brief It is present to remember modelling method that user will choose in dialogues.
	int form_radio; 

	/**Current state of the program:
	* 1 - working on histogram,
	* 2 - working on p-levels or power distribution,
	* 3 - working on dependence of the power from the sample size.
	*/
	int cases;

	/// \brief It is present to remember significance level that user will enter into dialogues.
	double p_lev_alpha;  
	/// \brief It is present to remember size of sample containing p-levels that user will enter into dialogues.
	int p_lev_ss; 

	double* p_values;
	/// \brief Values of the power that will be calculated and shown.
	double betas[12]; 
public:

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif

public:
	virtual ~CHistogramDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	void SetSearchContent(const CString& value);
#endif 
public:
	afx_msg void OnFormat();
	afx_msg void Onplevels();
	afx_msg void On32775();
};
