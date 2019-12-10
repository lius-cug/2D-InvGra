// MSIDoc.h : interface of the CMSIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSIDOC_H__0D5829FF_1DBA_49C7_96D9_2799ADE99DA2__INCLUDED_)
#define AFX_MSIDOC_H__0D5829FF_1DBA_49C7_96D9_2799ADE99DA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "section.h"


class CMSIDoc : public CDocument
{
protected: // create from serialization only
	CMSIDoc();
	DECLARE_DYNCREATE(CMSIDoc)

// Attributes
public:
	bool IsReadData;
	bool IsSettings;
	CSection section;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMSIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMSIDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void Settings(double x1,double y1,double x2,double y2,int row,int col,double A,double I,double Is);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSIDOC_H__0D5829FF_1DBA_49C7_96D9_2799ADE99DA2__INCLUDED_)
