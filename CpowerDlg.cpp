#include "pch.h"
#include "Histogram.h"
#include "CpowerDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CpowerDlg, CDialog)

CpowerDlg::CpowerDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG3, pParent)
	, m_H0_m(0)
	, m_H0_p(0)
	, m_H1_m(0)
	, m_H1_p(0)
	, m_alpha(0)
{

}

CpowerDlg::~CpowerDlg()
{
}

void CpowerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_H0_m);
	DDX_Text(pDX, IDC_H0_p, m_H0_p);
	DDX_Text(pDX, IDC_H1_m, m_H1_m);
	DDX_Text(pDX, IDC_H1_p, m_H1_p);
	DDX_Text(pDX, IDC_alpha, m_alpha);
}


BEGIN_MESSAGE_MAP(CpowerDlg, CDialog)
END_MESSAGE_MAP()

