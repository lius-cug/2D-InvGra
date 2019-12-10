// SetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MSI.h"
#include "SetDlg.h"
#include "math.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog


CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetDlg)
	m_x1 = 0.0;
	m_x2 = 1000.0;
	m_y1 = 0.0;
	m_y2 = 500.0;
	m_col = 40;
	m_row = 20;
	m_A = 0.0;
	m_B0 = 50000.0;
	m_I = 90.0;
	m_Is = 90.0;
	m_itertime = 100;
	m_pre = 0.0;
	m_Mmin = 0.0;
	m_Mmax = 1.0;
	m_MOrK = _T("视密度约束");
	m_UnitMOrK = _T("g/cm^3");
	//}}AFX_DATA_INIT
}


void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDlg)
	DDX_Text(pDX, IDC_EDITx1, m_x1);
	DDX_Text(pDX, IDC_EDITx2, m_x2);
	DDX_Text(pDX, IDC_EDITy1, m_y1);
	DDX_Text(pDX, IDC_EDITy2, m_y2);
	DDX_Text(pDX, IDC_EDITcol, m_col);
	DDV_MinMaxInt(pDX, m_col, 1, 10000);
	DDX_Text(pDX, IDC_EDITrow, m_row);
	DDV_MinMaxInt(pDX, m_row, 1, 10000);
	DDX_Text(pDX, IDC_EDITA, m_A);
	DDV_MinMaxDouble(pDX, m_A, -180., 180.);
	DDX_Text(pDX, IDC_EDITB0, m_B0);
	DDX_Text(pDX, IDC_EDITI, m_I);
	DDV_MinMaxDouble(pDX, m_I, -180., 180.);
	DDX_Text(pDX, IDC_EDITIs, m_Is);
	DDX_Text(pDX, IDC_EDITItertime, m_itertime);
	DDV_MinMaxInt(pDX, m_itertime, 0, 10000);
	DDX_Text(pDX, IDC_EDITpre, m_pre);
	DDV_MinMaxDouble(pDX, m_pre, 0., 10000.);
	DDX_Text(pDX, IDC_EDITMmin, m_Mmin);
	DDX_Text(pDX, IDC_EDITMmax, m_Mmax);
	DDX_Text(pDX, IDC_STATICMorK, m_MOrK);
	DDX_Text(pDX, IDC_STATICUnitMorK, m_UnitMOrK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSetDlg)
	ON_EN_KILLFOCUS(IDC_EDITA, OnKillfocusEdita)
	ON_EN_KILLFOCUS(IDC_EDITI, OnKillfocusEditi)
	ON_BN_CLICKED(IDC_RADIOM, OnRadiom)
	ON_BN_CLICKED(IDC_RADIOk, OnRADIOk)
	ON_BN_CLICKED(IDC_BUTTONhelp, OnBUTTONhelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDlg message handlers

BOOL CSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDC_RADIOdT))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIOM))->SetCheck(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetDlg::OnKillfocusEdita() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	const double pi=3.1415926;
	double tanI,cosA;
	tanI=tan(m_I*pi/180);
	cosA=cos(m_A*pi/180);
	if(m_I>=-90&&m_I<=90)
	{
		if(cosA>=0)m_Is=atan(tanI/cosA)*180/pi;
		else m_Is=180+atan(tanI/cosA)*180/pi;
	}
	else
	{
		if(cosA>=0)m_Is=180+atan(tanI/cosA)*180/pi;	
		else m_Is=atan(tanI/cosA)*180/pi;
	}
	m_Is=int(m_Is*100);
	m_Is=m_Is/100;
	UpdateData(false);
	
}

void CSetDlg::OnKillfocusEditi() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	const double pi=3.1415926;
	double tanI,cosA;
	tanI=tan(m_I*pi/180);
	cosA=cos(m_A*pi/180);
	if(m_I>=-90&&m_I<=90)
	{
		if(cosA>=0)m_Is=atan(tanI/cosA)*180/pi;
		else m_Is=180+atan(tanI/cosA)*180/pi;
	}
	else
	{
		if(cosA>=0)m_Is=180+atan(tanI/cosA)*180/pi;	
		else m_Is=atan(tanI/cosA)*180/pi;
	}
	m_Is=int(m_Is*100);
	m_Is=m_Is/100;
	UpdateData(false);
	
}

void CSetDlg::OnRadiom() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATICB0)->EnableWindow(false);
	GetDlgItem(IDC_EDITB0)->EnableWindow(false);
	GetDlgItem(IDC_STATICunitB0)->EnableWindow(false);
	m_B0=50000;
	m_MOrK = "视磁化强度约束";
	m_UnitMOrK = "10^-3A/m";
	UpdateData(false);
	
}

void CSetDlg::OnRADIOk() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATICB0)->EnableWindow(true);
	GetDlgItem(IDC_EDITB0)->EnableWindow(true);
	GetDlgItem(IDC_STATICunitB0)->EnableWindow(true);
	m_MOrK = "视磁化率约束";
	m_UnitMOrK = "10^-3SI";
	UpdateData(false);
	
}

/////////////////////////////////////////////////////////////////////////////
// CMyAboutDlg dialog used for About
class CMyAboutDlg : public CDialog
{
public:
	CMyAboutDlg();
	enum { IDD = IDD_ABOUTBOX };
};
CMyAboutDlg::CMyAboutDlg() : CDialog(CMyAboutDlg::IDD)
{}
void CSetDlg::OnBUTTONhelp() 
{
	// TODO: Add your control notification handler code here
	CMyAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CSetDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	if(m_x1>=m_x2||m_y1>=m_y2){AfxMessageBox("输入错误");return ;}
	if(m_Mmin>=m_Mmax){AfxMessageBox("输入错误");return ;}
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_RADIOdT))->GetCheck())
		m_TypeObs=0;
	else if(BST_CHECKED==((CButton*)GetDlgItem(IDC_RADIOHax))->GetCheck())
		m_TypeObs=1;
	else if(BST_CHECKED==((CButton*)GetDlgItem(IDC_RADIOZa))->GetCheck())
		m_TypeObs=2;
	else {AfxMessageBox("输入错误");return ;}
	const double pi=3.1415926;
	double cosI=cos(m_I*pi/180);
	double sinA=sin(m_A*pi/180);
	double k=sqrt(1-cosI*cosI*sinA*sinA);
	if(BST_CHECKED==((CButton*)GetDlgItem(IDC_RADIOM))->GetCheck())
		m_IsMorK=1/k;
	else if(BST_CHECKED==((CButton*)GetDlgItem(IDC_RADIOk))->GetCheck())
		m_IsMorK=(4*pi*1E-7)/(m_B0*1E-9)/k;
	else {AfxMessageBox("输入错误");return ;}
	CDialog::OnOK();
}
