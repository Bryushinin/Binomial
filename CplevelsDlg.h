#pragma once

/** 
*  A class of a dialog built for collecting parameters of distributions in hypotheses, significance level,
* sample size and method of modelling Bin(m,p) distribution, size of the sample containing p-values.
*/

class CplevelsDlg : public CDialog
{
	DECLARE_DYNAMIC(CplevelsDlg)

public:
	CplevelsDlg(CWnd* pParent = nullptr);
	virtual ~CplevelsDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	int m_H0_m;
	double m_H0_p;
	int m_H1_m;
	double m_H1_p;
	int m_p_val_sam_size;
	double m_alpha;
	int m_n;
	int m_meth;
};
