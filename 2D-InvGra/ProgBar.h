////////////////////////////////////////////////////////////////
// MSDN Magazine -- January 2003
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with VC 6.0 or VS.NET on Windows XP. Tab size=3.
//
#pragma once

//////////////////
// Status bar with progress control.
//
class CProgStatusBar : public CStatusBar {
public:
	CProgStatusBar();
	virtual ~CProgStatusBar();
	CProgressCtrl& GetProgressCtrl() {
		return m_wndProgBar;
	}
	void OnProgress(UINT pct);

protected:
	CProgressCtrl m_wndProgBar;			 // the progress bar
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CProgStatusBar)
public:
	CString str;
};

