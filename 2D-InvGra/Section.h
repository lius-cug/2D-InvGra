
#ifndef CLASS_CSection_H_
#define CLASS_CSection_H_


#include "stdafx.h"
#include "stdio.h"
#include "Dike2D.h"
#include "Matrix.h"
#include "Math.h"
#include "MyPoint.h"

////////////////////////////////////////////////////
class CSection
{
private:
	CMyPoint LeftTop;
	CMyPoint RightBottom;
	int Row;
	int Col;
	bool IsWeighted;
	CDike2D *dike;
	CMyPoint *obs;
	CMyPoint *pre;
	int NP;

public:

	///////////////////////////////////
	////构造函数
	CSection();
	CSection(CMyPoint,CMyPoint);
	CSection(CMyPoint,CMyPoint,int,int);
	void SetSection(double x1,double y1,double x2,double y2,int m,int n);
	/////////////////////////////////
	////初始化
	void InitSection();
	/////////////////////////////////
	/////设置
	//index=0 → Ms：有效磁化强度
	//index=1 → Is：有效磁化倾角
	//index=2 → x0：板中心横坐标
	//index=3 → z0：板中心纵坐标
	//index=4 → b： 板半宽
	//index=5 → l：板半延伸长度
	//index=6 → alpha：板倾角
	//index=7 → A：测线方位角
	void SetSection(int,int,CDike2D);
	void SetSection(int,int,int,double);
	void SetSection(int,double);
	////////////////////////////////
	//////获取属性
	double GetData(int,int,int);
	///////////////////////////////////
	///////计算异常
	double Cal_Hax(CMyPoint);
	double Cal_Za(CMyPoint);
	double Cal_deltaT(CMyPoint);
	void Cal_Hax(CString forfile);
	void Cal_Za(CString forfile);
	void Cal_deltaT(CString forfile);
	////////////////////////////////////
	//// 计算拟合误差
	double Cal_Precision(int typeobs);
	//////////////////////////////////
	///////计算模型的2范数，水平与垂直方向的最小构造
	double Cal_Norm2(int);
	double Cal_Rx(int);
	double Cal_Rz(int);
	double Cal_R1(int);
	//////////////////////////////////
	//////反演
	bool PCGM(const double Msmin,const double Msmax,int &iter,double &pre,int typeobs,
		      CString infile,CString forfile,CString outfile,double IsMOrK=1);
	bool PCGM(const double Msmin,const double Msmax,int iter,double pre,int typeobs);
	//////////////////////////////////
	//////输入与输出
	bool ReadData(CString);
	void WriteGrd(CString,int index=0);
	///////////////////////////////////
	////析构函数
	virtual~CSection();

	void Draw(CDC* pDC,CRect ClientRect,bool isreaddata=false,bool issettings=false);

public:
	int OffsetX;
	int OffsetY;
	double Scale;
	bool IsDrawColorBar;

	double IsMorK;

};

#endif
