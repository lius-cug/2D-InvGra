// SECTION.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stdio.h"
#include "Dike2D.h"
#include "Matrix.h"
#include "Math.h"
#include "Section.h"
#include "MyPoint.h"
#include "ProgBar.h"
#include "Resource.h"

#include "MSIDoc.h"
#include "MSIView.h"
#include "MSI.h"
#include "MainFrm.h"


//没有参数的构造函数
CSection::CSection()
{
	obs=NULL;
	pre=NULL;
	IsDrawColorBar=false;
/*	CMyPoint Org(0,0);
	LeftTop=Org;
	RightBottom=Org;
	Row=1;
	Col=1;
	dike=new CDike2D[Row*Col];
	CSection::InitSection();*/
}

//构造函数参数为成像剖面的左上角点和右下角点
CSection::CSection(CMyPoint LT,CMyPoint RB)
{
	LeftTop=LT;
	RightBottom=RB;
	Row=1;
	Col=1;
	dike=new CDike2D[Row*Col];
	CSection::InitSection();
}

//构造函数参数为成像剖面的左上角点,右下角点,网格剖分的行数和列数
CSection::CSection(CMyPoint LT,CMyPoint RB,int m,int n)
{
	LeftTop=LT;
	RightBottom=RB;
	Row=m;
	Col=n;
	dike=new CDike2D[Row*Col];
	CSection::InitSection();
}

void CSection::SetSection(double x1,double y1,double x2,double y2,int m,int n)
{
	LeftTop.SetX(x1);
	LeftTop.SetZ(y1);
	RightBottom.SetX(x2);
	RightBottom.SetZ(y2);
	Row=m;
	Col=n;
	dike=new CDike2D[Row*Col];
	
	/*IsWeighted=false;
	double Ms=0;
	double Is=0;
	double alpha=90;
	double A=0;
	double I=0;
	double b=(RightBottom.GetX()-LeftTop.GetX() )/Col/2;
	double l=(RightBottom.GetZ()-LeftTop.GetZ() )/Row/2;
	double x0=0;
    double z0=0;
	for(int i=0;i<Row*Col;i++)
	{
		x0=LeftTop.GetX()+2*b*(i%Col)+b;
        z0=LeftTop.GetZ()+2*l*(i/Col)+l;
		dike[i].Set(Ms,Is,x0,z0,b,l,alpha,A,I);
	}*/

	CSection::InitSection();
}

//析构函数
CSection::~CSection()
{
	delete[]dike;
	delete[]obs;
	delete[]pre;
}

//初始化函数
void CSection::InitSection()
{
	
	OffsetX=0;
	OffsetY=0;
	Scale=1;
	IsWeighted=false;
	double Ms=0;
	double Is=0;
	double alpha=90;
	double A=0;
	double I=0;
	double b=(RightBottom.GetX()-LeftTop.GetX() )/Col/2;
	double l=(RightBottom.GetZ()-LeftTop.GetZ() )/Row/2;
	double x0=0;
    double z0=0;
	for(int i=0;i<Row*Col;i++)
	{
		x0=LeftTop.GetX()+2*b*(i%Col)+b;
        z0=LeftTop.GetZ()+2*l*(i/Col)+l;
		dike[i].Set(Ms,Is,x0,z0,b,l,alpha,A,I);
	}
}
//重新给第i行，第j列网格赋值dike2d
void CSection::SetSection(int i,int j,CDike2D dike2d)
{dike[(i-1)*Col+j-1]=dike2d;}

//重新给第i行，第j列网格的第index个参数赋值para
//index=0 → Ms：有效磁化强度
//index=1 → Is：有效磁化倾角
//index=2 → x0：板中心横坐标
//index=3 → z0：板中心纵坐标
//index=4 → b： 板半宽
//index=5 → l：板半延伸长度
//index=6 → alpha：板倾角
//index=7 → A：测线方位角
void CSection::SetSection(int i,int j,int index,double para)
{dike[(i-1)*Col+j-1].Set(index,para);}

//给剖面的第index个参数重新赋值
void CSection::SetSection(int index,double para)
{
	for(int i=0;i<Row*Col;i++)
		dike[i].Set(index,para);
}

//计算点obspoint的Hax异常
double CSection::Cal_Hax(CMyPoint obspoint)
{
	double Hax=0;
	for(int i=0;i<Row*Col;i++)
		Hax+=dike[i].Cal_Hax(obspoint.GetX(),obspoint.GetZ ());
	return Hax;
}
//计算点obspoint的Za异常
double CSection::Cal_Za(CMyPoint obspoint)
{
	double Za=0;
	for(int i=0;i<Row*Col;i++)
		Za+=dike[i].Cal_Za (obspoint.GetX(),obspoint.GetZ ());
	return Za;
}
//计算点obspoint的ΔT异常
double CSection::Cal_deltaT(CMyPoint obspoint)
{
	double T=0;
	for(int i=0;i<Row*Col;i++)
		T+=dike[i].Cal_delta_T (obspoint.GetX(),obspoint.GetZ ());
	return T;
}
//获取第i行，j列网格的第index参数的值
double CSection::GetData(int i,int j,int index)
{return dike[(i-1)*Col+j-1].GetData (index);}

//计算第index个参数模型的二范数（或者长度）
double CSection::Cal_Norm2(const int index=0)
{
	double norm2=0;
	if(IsWeighted)
	{
		return 1.0;
	}
	else
	{
		for(int i=0;i<Row*Col;i++)
			norm2+=dike[i].GetData(index)*dike[i].GetData(index);
	};
	return norm2;
	
}
//第index参数的水平粗糙度
double CSection::Cal_Rx (const int index=0)
{
	double rx=0;
	if(IsWeighted)
	{
		return 1.0;
	}
	else
	{
		for(int i=0;i<Row*Col-1;i++)
			rx+=pow(dike[i].GetData(index)-dike[i+1].GetData(index),2);
	};
	return rx;
	
}

//第index参数的垂直粗糙度
double CSection::Cal_Rz(const int index=0)
{
	double rz=0;
	if(IsWeighted)
	{
		return 1.0;
	}
	else
	{
		for(int i=0;i<(Row-1)*Col;i++)
			if (i!=Col-1)
				rz+=pow(dike[i].GetData(index)-dike[i+Col].GetData(index),2);
	};
	return rz;
	
}
//总粗糙度
double CSection::Cal_R1 (const int index=0)
{return Cal_Rz(index)+Cal_Rz(index);}

//计算拟合误差
double CSection::Cal_Precision(int typeobs)
{
	double sum1=0,sum2=0;
	for(int i=0;i<NP;i++)
	{
		if (typeobs==0)pre[i].SetData(Cal_deltaT(pre[i]));
		else if(typeobs==1)pre[i].SetData(Cal_Hax(pre[i]));
		else if(typeobs==2)pre[i].SetData(Cal_Za(pre[i]));
		else return 0;
		sum1+=(obs[i].GetData()-pre[i].GetData())*(obs[i].GetData()-pre[i].GetData());
		sum2+=obs[i].GetData()*obs[i].GetData();
	}
	return sqrt(sum1/sum2);
}

//计算剖面的Hax分量
void CSection::Cal_Hax(CString forfile)
{
	FILE *fp=fopen(forfile,"w");
	//	fprintf(fp,"点号 X坐标 Z坐标 观测数据Hax 预测数据Hax 两者偏差\n");
	for(int i=0;i<NP;i++)
	{
		pre[i].SetData(Cal_Hax(pre[i]));
		fprintf(fp,"%5f %5f %5f\n",obs[i].GetX(),obs[i].GetZ(),pre[i].GetData());
	}
	fclose(fp);
}
//计算剖面的Za分量
void CSection::Cal_Za(CString forfile)
{
	FILE *fp=fopen(forfile,"w");
	//	fprintf(fp,"点号 X坐标 Z坐标 观测数据Za 预测数据Za 两者偏差\n");
	for(int i=0;i<NP;i++)
	{
		pre[i].SetData(Cal_Za(pre[i]));
		fprintf(fp,"%5f %5f %5f\n",obs[i].GetX(),obs[i].GetZ(),pre[i].GetData());
	}
	fclose(fp);
}
//计算剖面的ΔT分量
void CSection::Cal_deltaT(CString forfile)
{
	FILE *fp=fopen(forfile,"w");
	//	fprintf(fp,"X坐标 Z坐标 观测数据ΔT 预测数据ΔT 两者偏差\n");
	fprintf(fp,"X坐标 Z坐标 观测数据ΔT 预测数据ΔT 两者偏差\n");
	for(int i=0;i<NP;i++)
	{
		pre[i].SetData(Cal_deltaT(pre[i]));
		fprintf(fp,"%5f %5f %5f %5f %5f\n",obs[i].GetX(),obs[i].GetZ(),obs[i].GetData(),pre[i].GetData(),obs[i].GetData()-pre[i].GetData());
	}
	fclose(fp);	
}

//写***.GRD文件
void CSection::WriteGrd(CString outfile,const int index)
{
	double Zmin=10E38,Zmax=10E-38;
	for(int i=0;i<Row*Col;i++)
	{
		if(dike[i].GetData(index)<Zmin)Zmin=dike[i].GetData(index);
		if(dike[i].GetData(index)>Zmax)Zmax=dike[i].GetData(index);
	}
	FILE *fp;
	fp=fopen(outfile,"w");
	fprintf(fp,"DSAA\n");
	fprintf(fp,"%8d %8d\n",Col,Row);
	fprintf(fp,"%10.4f %10.4f\n",(LeftTop.GetX()+(RightBottom.GetX()-LeftTop.GetX() )/Col/2)/1,
		(RightBottom.GetX()-(RightBottom.GetX()-LeftTop.GetX() )/Col/2)/1);
	fprintf(fp,"%10.4f %10.4f\n",-((RightBottom.GetZ()-(RightBottom.GetZ()-LeftTop.GetZ())/Row/2)/1),
		-(LeftTop.GetZ()+(RightBottom.GetZ()-LeftTop.GetZ())/Row/2)/1);
	Zmin=Zmin;
	Zmax=Zmax;
	fprintf(fp,"%10.4f %10.4f\n",Zmin,Zmax);
	for(int row=Row-1;row>=0;row--)
	{	
		for(int col=0;col<=Col-1;col++)	
			/////////////////////白化
		{
			double x=LeftTop.GetX()+(2*col+1)*(RightBottom.GetX()-LeftTop.GetX())/Col/2;
			double z=LeftTop.GetZ()+(2*row+1)*(RightBottom.GetZ()-LeftTop.GetZ())/Row/2;
			double ZZZZ=0;
			for(int np=0;np<NP-1;np++)
			{
				if(x>obs[np].GetX() && x<obs[np+1].GetX())
				{
					ZZZZ=(x-obs[np].GetX())*(obs[np].GetZ()-obs[np+1].GetZ())/(obs[np].GetX()-obs[np+1].GetX())+obs[np].GetZ();
					break;
				}
				else
					ZZZZ=1E-38;
			}
			if(z<ZZZZ)
				fprintf(fp,"%12.2e",1E38);
			else
				fprintf(fp,"%20.4f",dike[row*Col+col].GetData(index));
		}
		fprintf(fp,"\n");	
	}
	fclose(fp);
}

//读数据
bool CSection::ReadData(CString infile)
{
	//////////////////////////////////////////////
	////////调用datatrans.dll文件 将观测数据格式转化在datatrans.ini中
	char CurrentDir[160];
	GetModuleFileName(AfxGetInstanceHandle(), CurrentDir,sizeof(CurrentDir)); 
	(*strrchr(CurrentDir,'\\'))='\0';  
	strcat(CurrentDir,"\\datatrans.ini");
	typedef void (* lpFun)(const char* infile,const char* outfile);
    HINSTANCE hDll; 
	lpFun Fun;
	hDll = LoadLibrary("datatrans.dll");
	if (hDll != NULL)
	{		
		Fun = (lpFun)GetProcAddress(hDll,"datatrans");
		if(Fun!=NULL)Fun(infile,CurrentDir);  
		else{AfxMessageBox("调用文件datatrans.dll是出错！");return false;}
		FreeLibrary(hDll);
	}	
	else
	{AfxMessageBox("文件datatrans.dll不存在！");return false;}
	////////////////////////////////////////////////////	
	float temp1,temp2,temp3,temp4;
	FILE *fp;
	if((fp=fopen(CurrentDir,"r"))==NULL)                 
	{ 
		AfxMessageBox("文件打开错误！");
		exit(0);return false;
	}
	else
	{
		fscanf(fp,"%d\n",&NP);
		if(NP<=0){AfxMessageBox("数据文件不存在或者格式错误！");return false;}
		obs=new CMyPoint[NP];
		pre=new CMyPoint[NP];
		for(int i=0;i<NP;i++)
		{
			fscanf(fp,"%f %f %f %f\n",&temp1,&temp2,&temp3,&temp4);
			obs[i].SetX(temp1);
			obs[i].SetZ(temp3);
			obs[i].SetData(temp4);
			pre[i].SetX(temp1);
			pre[i].SetZ(temp3);
			pre[i].SetData(0);
		}
		fclose(fp);
	}
	return true;
}



//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////
bool CSection::PCGM(const double Msmin,const double Msmax,int iter,double pre,int typeobs)
{

	CWnd* pFrame = AfxGetMainWnd();
	int MaxIter=iter;
	double MaxPre=pre;
	int i,j,k;
	Matrix G(NP,Row*Col,0);
	Matrix m(Row*Col,1,0),P(Row*Col,1,0),Hp(Row*Col,1,0);
	Matrix d0(NP,1,0),d(NP,1,0),dd(NP,1,0);
	////////////////////////////////////////////////////////////
	//////计算核矩阵G
	SetSection(0,1.0);
	for( i=0;i<NP;i++)
	{
		for(j=0;j<Row*Col;j++)
		{
			if(typeobs==0)G(i+1,j+1)=dike[j].Cal_delta_T(obs[i].GetX (),obs[i].GetZ ());
			else if(typeobs==1)G(i+1,j+1)=dike[j].Cal_Hax(obs[i].GetX (),obs[i].GetZ ());
			else if(typeobs==2)G(i+1,j+1)=dike[j].Cal_Za(obs[i].GetX (),obs[i].GetZ ());
			else return false;
		}
	}	
	SetSection(0,0.0);
	////////////////////////////////////////////////////////////
	////计算预优矩阵
	for(i=0;i<Row*Col;i++)
		P(i+1,1)=pow(dike[i].GetData(3),2);
	///////////////////////////////////////////////////////////
	for( k=0;k<NP;k++)
		d0(k+1,1)=obs[k].GetData();	
	
	Matrix r(Row*Col,1,0),R(Row*Col,1,0),z(Row*Col,1,0),Z(Row*Col,1,0),p(Row*Col,1,0);
	Matrix tpMat1(1,1,1),tpMat2(1,1,1),Gp(NP,1,0);
	double t,beta;
	


   ///////////////////////////Starting model
  /*  FILE *fp=fopen("StartingModelKriging.dat","r");
    for(i=Row-1;i>=0;i--)
		for (j=0;j<Col;j++)
		{
			float tp=0;
			fscanf(fp,"%f\n",&tp);
			k=i*40+j;
			m(k+1,1)=tp;
		}
	d=G*m;*/



	/////////////// Reference model

   	Matrix m0(Row*Col,1,0);
    FILE *fp=fopen("StartingModelKriging.dat","r");
    for(i=Row-1;i>=0;i--)
		for (j=0;j<Col;j++)
		{
			float tp=0;
			fscanf(fp,"%f\n",&tp);
			k=i*40+j;
			m0(k+1,1)=tp;
		}
    Matrix one(Row*Col,Row*Col,0);
	for (i=0;i<Row*Col;i++)
		one(i+1,i+1)=1;

	double lamda=3E-6;


	//////////

	for(int LoopNum=0;LoopNum<MaxIter;LoopNum++)
	{
		dd=d0-d;
		r=G.Transpose()*dd+lamda*m0;     //Reference model
	//	r=G.Transpose()*dd;              //Starting model
		////////////////////////////////////////////////////////
		///预优共轭梯度法
		Matrix dm(Row*Col,1,0);
		for(int CG=0;CG<20;CG++)
		{	
			for(i=0;i<Row*Col;i++)
				z(i+1,1)=P(i+1,1)*r(i+1,1);
			if(CG==0)
				p=z;
			else
			{
				tpMat1=r.Transpose()*z;
				tpMat2=R.Transpose()*Z;
				beta=tpMat1(1,1)/tpMat2(1,1);
				p=z+beta*p;
			}
			Gp=G*p;
			Hp=(G.Transpose()*G+lamda*one)*p;   //Reference model
		//	Hp=G.Transpose()*Gp;                //Starting model
			tpMat1=r.Transpose()*z;
			tpMat2=p.Transpose()*Hp;
			t=tpMat1(1,1)/tpMat2(1,1);
			dm=dm+t*p;
			R=r;
			Z=z;
			r=r-t*Hp;
		}
		///////////////////////
		m=m+dm;
		for(i=0;i<Row*Col;i++)
		{
			if(m(i+1,1)<Msmin)m(i+1,1)=Msmin;
			if(m(i+1,1)>Msmax)m(i+1,1)=Msmax;
			dike[i].Set(0,m(i+1,1));
		}



//////////////////

		d=G*m;
		pre=100*Cal_Precision(typeobs);
		iter=LoopNum+1;
		if (pFrame)
		pFrame->SendMessage(MYWM_PROGRESS, (LoopNum+1)*1000.0/MaxIter);
			
		
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd(); ////////更新视图
		CMSIView  *pView = (CMSIView*)pFrame->GetActiveView(); 
		pView->UpdateImage();

		if(pre<=MaxPre)break;

	}

	CString str;
	str.Format("运行结束，共迭代%d次，拟合观测数据误差%.2f%%",iter,pre);
	CMSIApp *pApp=(CMSIApp *)AfxGetApp();  
	CMainFrame *pMainFrame=(CMainFrame *)pApp->m_pMainWnd;  
	pMainFrame->m_wndStatusBar.str=str;
	Sleep(500);
	if (pFrame)
		pFrame->SendMessage(MYWM_PROGRESS, 0);
	return true;	
}


///////////////////////////////////////////////////////////////////////////////////////
void CSection::Draw(CDC* pDC, CRect ClientRect,const bool isreaddata,const bool issettings)
{

	CDC dcMem; //用于缓冲作图的内存DC 
	CBitmap bmp; //内存中承载临时图象的位图 
	dcMem.CreateCompatibleDC(pDC); //依附窗口DC创建兼容内存DC 
	bmp.CreateCompatibleBitmap(pDC,ClientRect.Width(),ClientRect.Height());//创建兼容位图 
	dcMem.SelectObject(&bmp); //将位图选择进内存DC 	
	dcMem.FillSolidRect(ClientRect,pDC->GetBkColor()); //按原来背景填充客户区，不然会是黑色
	
	
	int i,j;

	CRect rectcurve(ClientRect.left+0.1*ClientRect.Width(),ClientRect.top+0.05*ClientRect.Height(),
			ClientRect.right-0.2*ClientRect.Width(),ClientRect.bottom-0.70*ClientRect.Height());
	
	rectcurve.OffsetRect(OffsetX,OffsetY);/////////////////视图偏移
	rectcurve.SetRect(rectcurve.CenterPoint().x-0.5*Scale*rectcurve.Width(),
		              rectcurve.CenterPoint().y-0.5*Scale*rectcurve.Height(),
					  rectcurve.CenterPoint().x+0.5*Scale*rectcurve.Width(),
		              rectcurve.CenterPoint().y+0.5*Scale*rectcurve.Height());

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////绘制影像图
	if(issettings==true)
	{
		//CRect rect(200,400,800,800);
		CRect rect;
		if(isreaddata==false)
		{
			rect.left=rectcurve.left;
			rect.top=rectcurve.top+100;
			rect.right=rectcurve.right;
			rect.bottom=rectcurve.bottom+100;
		}
		else
		{
			double obsZmin=obs[0].GetZ();
			for(i=0;i<NP;i++)
			{
				if(obsZmin>obs[i].GetZ())
					obsZmin=obs[i].GetZ();
			}
			double XRatio;
			XRatio=(obs[NP-1].GetX()-obs[0].GetX())/rectcurve.Width();
			double w=LeftTop.GetX()-obs[0].GetX();
			double h=LeftTop.GetZ()-obsZmin;
			double W=RightBottom.GetX()-obs[0].GetX();
			double H=RightBottom.GetZ()-obsZmin;
			w=w/XRatio;
			h=h/XRatio;
			W=W/XRatio;
			H=H/XRatio;
			rect.left=rectcurve.left+w;
			rect.top=rectcurve.bottom+40+h;
			rect.right=rectcurve.left+W;
			rect.bottom=rectcurve.bottom+40+H;
		}
		
		CPen pen;
		CBrush brush; 
		double Ratio=(RightBottom.GetX()-LeftTop.GetX())*1.0/rect.Width();
		
		double x0,y0,b,l;
		double x1, y1, x2, y2;
		
		COLORREF *color;
		COLORREF COLOR;
		color =new COLORREF[Row*Col];
		
		///////////////////////////
		double min,max;
		min=GetData(1,1,0);
		max=GetData(1,1,0);
		for( i=0;i<Row;i++)
		{
			for( j=0;j<Col;j++)
			{
				double temp=GetData(i+1,j+1,0);
				if(min>temp)
					min=temp;
				if(max<temp)
					max=temp;
			}
		}
		if(max<min)return;
		///////////////////////////
		
		for( i=0;i<Row;i++)
		{
			for( j=0;j<Col;j++)
			{
				x0=GetData(i+1,j+1,2);
				y0=GetData(i+1,j+1,3);
				b=GetData(i+1,j+1,4);
				l=GetData(i+1,j+1,5);
				x1=x0-b;
				x2=x0+b;
				y1=y0-l;
				y2=y0+l;
				
				x1=(x1-LeftTop.GetX())/Ratio+rect.left;
				x2=(x2-LeftTop.GetX())/Ratio+rect.left;
				y1=(y1-LeftTop.GetZ())/Ratio+rect.top;
				y2=(y2-LeftTop.GetZ())/Ratio+rect.top;
				
				color[i]=(COLORREF)1023.0*(GetData(i+1,j+1,0)-min)/(max-min);
	
				if(color[i]<=255)//////0~255
					COLOR=RGB(0,color[i],255);
				else if (color[i]<=511)/////256~511
					COLOR=RGB(0,255,511-color[i]);
				else if (color[i]<=767)//////512~767
					COLOR=RGB(color[i]-512,255,0);
				else if (color[i]<=1023)/////768~1023
					COLOR=RGB(255,1023-color[i],0);
			
				if(min==max)
				{
					pen.CreatePen(PS_SOLID,1,RGB(0,0,0)); 
					dcMem.SelectObject(&pen);
				}
				else
				{
					pen.CreatePen(PS_SOLID,1,COLOR); 
					dcMem.SelectObject(&pen);
				}
				brush.CreateSolidBrush(COLOR); 
				dcMem.SelectObject(&brush);
				dcMem.Rectangle(x1,y1,x2,y2);
				pen.DeleteObject();
				brush.DeleteObject();
			}
		}	
		delete[]color;


		/////////////////////////////////////////////
		///////////显示颜色刻度
		if(isreaddata==true&&IsDrawColorBar==true)
		{
			COLORREF ColorBar[100];
			COLORREF COLORBAR;
			double DataBar[100];
			for (i=0;i<100;i++)
				DataBar[i]=min+i*1.0*(max-min)/100;
			for(i=99;i>=0;i--)
			{
				ColorBar[i]=(COLORREF)1023*(DataBar[i]-min)/(max-min);
				if(ColorBar[i]<=255)//////0~255
					COLORBAR=RGB(0,ColorBar[i],255);
				else if (ColorBar[i]<=511)/////256~511
					COLORBAR=RGB(0,255,511-ColorBar[i]);
				else if (ColorBar[i]<=767)//////512~767
					COLORBAR=RGB(ColorBar[i]-512,255,0);
				else if (ColorBar[i]<=1023)/////768~1023
					COLORBAR=RGB(255,1023-ColorBar[i],0);
				pen.CreatePen(PS_SOLID,1,COLORBAR); 
				dcMem.SelectObject(&pen);
				
				brush.CreateSolidBrush(COLORBAR); 
				dcMem.SelectObject(&brush);
				dcMem.Rectangle(rectcurve.right+40,rect.top+(99-i)*1.0*rect.Height()/100,
					rectcurve.right+80,rect.top+(100-i)*1.0*rect.Height()/100);
				if(i%10==0)
				{
					CString str;
					//int tp=int(DataBar[i]);
					str.Format("%.2f",DataBar[i]);
					dcMem.TextOut(rectcurve.right+85,rect.top+(100-i)*1.0*rect.Height()/100-15,str);
				}
				pen.DeleteObject();
				brush.DeleteObject();
			}
		}


		////////////////
	}////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////绘制曲线
	if(isreaddata==true)
	{		
		double obsMin,obsMax,obsZmin;
		obsMin=obs[0].GetData();
		obsMax=obs[0].GetData();
		obsZmin=obs[0].GetZ();
		for(i=0;i<NP;i++)
		{
			double temp=obs[i].GetData();
			if(obsMin>temp)
				obsMin=temp;
			if(obsMax<temp)
				obsMax=temp;
			if(obsZmin>obs[i].GetZ())
				obsZmin=obs[i].GetZ();
		}
		double XRatio,YRatio;
		XRatio=(obs[NP-1].GetX()-obs[0].GetX())/rectcurve.Width();
		YRatio=(obsMax-obsMin)/rectcurve.Height();
		///

		CPen pen;
		//pen.DeleteObject();
		////////////////////////////////////////////////////////////////
		////////////////////截掉地面以上部分的影像图
		pen.CreatePen(PS_NULL,0,RGB(0,0,0)); 
		dcMem.SelectObject(&pen);
		CBrush brush; 
		brush.CreateSolidBrush(pDC->GetBkColor()); 
		dcMem.SelectObject(&brush);
		CPoint *PointCut;
		PointCut=new CPoint[NP+2];
		for(i=0;i<NP;i++)
		{
			PointCut[i].x=(obs[i].GetX()-obs[0].GetX())/XRatio+rectcurve.left;
			PointCut[i].y=(obs[i].GetZ()-obsZmin)/XRatio+rectcurve.bottom+40;
		}
		PointCut[NP].x=(obs[NP-1].GetX()-obs[0].GetX())/XRatio+rectcurve.left;
		PointCut[NP].y=-1000;//(obs[NP-1].GetZ()-obsZmin)/XRatio+rectcurve.bottom+40;
		PointCut[NP+1].x=(obs[0].GetX()-obs[0].GetX())/XRatio+rectcurve.left;
		PointCut[NP+1].y=-1000;//(obs[0].GetZ()-obsZmin)/XRatio+rectcurve.bottom+40;
		dcMem.Polygon(PointCut,NP+2);
		delete[]PointCut;
		brush.DeleteObject();
		//////////////////////////////////////////////////////////////

		CFont font;
		font.CreateFont(20,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,
			DRAFT_QUALITY,VARIABLE_PITCH | FF_SWISS,"Times New Roman");
		dcMem.SelectObject(&font);
		pen.DeleteObject();
		pen.CreatePen(PS_DOT,1,RGB(0,0,0)); 
		dcMem.SelectObject(&pen);
		dcMem.Rectangle(rectcurve.right+40,rectcurve.top-10,rectcurve.right+175,rectcurve.top+70);
		dcMem.TextOut(rectcurve.right+90,rectcurve.top,"观测数据");
		dcMem.TextOut(rectcurve.right+90,rectcurve.top+20,"预测数据");
		dcMem.TextOut(rectcurve.right+90,rectcurve.top+40,"地形起伏");


		pen.DeleteObject();
		pen.CreatePen(PS_SOLID,1,RGB(0,0,0)); 
		dcMem.SelectObject(&pen);
		dcMem.MoveTo(rectcurve.left,rectcurve.bottom);//ΔT轴
		dcMem.LineTo(rectcurve.left,rectcurve.top);
		dcMem.LineTo(rectcurve.left-5,rectcurve.top+10);
		dcMem.MoveTo(rectcurve.left,rectcurve.top);
		dcMem.LineTo(rectcurve.left+5,rectcurve.top+10);
		dcMem.TextOut(rectcurve.left+10,rectcurve.top,"Δg/mGal");

		dcMem.MoveTo(rectcurve.left,rectcurve.bottom);//水平X轴
		dcMem.LineTo(rectcurve.right,rectcurve.bottom);
		dcMem.LineTo(rectcurve.right-10,rectcurve.bottom-5);
		dcMem.LineTo(rectcurve.right,rectcurve.bottom);
		dcMem.LineTo(rectcurve.right-10,rectcurve.bottom+5);
		dcMem.TextOut(rectcurve.right+5,rectcurve.bottom-7,"X/m");

		dcMem.MoveTo(rectcurve.left,rectcurve.bottom+40);//深度Z轴
		dcMem.LineTo(rectcurve.left,rectcurve.bottom+40+0.5*rectcurve.Width());
		dcMem.LineTo(rectcurve.left-5,rectcurve.bottom+40+0.5*rectcurve.Width()-10);
		dcMem.LineTo(rectcurve.left,rectcurve.bottom+40+0.5*rectcurve.Width());
		dcMem.LineTo(rectcurve.left+5,rectcurve.bottom+40+0.5*rectcurve.Width()-10);
		dcMem.TextOut(rectcurve.left+10,rectcurve.bottom+40+0.5*rectcurve.Width()-14,"Z/m");
		
		for(i=0;i<11;i++)////绘制水平X刻度
		{
			double m_xAxis=rectcurve.left+rectcurve.Width()*i/10;
			CString str;
			str.Format("%.0f",obs[0].GetX()+(obs[NP-1].GetX()-obs[0].GetX())*i/10);
			dcMem.SetTextAlign (TA_CENTER);
			dcMem.TextOut ((int)m_xAxis ,rectcurve.bottom+10,str);
			dcMem.MoveTo ((int)m_xAxis ,rectcurve.bottom);
			dcMem.LineTo ((int)m_xAxis ,rectcurve.bottom+5);			
		}

		for(i=0;i<6;i++)/////绘制ΔT轴刻度
		{
			double m_yAxis=rectcurve.bottom-rectcurve.Height()*i/5;
			CString str;
			str.Format("%.0f",obsMin+(obsMax-obsMin)*i/5);
			dcMem.SetTextAlign (TA_RIGHT);
			dcMem.TextOut ( rectcurve.left-10,(int)m_yAxis-8,str);
			dcMem.MoveTo (rectcurve.left ,(int)m_yAxis);
			dcMem.LineTo (rectcurve.left-5 ,(int)m_yAxis);
		}
		for(i=0;i<6;i++)/////绘制深度Z轴刻度
		{
			double m_zAxis=rectcurve.bottom+40+rectcurve.Width()*i/10;
		//	if(m_zAxis>=ClientRect.bottom-0.05*ClientRect.Height())break;
			CString str;
			str.Format("%.0f",obsZmin+XRatio*rectcurve.Width()*i/10);
			dcMem.SetTextAlign (TA_RIGHT);
			dcMem.TextOut ( rectcurve.left-10,(int)m_zAxis-8,str);
			dcMem.MoveTo (rectcurve.left ,(int)m_zAxis);
			dcMem.LineTo (rectcurve.left-5 ,(int)m_zAxis);
		}
				
		pen.DeleteObject();//////////////////////绘制观测数据曲线
		pen.CreatePen(PS_SOLID,2,RGB(0,0,255)); 
		dcMem.SelectObject(&pen);
		for(i=0;i<NP-1;i++)
		{
			double X,Y;
			X=(obs[i].GetX()-obs[0].GetX())/XRatio+rectcurve.left;
			Y=-(obs[i].GetData()-obsMin)/YRatio+rectcurve.bottom;
			dcMem.MoveTo (X,Y);
			X=(obs[i+1].GetX()-obs[0].GetX())/XRatio+rectcurve.left;
			Y=-(obs[i+1].GetData()-obsMin)/YRatio+rectcurve.bottom;
			dcMem.LineTo (X,Y);
		}
		dcMem.MoveTo(rectcurve.right+50,rectcurve.top+10);
		dcMem.LineTo(rectcurve.right+90,rectcurve.top+10);
		
		pen.DeleteObject();//////////////////////绘制预测数据曲线
		pen.CreatePen(PS_SOLID,2,RGB(255,0,0)); 
		dcMem.SelectObject(&pen);
		for(i=0;i<NP-1;i++)
		{
			double X,Y;
			X=(pre[i].GetX()-pre[0].GetX())/XRatio+rectcurve.left;
			Y=-(pre[i].GetData()-obsMin)/YRatio+rectcurve.bottom;
			dcMem.MoveTo (X,Y);
			X=(pre[i+1].GetX()-pre[0].GetX())/XRatio+rectcurve.left;
			Y=-(pre[i+1].GetData()-obsMin)/YRatio+rectcurve.bottom;
			dcMem.LineTo (X,Y);
		}
		dcMem.MoveTo(rectcurve.right+50,rectcurve.top+30);
		dcMem.LineTo(rectcurve.right+90,rectcurve.top+30);


		pen.DeleteObject();//////////////////////绘制地形曲线
		pen.CreatePen(PS_SOLID,2,RGB(0,255,0)); 
		dcMem.SelectObject(&pen);
		for(i=0;i<NP-1;i++)
		{
			double X,Y;
			X=(obs[i].GetX()-obs[0].GetX())/XRatio+rectcurve.left;
			Y=(obs[i].GetZ()-obsZmin)/XRatio+rectcurve.bottom+40;
			dcMem.MoveTo (X,Y);
			X=(obs[i+1].GetX()-obs[0].GetX())/XRatio+rectcurve.left;
			Y=(obs[i+1].GetZ()-obsZmin)/XRatio+rectcurve.bottom+40;
			dcMem.LineTo (X,Y);
		}
		dcMem.MoveTo(rectcurve.right+50,rectcurve.top+50);
		dcMem.LineTo(rectcurve.right+90,rectcurve.top+50);

	}//////////////////////////////////
	pDC->BitBlt(0,0,ClientRect.Width(),ClientRect.Height(),&dcMem,0,0,SRCCOPY);//将内存DC上的图象拷贝到前台 
	dcMem.DeleteDC(); //删除DC 
	bmp.DeleteObject(); //删除位图 
	////
	
}
