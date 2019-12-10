#if !defined(AFX_SETDLG_H__A5DBA01F_9C45_4179_822A_B9DE7350EA0C__INCLUDED_)
#define AFX_SETDLG_H__A5DBA01F_9C45_4179_822A_B9DE7350EA0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog

class CSetDlg : public CDialog
{
// Construction
public:
	CSetDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CSetDlg)
	enum { IDD = IDD_SETDLG };
	double	m_x1;
	double	m_x2;
	double	m_y1;
	double	m_y2;
	int		m_col;
	int		m_row;
	double	m_A;
	double	m_B0;
	double	m_I;
	double	m_Is;
	int		m_itertime;
	double	m_pre;
	int m_TypeObs;
	double m_IsMorK;
	double	m_Mmin;
	double	m_Mmax;
	CString	m_MOrK;
	CString	m_UnitMOrK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEdita();
	afx_msg void OnKillfocusEditi();
	afx_msg void OnRadiom();
	afx_msg void OnRADIOk();
	afx_msg void OnBUTTONhelp();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETDLG_H__A5DBA01F_9C45_4179_822A_B9DE7350EA0C__INCLUDED_)
