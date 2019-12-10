// MSIView.cpp : implementation of the CMSIView class
//

#include "stdafx.h"
#include "MSI.h"

#include "MSIDoc.h"
#include "MSIView.h"
#include "Resource.h"
#include "SetDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSIView

IMPLEMENT_DYNCREATE(CMSIView, CView)

BEGIN_MESSAGE_MAP(CMSIView, CView)
//{{AFX_MSG_MAP(CMSIView)
ON_WM_TIMER()
ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_MENUITEM_SET, OnMenuitemSet)
	ON_COMMAND(ID_MENUITEM_START, OnMenuitemStart)
	ON_COMMAND(ID_MENUITEM_ZOOMIN, OnMenuitemZoomin)
	ON_COMMAND(ID_MENUITEM_ZOOMOUT, OnMenuitemZoomout)
	ON_COMMAND(ID_MENUITEMUP, OnMenuitemup)
	ON_COMMAND(ID_MENUITEMDOWN, OnMenuitemdown)
	ON_COMMAND(ID_MENUITEMRIGHT, OnMenuitemright)
	ON_COMMAND(ID_MENUITEMLEFT, OnMenuitemleft)
	ON_COMMAND(ID_MENUITEMP, OnMenuitemp)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_MENUITEMCOLORBAR, OnMenuitemcolorbar)
	ON_UPDATE_COMMAND_UI(ID_MENUITEMCOLORBAR, OnUpdateMenuitemcolorbar)
	//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSIView construction/destruction


CMSIView::CMSIView()
{
	// TODO: add construction code here
   	//m_timerID1 = this->SetTimer(24,500,NULL);
	ToX=0;
	ToY=0;
	Scale=0;
	IsCheckColorBar=false;
}

CMSIView::~CMSIView()
{
	//KillTimer(m_timerID1);
}

BOOL CMSIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMSIView drawing

void CMSIView::OnDraw(CDC* pDC)
{
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	CRect rect; 
	GetClientRect(&rect);
	pDoc->section.Draw(pDC,rect,pDoc->IsReadData,pDoc->IsSettings);	
	//pDoc->section.Draw(pDC,rect,true,true);	
}

/////////////////////////////////////////////////////////////////////////////
// CMSIView printing

BOOL CMSIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMSIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMSIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMSIView diagnostics

#ifdef _DEBUG
void CMSIView::AssertValid() const
{
	CView::AssertValid();
}

void CMSIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMSIDoc* CMSIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSIDoc)));
	return (CMSIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMSIView message handlers

void CMSIView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	// Invalidate();  
/*	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(rect);*/
	CView::OnTimer(nIDEvent);
}

void CMSIView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	//m_timerID1 = this->SetTimer(24,1000,NULL);
}

BOOL CMSIView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return true;
//	return CView::OnEraseBkgnd(pDC);
}



void CMSIView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CFileDialog inFileDialog(true,NULL,NULL,OFN_HIDEREADONLY,"Dat File(*.dat)|*.dat|All File(*.*)|*.*||") ;
	inFileDialog.m_ofn.lpstrTitle = "打开观测数据";
	if (inFileDialog.DoModal ()==IDOK)
	{
		CString m_infile=inFileDialog.GetPathName ();	
		if(pDoc->section.ReadData(m_infile)==true)
		{
			pDoc->section.OffsetX=0;
			pDoc->section.OffsetY=0;
			pDoc->IsReadData=true;
			Invalidate(true);
		}
	}
	
}


void CMSIView::OnMenuitemSet() 
{
	// TODO: Add your command handler code here
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(setdlg.DoModal()==IDOK)
	{
		x1=setdlg.m_x1;
		x2=setdlg.m_x2;
		y1=setdlg.m_y1;
		y2=setdlg.m_y2;
		row=setdlg.m_row;
		col=setdlg.m_col;
		A=setdlg.m_A;
		I=setdlg.m_I;
		Is=setdlg.m_Is;
		itertime=setdlg.m_itertime;
		pre=setdlg.m_pre;
		typeobs=setdlg.m_TypeObs;
		ismork=setdlg.m_IsMorK;
		Msmin=setdlg.m_Mmin;
		Msmax=setdlg.m_Mmax;

		pDoc->Settings(x1,y1,x2,y2,row,col,A,I,Is);
		pDoc->IsSettings=true;
		Invalidate(true);
	}
}
void CMSIView::OnMenuitemStart() 
{
	// TODO: Add your command handler code here
	
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->IsReadData==false)
	{
		AfxMessageBox("没有读入观测数据！");
		return;
	}
	if(pDoc->IsSettings==false)
	{
		AfxMessageBox("没有进行参数设置！");
		return;
	}
	pDoc->section.IsMorK=ismork;
	///////////////
	HCURSOR hCursor;
	hCursor=::LoadCursor(NULL,IDC_WAIT);
	::SetCursor(hCursor);
	////////////////
	pDoc->section.PCGM(Msmin,Msmax,itertime,pre,typeobs);
	/////////////////
	hCursor=::LoadCursor(NULL,IDC_ARROW);
	::SetCursor(hCursor);
	///////////////
	Invalidate(true);

	/*CDike2D dike(2.6,0,
		          450,150,
				  50,50,
				  0,0,0);
	/*CDike2D::CDike2D(const double C_Ms, const double C_Is,
				 const double C_x0, const double C_z0,
				 const double C_b, const double C_l,
				 const double C_alpha,const double C_A,
				 const double C_I)*/
/*	FILE *fp=fopen("temp.txt","w");
	for(int i=0;i<51;i++)
		fprintf(fp,"%.2f %.5f\n",i*20.0,dike.Cal_delta_T(i*20.0,0));
	fclose (fp);
*/

}

void CMSIView::OnMenuitemZoomin() 
{
	// TODO: Add your command handler code here
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->section.Scale*=1.1;
	Invalidate(true);
	
}

void CMSIView::OnMenuitemZoomout() 
{
	// TODO: Add your command handler code here
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->section.Scale*=0.9;
	Invalidate(true);
}

void CMSIView::OnMenuitemup() 
{
	// TODO: Add your command handler code here
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->section.OffsetY+=50;
	Invalidate(true);
	
}

void CMSIView::OnMenuitemdown() 
{
	// TODO: Add your command handler code here
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->section.OffsetY-=50;
	Invalidate(true);
}

void CMSIView::OnMenuitemright() 
{
	// TODO: Add your command handler code here

	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->section.OffsetX-=50;
	Invalidate(true);
}

void CMSIView::OnMenuitemleft() 
{
	// TODO: Add your command handler code here
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->section.OffsetX+=50;
	Invalidate(true);
	
}

void CMSIView::OnMenuitemp() 
{
	// TODO: Add your command handler code here
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->section.OffsetX=0;
	pDoc->section.OffsetY=0;
	pDoc->section.Scale=1.0;
	Invalidate(true);
}

void CMSIView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMSIView::OnMenuitemSet();
	CView::OnLButtonDblClk(nFlags, point);
}



///////////////////////////////////////////

BOOL SaveBitmapToFile(HBITMAP hBitmap, LPCTSTR lpFileName ) 
{ 
	HDC hDC; //设备描述表 
	int iBits; //当前显示分辨率下每个像素所占字节数 
	WORD wBitCount; //位图中每个像素所占字节数 
	DWORD dwPaletteSize=0, //定义调色板大小， 位图中像素字节大小 ，位图文件大小 ， 写入文件字节数 
		dwBmBitsSize, 
		dwDIBSize, dwWritten; 
	BITMAP Bitmap; //位图属性结构 
	BITMAPFILEHEADER bmfHdr; //位图文件头结构 
	BITMAPINFOHEADER bi; //位图信息头结构 
	LPBITMAPINFOHEADER lpbi; //指向位图信息头结构 
	HANDLE fh, hDib, hPal,hOldPal=NULL; //定义文件，分配内存句柄，调色板句柄 
	//计算位图文件每个像素所占字节数 
	HDC hWndDC = CreateDC("DISPLAY",NULL,NULL,NULL); 
	hDC = ::CreateCompatibleDC( hWndDC ) ; 
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES); 
	DeleteDC(hDC); 
	if (iBits <= 1) 
		wBitCount = 1; 
	else if (iBits <= 4) 
		wBitCount = 4; 
	else if (iBits <= 8) 
		wBitCount = 8; 
	else if (iBits <= 24) 
		wBitCount = 24; 
	else 
		wBitCount = 24 ; 
	//计算调色板大小 
	if (wBitCount <= 8) 
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD); 
	//设置位图信息头结构 
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap); 
	bi.biSize = sizeof(BITMAPINFOHEADER); 
	bi.biWidth = Bitmap.bmWidth; 
	bi.biHeight = Bitmap.bmHeight; 
	bi.biPlanes = 1; 
	bi.biBitCount = wBitCount; 
	bi.biCompression = BI_RGB; 
	bi.biSizeImage = 0; 
	bi.biXPelsPerMeter = 0; 
	bi.biYPelsPerMeter = 0; 
	bi.biClrUsed = 0; 
	bi.biClrImportant = 0; 
	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount+31)/32) * 4 * Bitmap.bmHeight ; 
	//为位图内容分配内存 
	hDib = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER)); 
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib); 
	*lpbi = bi; 
	// 处理调色板 
	hPal = GetStockObject(DEFAULT_PALETTE); 
	if (hPal) 
	{ 
		hDC = ::GetDC(NULL); 
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE); 
		RealizePalette(hDC); 
	} 
	// 获取该调色板下新的像素值 
	GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight, 
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) 
		+dwPaletteSize, 
		(LPBITMAPINFO ) 
		lpbi, DIB_RGB_COLORS); 
	//恢复调色板 
	if (hOldPal) 
	{ 
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE); 
		RealizePalette(hDC); 
		::ReleaseDC(NULL, hDC); 
	} 
	//创建位图文件 
	fh = CreateFile(lpFileName, GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL); 
	if (fh == INVALID_HANDLE_VALUE) 
		return FALSE; 
	// 设置位图文件头 
	bmfHdr.bfType = 0x4D42; // "BM" 
	dwDIBSize = sizeof(BITMAPFILEHEADER) 
		+ sizeof(BITMAPINFOHEADER) 
		+ dwPaletteSize + dwBmBitsSize; 
	bmfHdr.bfSize = dwDIBSize; 
	bmfHdr.bfReserved1 = 0; 
	bmfHdr.bfReserved2 = 0; 
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) 
		+ (DWORD)sizeof(BITMAPINFOHEADER) 
		+ dwPaletteSize; 
	// 写入位图文件头 
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL); 
	// 写入位图文件其余内容 
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, 
		&dwWritten, NULL); 
	//清除 
	GlobalUnlock(hDib); 
	GlobalFree(hDib); 
	CloseHandle(fh); 
	return TRUE; 
}


HBITMAP CopyScreenToBitmap(LPRECT lpRect) 
{ 
	// 屏幕和内存设备描述表 
	HDC hScrDC=0, hMemDC; 
	// 位图句柄 
	HBITMAP hBitmap, hOldBitmap; 
	// 选定区域坐标 
	int nX, nY, nX2, nY2; 
	// 位图宽度和高度 
	int nWidth, nHeight; 
	// 屏幕分辨率 
	int xScrn, yScrn; 	
	// 确保选定区域不为空矩形 
	// if (IsRectEmpty(lpRect)) 
	// return NULL; 
	//为屏幕创建设备描述表 
	hScrDC = CreateDC( "DISPLAY", NULL, NULL, NULL); 
	//
	int ok=1; 
	if(hScrDC==NULL)  //如果创建失败
	{	
		ok=0;
	}
	//为屏幕设备描述表创建兼容的内存设备描述表 
	hMemDC = CreateCompatibleDC(hScrDC); 	
	// 获得选定区域坐标 
	nX = lpRect-> left; 
	nY = lpRect-> top; 
	nX2 = lpRect-> right; 
	nY2 = lpRect-> bottom; 
	// 获得屏幕分辨率 
	xScrn = GetDeviceCaps(hScrDC, HORZRES); 
	yScrn = GetDeviceCaps(hScrDC, VERTRES); 
	//确保选定区域是可见的 
	if (nX <0) 
		nX = 0; 
	if (nY < 0) 
		nY = 0; 
	if (nX2 > xScrn) 
		nX2 = xScrn; 
	if (nY2 > yScrn) 
		nY2 = yScrn; 
	nWidth = nX2 - nX; 
	nHeight = nY2 - nY; 
	// 创建一个与屏幕设备描述表兼容的位图 
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight); 
	// 把新位图选到内存设备描述表中 
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap); 	
	// 把屏幕设备描述表拷贝到内存设备描述表中 
	BitBlt(hMemDC, 0, 0, nWidth, nHeight,hScrDC, nX, nY, SRCCOPY); 	
	//得到屏幕位图的句柄 
	hBitmap =(HBITMAP)SelectObject(hMemDC, hOldBitmap); 
	//清除 
	DeleteDC(hScrDC); 
	DeleteDC(hMemDC); 	
	// 返回位图句柄 
	return hBitmap; 	
}


void CMSIView::OnFileSave() 
{
	// TODO: Add your command handler code here
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->IsSettings==false)
	{
		AfxMessageBox("没有进行设置！");
		return;
	}
	CBitmap m_bitmap;
	CRect rect; 
	GetWindowRect(&rect);
	rect.OffsetRect(1,1);	
	m_bitmap.m_hObject=CopyScreenToBitmap(rect);
	CFileDialog outFileDialog(false,".grd","成像结果",OFN_HIDEREADONLY,"Grd File(*.grd)|*.grd|Bmp File(*.bmp)|*.bmp|Dat File(*.dat)|*.dat|All File(*.*)|*.*||") ;
	outFileDialog.m_ofn.lpstrTitle = "保存成像结果";
	CString FileExt,m_outfile;
	if (outFileDialog.DoModal ()==IDOK)
	{
		m_outfile=outFileDialog.GetPathName ();
		FileExt=outFileDialog.GetFileExt();
		CFileStatus status;  
		if(CFile::GetStatus(m_outfile,status))   
		{ 
			CString msg;
			msg.Format("数据文件“%s”已经存在。\n要替换它吗？",m_outfile);   
			int exist=AfxMessageBox(msg,MB_YESNO); 
			if(exist==7)return ;
		}  
		if(FileExt=="grd"||FileExt=="GRD")
		{
			pDoc->section.WriteGrd(m_outfile);
		}
		else if(FileExt=="bmp"||FileExt=="BMP")
		{
			SaveBitmapToFile(m_bitmap,m_outfile);
		}
		else if(FileExt=="dat"||FileExt=="DAT")
		{
			pDoc->section.Cal_deltaT(m_outfile);
		}
		else return;
	}
}

void CMSIView::UpdateImage()
{
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *pDC;
	pDC=GetDC();
	CRect rect; 
	GetClientRect(&rect);
	pDoc->section.Draw(pDC,rect,pDoc->IsReadData,pDoc->IsSettings);	
}

void CMSIView::OnMenuitemcolorbar() 
{
	// TODO: Add your command handler code here
	IsCheckColorBar=!IsCheckColorBar;
	CMSIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->section.IsDrawColorBar=IsCheckColorBar;
	Invalidate(true);	
}

void CMSIView::OnUpdateMenuitemcolorbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(IsCheckColorBar);
}