#pragma once

/**
*  A class of a dialog built for collecting parameters of distributions in hypotheses and significance level.
*/

class CpowerDlg : public CDialog
{
	DECLARE_DYNAMIC(CpowerDlg)

public:
	CpowerDlg(CWnd* pParent = nullptr); 
	virtual ~CpowerDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	int m_H0_m;
	double m_H0_p;
	int m_H1_m;
	double m_H1_p;
	double m_alpha;
};
