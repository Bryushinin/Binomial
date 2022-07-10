#pragma once


class CHistogramView : public CView
{
protected: 
	CHistogramView() noexcept;
	DECLARE_DYNCREATE(CHistogramView)

public:
	CHistogramDoc* GetDocument() const;

public:

public:
	virtual void OnDraw(CDC* pDC); 
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

public:
	virtual ~CHistogramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CHistogramDoc* CHistogramView::GetDocument() const
   { return reinterpret_cast<CHistogramDoc*>(m_pDocument); }
#endif

