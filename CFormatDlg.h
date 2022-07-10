#pragma once

/**
*  A class of a dialog built for collecting parametrs of the binomial distribution in null hypothesis,
* sample size and method of modelling.
*/

class CFormatDlg : public CDialog
{
	DECLARE_DYNAMIC(CFormatDlg)

public:
	CFormatDlg(CWnd* pParent = nullptr);  
	virtual ~CFormatDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	int m_n_par;
	double m_p_par;
	int m_vol_par;
	int m_radio;
};
