

#include "pch.h"
#include <iostream>
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "Histogram.h"
#endif

#include "HistogramDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CHistogramDoc, CDocument)

BEGIN_MESSAGE_MAP(CHistogramDoc, CDocument)
	ON_COMMAND(ID_FORMAT, &CHistogramDoc::OnFormat)
	ON_COMMAND(ID_p_levels, &CHistogramDoc::Onplevels)
	ON_COMMAND(ID_32775, &CHistogramDoc::On32775)
END_MESSAGE_MAP()


CHistogramDoc::CHistogramDoc() noexcept : form_n(1000),
form_radio(0), cases(0), p_lev_ss(10000),
p_lev_alpha(0.05), /*h0(20, 0.5),*/ h1(20, 0.51)
{
	h0.set_m(20);
	h0.set_p(0.5);
	generator = nullptr;

	h0.probabilities();
	h1.probabilities();

	unsigned long long ti;
	ti = time(0);
	rninit(ti);

	p_values = nullptr;

	for (int i = 1; i < 11; ++i)
		betas[i] = 0;
}

CHistogramDoc::~CHistogramDoc()
{
	delete[] p_values;
}

BOOL CHistogramDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}


void CHistogramDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
		
	}
}

#ifdef SHARED_HANDLERS


void CHistogramDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}


void CHistogramDoc::InitializeSearchContent()
{
	CString strSearchContent;
	
	SetSearchContent(strSearchContent);
}

void CHistogramDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif


#ifdef _DEBUG
void CHistogramDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHistogramDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif


void CHistogramDoc::OnFormat()
{
	CFormatDlg dial;

	dial.m_n_par = h0.get_m();
	dial.m_p_par = h0.get_p();
	dial.m_vol_par = form_n;
	dial.m_radio = form_radio;
	if (dial.DoModal() == IDOK)
	{
		cases = 1;
		h0.set_m(dial.m_n_par);
		h0.set_p(dial.m_p_par);
		h0.probabilities();
		//h1.probabilities();
		form_n = dial.m_vol_par;
		form_radio = dial.m_radio;
		{
			if (h0.get_m() < 1)
			{
				AfxMessageBox(L"Parameter m should be from 1 to 1000 and it has been changed to 1");
				h0.set_m(1);
			}
			if (h0.get_m() > 1000)
			{
				AfxMessageBox(L"Parameter m should be from 1 to 1000 and it has been changed to 1000");
				h0.set_m(1000);
			}
			if (h0.get_p() < 0.)
			{
				AfxMessageBox(L"Parameter p should be from 0 to 1 and it has been changed to 0");
				h0.set_p(0.);
			}
			if (h0.get_p() > 1.)
			{
				AfxMessageBox(L"Parameter p should be from 0 to 1 and it has been changed to 1");
				h0.set_p(1.);
			}
			if (form_n > 1000000)
			{
				AfxMessageBox(L"Sample volume should be from 1 to 1000000 and it has been changed to 1000000");
				form_n = 1000000;
			}
			if (form_n < 1)
			{
				AfxMessageBox(L"Sample volume should be from 1 to 1000000 and it has been changed to 1");
				form_n = 1;
			}
		}
		if (form_radio)
			generator = new Ber_sim(form_n, h0.get_m(), h0.get_p());
		else
			generator = new MOF_sim(form_n, h0.get_m(), h0.get_p());

		generator->simulate();
		CHI_c.Set_Data(generator->sample, form_n, h0);
		CHI_c.Calc_chi_sq();

		delete generator;
		UpdateAllViews(0);
	}
}


void CHistogramDoc::Onplevels()
{
	CplevelsDlg dial;
	dial.m_H0_m = h0.get_m();
	dial.m_H0_p = h0.get_p();
	dial.m_H1_m = h1.get_m();
	dial.m_H1_p = h1.get_p();
	dial.m_alpha = p_lev_alpha;
	dial.m_n = form_n;
	dial.m_meth = form_radio;
	dial.m_p_val_sam_size = p_lev_ss;
	if (dial.DoModal() == IDOK)
	{
		cases = 2;
		h0.set_m(dial.m_H0_m);
		h0.set_p(dial.m_H0_p);
		h1.set_m(dial.m_H1_m);
		h1.set_p(dial.m_H1_p);
		h0.probabilities();
		h1.probabilities();
		p_lev_alpha = dial.m_alpha;
		form_n = dial.m_n;
		form_radio = dial.m_meth;
		p_lev_ss = dial.m_p_val_sam_size;
		{
			if (h0.get_m() < 1)
			{
				AfxMessageBox(L"Parameter m should be from 1 to 1000 and it has been changed to 1");
				h0.set_m(1);
			}
			if (h1.get_m() < 1)
			{
				AfxMessageBox(L"Parameter m should be from 1 to 1000 and it has been changed to 1");
				h1.set_m(1);
			}
			if (h0.get_m() > 1000)
			{
				AfxMessageBox(L"Parameter m should be from 1 to 1000 and it has been changed to 1000");
				h0.set_m(1000);
			}
			if (h1.get_m() > 1000)
			{
				AfxMessageBox(L"Parameter m should be from 1 to 1000 and it has been changed to 1000");
				h1.set_m(1000);
			}
			if (h0.get_p() < 0.)
			{
				AfxMessageBox(L"Parameter p should be from 0 to 1 and it has been changed to 0");
				h0.set_p(0.);
			}
			if (h0.get_p() > 1.)
			{
				AfxMessageBox(L"Parameter p should be from 0 to 1 and it has been changed to 1");
				h0.set_p(1.);
			}
			if (h1.get_p() < 0.)
			{
				AfxMessageBox(L"Parameter p should be from 0 to 1 and it has been changed to 0");
				h1.set_p(0.);
			}
			if (h1.get_p() > 1.)
			{
				AfxMessageBox(L"Parameter p should be from 0 to 1 and it has been changed to 1");
				h1.set_p(1.);
			}
			if (p_lev_alpha < 0.)
			{
				AfxMessageBox(L"Parameter alpha should be from 0 to 1 and it has been changed to 0");
				p_lev_alpha = 0.;
			}
			if (p_lev_alpha > 1.)
			{
				AfxMessageBox(L"Parameter alpha should be from 0 to 1 and it has been changed to 1");
				p_lev_alpha = 1.;
			}
			if (p_lev_ss > 1000000)
			{
				AfxMessageBox(L"Sample volume should be from 1 to 1000000 and it has been changed to 1000000");
				p_lev_ss = 1000000;
			}
			if (p_lev_ss < 1)
			{
				AfxMessageBox(L"Sample volume should be from 1 to 1000000 and it has been changed to 1");
				p_lev_ss = 1;
			}
			if (form_n > 1000000)
			{
				AfxMessageBox(L"Sample volume should be from 1 to 1000000 and it has been changed to 1000000");
				form_n = 1000000;
			}
			if (form_n < 1)
			{
				AfxMessageBox(L"Sample volume should be from 1 to 1000000 and it has been changed to 1");
				form_n = 1;
			}
		}
		delete[] p_values;
		p_values = new double[p_lev_ss + 1];

		if (form_radio)
			generator = new Ber_sim(form_n, h0.get_m(), h0.get_p());
		else
			generator = new MOF_sim(form_n, h0.get_m(), h0.get_p());

		for (int j = 0; j < p_lev_ss; ++j)
		{
			generator->simulate();

			CHI_c.Set_Data(generator->sample, form_n, h1);
			CHI_c.Calc_chi_sq();
			p_values[j] = CHI_c.p_level;
		}
		delete generator;
		UpdateAllViews(0);
	}
}


void CHistogramDoc::On32775()
{
	CpowerDlg dial;
	dial.m_H0_m = h0.get_m();
	dial.m_H0_p = h0.get_p();
	dial.m_H1_m = h1.get_m();
	dial.m_H1_p = h1.get_p();
	dial.m_alpha = p_lev_alpha;
	if (dial.DoModal() == IDOK)
	{
		cases = 3;
		h0.set_m(dial.m_H0_m);
		h0.set_p(dial.m_H0_p);
		h1.set_m(dial.m_H1_m);
		h1.set_p(dial.m_H1_p);
		h0.probabilities();
		h1.probabilities();
		p_lev_alpha = dial.m_alpha;
		{
			if (h0.get_m() < 1)
			{
				AfxMessageBox(L"Parameter m should be from 1 to 1000 and it has been changed to 1");
				h0.set_m(1);
			}
			if (h1.get_m() < 1)
			{
				AfxMessageBox(L"Parameter m should be from 1 to 1000 and it has been changed to 1");
				h1.set_m(1);
			}
			if (h0.get_m() > 1000)
			{
				AfxMessageBox(L"Parameter m should be from 1 to 1000 and it has been changed to 1000");
				h0.set_m(1000);
			}
			if (h1.get_m() > 1000)
			{
				AfxMessageBox(L"Parameter m should be from 1 to 1000 and it has been changed to 1000");
				h1.set_m(1000);
			}
			if (h0.get_p() < 0.)
			{
				AfxMessageBox(L"Parameter p should be from 0 to 1 and it has been changed to 0");
				h0.set_p(0.);
			}
			if (h0.get_p() > 1.)
			{
				AfxMessageBox(L"Parameter p should be from 0 to 1 and it has been changed to 1");
				h0.set_p(1.);
			}
			if (h1.get_p() < 0.)
			{
				AfxMessageBox(L"Parameter p should be from 0 to 1 and it has been changed to 0");
				h1.set_p(0.);
			}
			if (h1.get_p() > 1.)
			{
				AfxMessageBox(L"Parameter p should be from 0 to 1 and it has been changed to 1");
				h1.set_p(1.);
			}
			if (p_lev_alpha < 0.)
			{
				AfxMessageBox(L"Parameter alpha should be from 0 to 1 and it has been changed to 0");
				p_lev_alpha = 0.;
			}
			if (p_lev_alpha > 1.)
			{
				AfxMessageBox(L"Parameter alpha should be from 0 to 1 and it has been changed to 1");
				p_lev_alpha = 1.;
			}
		}
		for (int j = 0; j < 11; ++j)
			betas[j] = 0;
		int z = 0, p_lev_ss_2 = 10000;
		delete[] p_values;
		p_values = new double[p_lev_ss_2 + 1];
		
		generator = new MOF_sim(z, h0.get_m(), h0.get_p());
		for (int j = 1; j < 11; ++j)
		{
			z += 100;
			for (int l = 0; l < p_lev_ss_2; ++l)
			{
				int p_lev_n_ = z;
				generator->set_vol(p_lev_n_);
				generator->simulate();

				CHI_c.Set_Data(generator->sample, p_lev_n_, h1);
				CHI_c.Calc_chi_sq();
				p_values[l] = CHI_c.p_level;

				
			}

			double q = 0, step = 0.02, alp = step, beta_ = 0.;
			for (int i = 1; i<int(1 / step + 1); ++i)
			{
				q += double(Count_p_vals(alp, step, p_lev_ss_2, p_values)) / p_lev_ss_2;
				if (alp > p_lev_alpha && !beta_)
				{
					beta_ = q;
					betas[j] = q;
					break;
				}
				alp += step;
			}

		}
		delete generator;
		UpdateAllViews(0);
	}
}
