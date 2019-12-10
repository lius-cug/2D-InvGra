// MSIDoc.cpp : implementation of the CMSIDoc class
//

#include "stdafx.h"
#include "MSI.h"

#include "MSIDoc.h"
#include "SetDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMSIDoc

IMPLEMENT_DYNCREATE(CMSIDoc, CDocument)

BEGIN_MESSAGE_MAP(CMSIDoc, CDocument)
	//{{AFX_MSG_MAP(CMSIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSIDoc construction/destruction

CMSIDoc::CMSIDoc()
{
	// TODO: add one-time construction code here

	IsReadData=false;
	IsSettings=false;
	
	section.SetSection(0,0,1000,400,1,1);
/*	for(int i=0;i<20;i++)
		for(int j=0;j<40;j++)
			section.SetSection(i+1,j+1,0,exp(-(i-10)*(i-10)/40.0-(j-20)*(j-20)/160.0));
	*/


}

CMSIDoc::~CMSIDoc()
{
}

BOOL CMSIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMSIDoc serialization

void CMSIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMSIDoc diagnostics

#ifdef _DEBUG
void CMSIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMSIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMSIDoc commands

void CMSIDoc::Settings(double x1,double y1,double x2,double y2,int row,int col,double A,double I,double Is)
{
	section.SetSection(x1,y1,x2,y2,row,col);
	section.SetSection(1,Is);         //有效磁化倾角设置
	section.SetSection(7,A);          //测线磁方位角设置
	section.SetSection(8,I);          //地磁倾角设置

}
