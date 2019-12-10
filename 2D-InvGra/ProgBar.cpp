////////////////////////////////////////////////////////////////
// MSDN Magazine -- January 2003
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with VC 6.0 or VS.NET on Windows XP. Tab size=3.
//

#include "StdAfx.h"
#include "afxpriv.h"
#include "ProgBar.h"

#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CProgStatusBar, CStatusBar)
BEGIN_MESSAGE_MAP(CProgStatusBar, CStatusBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

CProgStatusBar::CProgStatusBar()
{
}

CProgStatusBar::~CProgStatusBar()
{
}

/////////////////
// Status bar created: create progress bar too.
//
int CProgStatusBar::OnCreate(LPCREATESTRUCT lpcs)
{
	lpcs->style |= WS_CLIPCHILDREN;
	VERIFY(CStatusBar::OnCreate(lpcs)==0);
	VERIFY(m_wndProgBar.Create(PBS_SMOOTH, CRect(), this, 1));
	m_wndProgBar.SetRange(0,1000);
	return 0;
}

//////////////////
// Status bar was sized: adjust size of progress bar to same as first
// pane (ready message). Note that the progress bar may or may not be
// visible.
//
void CProgStatusBar::OnSize(UINT nType, int cx, int cy)
{
	CStatusBar::OnSize(nType, cx, cy); // call base class
	CRect rc;								  // rectangle 
	GetItemRect(0, &rc);					  // item 0 = first pane, "ready" message
	m_wndProgBar.MoveWindow(&rc,FALSE);// move progress bar
}

//////////////////
// Set progress bar position. pct is an integer from 0 to 100:
//
//  0 = hide progress bar and display ready message (done);
// >0 = (assemed 0-100) set progress bar position
//
// You should call this from your main frame to update progress.
// (See Mainfrm.cpp)
//
void CProgStatusBar::OnProgress(UINT pct)
{
	CProgressCtrl& pc = m_wndProgBar;
	DWORD dwOldStyle = pc.GetStyle();
	DWORD dwNewStyle = dwOldStyle;
	if (pct>0)
		// positive progress: show prog bar
		dwNewStyle |= WS_VISIBLE;
	else
		// prog <= 0: hide prog bar
		dwNewStyle &= ~WS_VISIBLE;

	if (dwNewStyle != dwOldStyle) {
		// change state of hide/show
		SetWindowText(NULL);											// clear old text
		SetWindowLong(pc.m_hWnd, GWL_STYLE, dwNewStyle);	// change style
	}

	// set progress bar position
	pc.SetPos(pct);
	if (pct==0)
		//display MFC idle (ready) message.
		//GetParent()->PostMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
		//GetParent()->PostMessage(WM_SETMESSAGESTRING, AFX_IDS_PREVIEW_CLOSE);
	{
		//CString str="运行结束，迭代10次，拟合观测数据的误差为5%";
		CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		CStatusBar* pStatus = &pFrame->m_wndStatusBar;
		if (pStatus)		 
			pStatus->SetPaneText(0,str); 
	}
}

