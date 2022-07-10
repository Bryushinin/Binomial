#include "pch.h"
#include "Histogram.h"
#include "CplevelsDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CplevelsDlg, CDialog)

CplevelsDlg::CplevelsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
	, m_H0_m(0)
	, m_H0_p(0)
	, m_H1_m(0)
	, m_H1_p(0)
	, m_p_val_sam_size(0)
	, m_alpha(0)
	, m_n(0)
	, m_meth(0)
{

}

CplevelsDlg::~CplevelsDlg()
{
}

void CplevelsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_H0_m, m_H0_m);
	DDX_Text(pDX, IDC_H0_p, m_H0_p);
	DDX_Text(pDX, IDC_H1_m, m_H1_m);
	DDX_Text(pDX, IDC_H1_p, m_H1_p);
	DDX_Text(pDX, IDC_p_val_sam_size, m_p_val_sam_size);
	DDX_Text(pDX, IDC_alpha, m_alpha);
	DDX_Text(pDX, IDC_n, m_n);
	DDX_Radio(pDX, IDC_RADIO2, m_meth);
}


BEGIN_MESSAGE_MAP(CplevelsDlg, CDialog)
END_MESSAGE_MAP()

