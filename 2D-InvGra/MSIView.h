// MSIView.h : interface of the CMSIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSIVIEW_H__6F284641_5662_4CF5_B3EC_D9F724D0A4F1__INCLUDED_)
#define AFX_MSIVIEW_H__6F284641_5662_4CF5_B3EC_D9F724D0A4F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SetDlg.h"

class CMSIView : public CView
{
protected: // create from serialization only
	CMSIView();
	DECLARE_DYNCREATE(CMSIView)

// Attributes
public:
	CMSIDoc* GetDocument();
//	UINT m_timerID1;
	CSetDlg setdlg;
	void UpdateImage();
	
private:
	double x1;
	double x2;
	double y1;
	double y2;
	int row;
	int col;
	double A;
	double I;
	double Is;
	int itertime;
	double pre;
	double Msmin;
	double Msmax;

	int typeobs;
	double ismork;
	

	double ToX;
	double ToY;
	double Scale;
	bool IsCheckColorBar;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSIView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMSIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMSIView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnMenuitemSet();
	afx_msg void OnMenuitemStart();
	afx_msg void OnMenuitemZoomin();
	afx_msg void OnMenuitemZoomout();
	afx_msg void OnMenuitemup();
	afx_msg void OnMenuitemdown();
	afx_msg void OnMenuitemright();
	afx_msg void OnMenuitemleft();
	afx_msg void OnMenuitemp();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMenuitemcolorbar();
	afx_msg void OnUpdateMenuitemcolorbar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MSIView.cpp
inline CMSIDoc* CMSIView::GetDocument()
   { return (CMSIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSIVIEW_H__6F284641_5662_4CF5_B3EC_D9F724D0A4F1__INCLUDED_)
