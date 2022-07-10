#include "pch.h"
#include "Histogram.h"
#include "CFormatDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CFormatDlg, CDialog)

CFormatDlg::CFormatDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_n_par(0)
	, m_p_par(0)
	, m_vol_par(0)
	, m_radio(0)
{

}

CFormatDlg::~CFormatDlg()
{
}

void CFormatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_n_par);
	DDX_Text(pDX, IDC_EDIT2, m_p_par);
	DDX_Text(pDX, IDC_EDIT3, m_vol_par);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
}


BEGIN_MESSAGE_MAP(CFormatDlg, CDialog)
END_MESSAGE_MAP()

