#include "Bin_Distr_Chi_Sq.h"
#include "pch.h"
#include <cstdlib>
#include <string>
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "Histogram.h"
#endif

#include "HistogramDoc.h"
#include "HistogramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CHistogramView, CView)

BEGIN_MESSAGE_MAP(CHistogramView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

CHistogramView::CHistogramView() noexcept
{

}

CHistogramView::~CHistogramView()
{
}

BOOL CHistogramView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void Histogram(CDC* pDC, CRect rc, CHistogramDoc* pDoc)
{
	CPen penAxis;
	penAxis.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = (CPen*)pDC->SelectObject(&penAxis);
	
	int horizontal_start = int(0.05 * rc.Width());
	int vertical_start = int(0.95 * rc.Height());
	pDC->MoveTo(horizontal_start, int(0.05 * rc.Height()));
	pDC->LineTo(horizontal_start, vertical_start);
	pDC->LineTo(int(0.95 * rc.Width()), vertical_start);

	int vert_diap = 0;
	int h_max = pDoc->CHI_c.max_h, count = 0;
	while (!vert_diap)
	{
		h_max = 0; double t = 1.;
		if (count)
			t = 0.8;
		for (int i = 0; i < pDoc->h0.get_m() + 1; ++i)
		{
			pDoc->CHI_c.hist[i] = int(pDoc->CHI_c.hist[i] * t);
			pDoc->CHI_c.ExpectedFr[i] = int(pDoc->CHI_c.ExpectedFr[i] * t);
			if (h_max < pDoc->CHI_c.hist[i] || h_max < pDoc->CHI_c.ExpectedFr[i])
				h_max = max(pDoc->CHI_c.hist[i], int(trunc(pDoc->CHI_c.ExpectedFr[i])));
		}
		vert_diap = int(0.9 * rc.Height() / h_max);
		++count;
	}

	int hor_diap = int(0.9 * rc.Width() / (pDoc->h0.get_m() + 1.));

	pDC->MoveTo(horizontal_start + hor_diap * (pDoc->h0.get_m()), vertical_start + 5);
	pDC->LineTo(horizontal_start + hor_diap * (pDoc->h0.get_m()), vertical_start - 5);

	pDC->TextOut(horizontal_start + hor_diap * (pDoc->h0.get_m()) - 5, vertical_start + 6, L"m");
	pDC->TextOut(horizontal_start - 5, vertical_start + 5, L"0");

	pDC->MoveTo(horizontal_start + 5, vertical_start - h_max * vert_diap);
	pDC->LineTo(horizontal_start - 5, vertical_start - h_max * vert_diap);

	wchar_t* str_max = new wchar_t[9];
	wsprintf(str_max, L"%d", pDoc->CHI_c.max_h);
	pDC->TextOut(horizontal_start - 40, vertical_start - h_max * vert_diap - 10, /*L"max"*/ str_max);
	delete[] str_max;

	int legend = 1;
	if (pDoc->h0.get_p() >= 0.5)
		legend = -1;

	wchar_t* str_cs = new wchar_t[50];
	std::wstring str = (std::to_wstring(pDoc->CHI_c.chi_sq)).substr(0, 5);

	pDC->TextOutW(((0.5 + 0.3 * legend) * rc.Width()), (0.15 * rc.Height()), L"Хи-квадрат: ");
	pDC->TextOutW(int((0.5 + 0.3 * legend) * rc.Width() + 110), int(0.15 * rc.Height()), str.data());

	wsprintf(str_cs, L"Степеней свободы: %d", pDoc->CHI_c.freedom_degree);
	pDC->TextOut(int((0.5 + 0.3 * legend) * rc.Width()), int(0.15 * rc.Height()) + 20, str_cs);

	str = (std::to_wstring(pDoc->CHI_c.p_level)).substr(0, 5);
	pDC->TextOut(int((0.5 + 0.3 * legend) * rc.Width()), int(0.15 * rc.Height()) + 40, L"p-level: ");
	pDC->TextOut(int((0.5 + 0.3 * legend) * rc.Width()) + 60, int(0.15 * rc.Height()) + 40, str.data());
	delete[] str_cs;

	CPen penBars;
	penBars.CreatePen(PS_SOLID, 4, RGB(255, 0, 0));

	CPen penTheory;
	penTheory.CreatePen(PS_SOLID, 6, RGB(0, 187, 255));

	CPen penZero;
	penZero.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	int temp = rc.Width();
	int temp_start = horizontal_start;

	for (int i = 0; i < pDoc->h0.get_m() + 1; ++i)
	{
		if (vert_diap * pDoc->CHI_c.hist[i])
		{
			pDC->SelectObject(&penBars);
			pDC->Rectangle(temp_start, vertical_start - vert_diap * pDoc->CHI_c.hist[i], temp_start + hor_diap, vertical_start);
		}
		else
		{
			pDC->SelectObject(&penZero);
			pDC->MoveTo(temp_start, vertical_start);
			pDC->LineTo(temp_start + hor_diap, vertical_start);
		}
		temp_start += hor_diap;
	}

	temp_start = horizontal_start;

	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = RGB(0, 187, 255);
	logBrush.lbHatch = HS_VERTICAL;
	CBrush brush;

	brush.CreateBrushIndirect(&logBrush);
	pDC->SelectObject(brush);

	for (int i = 0; i < pDoc->h0.get_m() + 1; ++i)
	{
		if (vert_diap * pDoc->CHI_c.ExpectedFr[i])
		{
			pDC->SelectObject(&penTheory);
			pDC->Rectangle(temp_start + 0.3 * hor_diap, vertical_start - vert_diap * pDoc->CHI_c.ExpectedFr[i], temp_start + 0.7 * hor_diap, vertical_start);
		}
		else
		{
			pDC->SelectObject(&penZero);
			pDC->MoveTo(temp_start, vertical_start);
			pDC->LineTo(temp_start + hor_diap, vertical_start);
		}
		temp_start += hor_diap;
	}
}

void P_levels(CDC* pDC, CRect rc, CHistogramDoc* pDoc)
{
	CPen penAxis;
	penAxis.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = (CPen*)pDC->SelectObject(&penAxis);

	int horizontal_start = int(0.05 * rc.Width());
	int vertical_start = int(0.95 * rc.Height());
	pDC->MoveTo(horizontal_start, int(0.05 * rc.Height()));
	pDC->LineTo(horizontal_start, vertical_start);
	pDC->LineTo(int(0.95 * rc.Width()), vertical_start);

	pDC->MoveTo(horizontal_start, vertical_start);
	pDC->LineTo(int(0.8 * rc.Width()), int(0.2 * rc.Height()));
	pDC->LineTo(int(0.9 * rc.Width()), int(0.2 * rc.Height()));

	int vert_diap = int(0.75 * rc.Height()), hor_diap = int(0.75 * rc.Width());

	pDC->MoveTo(horizontal_start + hor_diap, vertical_start + 5);
	pDC->LineTo(horizontal_start + hor_diap, vertical_start - 5);

	pDC->MoveTo(horizontal_start + hor_diap * pDoc->p_lev_alpha, vertical_start + 5);
	pDC->LineTo(horizontal_start + hor_diap * pDoc->p_lev_alpha, vertical_start - 5);

	std::wstring str = (std::to_wstring(pDoc->p_lev_alpha)).substr(0, 5);
	pDC->TextOutW(horizontal_start + hor_diap * pDoc->p_lev_alpha, vertical_start + 15, str.data());

	pDC->TextOut(horizontal_start + hor_diap - 5, vertical_start + 6, L"1");
	pDC->TextOut(horizontal_start - 5, vertical_start + 5, L"0");

	pDC->MoveTo(horizontal_start + 5, vertical_start - vert_diap);
	pDC->LineTo(horizontal_start - 5, vertical_start - vert_diap);

	pDC->TextOut(horizontal_start - 40, vertical_start - vert_diap - 10, L"1");

	CPen penBars;

	if (pDoc->h0.get_m() == pDoc->h1.get_m() && pDoc->h0.get_p() == pDoc->h1.get_p())
	{
		pDC->TextOut(horizontal_start + hor_diap, vertical_start - 0.8 * vert_diap, L"Истинный уровень значимости:");
		penBars.CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
	}
	else
	{
		pDC->TextOut(horizontal_start + hor_diap, vertical_start - 0.8 * vert_diap - 4, L"Мощность:");
		penBars.CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
	}
	pDC->SelectObject(&penBars);

	pDC->MoveTo(horizontal_start, vertical_start);

	double q = 0, step = 0.02, alp = step, beta_ = 0.;
	for (int i = 1; i<int(1 / step + 1); ++i)
	{
		q += double(Count_p_vals(alp, step, pDoc->p_lev_ss, pDoc->p_values)) / pDoc->p_lev_ss;
		if (alp > pDoc->p_lev_alpha && !beta_)
			beta_ = q;
		pDC->LineTo(horizontal_start + int(alp * hor_diap), vertical_start - int(q * vert_diap));
		alp += step;
	}
	pDC->LineTo(int(0.8 * rc.Width()), int(0.2 * rc.Height()));

	str = (std::to_wstring(beta_)).substr(0, 5);
	pDC->TextOutW(horizontal_start + hor_diap, vertical_start - 0.8 * vert_diap + 15, str.data());
}

void Power(CDC* pDC, CRect rc, CHistogramDoc* pDoc)
{
	CPen penAxis;
	penAxis.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = (CPen*)pDC->SelectObject(&penAxis);

	int horizontal_start = int(0.05 * rc.Width());
	int vertical_start = int(0.95 * rc.Height());
	pDC->MoveTo(horizontal_start, int(0.05 * rc.Height()));
	pDC->LineTo(horizontal_start, vertical_start);
	pDC->LineTo(int(0.95 * rc.Width()), vertical_start);

	int vert_diap = int(0.75 * rc.Height()), hor_diap = int(0.75 * rc.Width());

	pDC->TextOut(horizontal_start + hor_diap + 70, vertical_start + 10, L"n");
	pDC->TextOut(horizontal_start - 5, vertical_start + 5, L"0");


	pDC->TextOut(horizontal_start - 50, vertical_start - vert_diap - 140, L"Мощность");
	pDC->TextOut(horizontal_start + 40, vertical_start - vert_diap - 140, L"при уровне значимости");

	std::wstring str = (std::to_wstring(pDoc->p_lev_alpha)).substr(0, 5);
	pDC->TextOutW(horizontal_start + 250, vertical_start - vert_diap - 140, str.data());

	CPen penBars;
	penBars.CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
	pDC->SelectObject(&penBars);
	pDC->MoveTo(0.08 * rc.Width(), vertical_start - pDoc->betas[1] * vert_diap);

	wchar_t* str_ = new wchar_t[9];
	wchar_t* z_ = new wchar_t[9];
	int z = 0;
	for (int j = 1; j < 11; ++j)
	{
		z += 100;
		pDC->LineTo(j * 0.08 * rc.Width(), vertical_start - pDoc->betas[j] * vert_diap);
	}
	z = 0;
	for (int j = 1; j < 11; ++j)
	{
		z += 100;

		std::wstring str = (std::to_wstring(pDoc->betas[j])).substr(0, 5);
		pDC->TextOutW(j * 0.08 * rc.Width(), vertical_start - pDoc->betas[j] * vert_diap - 22, str.data());
		wsprintf(z_, L"%d", z);

		pDC->TextOut(j * 0.08 * rc.Width(), vertical_start + 10, z_);

	}
	delete[] str_;
	delete[] z_;
}

void CHistogramView::OnDraw(CDC* pDC)
{
	CHistogramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rc;
	GetClientRect(&rc);

	switch (pDoc->cases)
	{
	case 1:
	{
		Histogram(pDC, rc, pDoc);
		break;
	}
	case 2:
	{
		P_levels(pDC, rc, pDoc);
		break;
	}
	case 3:
	{
		Power(pDC, rc, pDoc);
		break;
	}
	default: break;
	}
}

void CHistogramView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHistogramView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

#ifdef _DEBUG
void CHistogramView::AssertValid() const
{
	CView::AssertValid();
}

void CHistogramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHistogramDoc* CHistogramView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHistogramDoc)));
	return (CHistogramDoc*)m_pDocument;
}
#endif
