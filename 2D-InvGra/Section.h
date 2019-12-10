
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
	////���캯��
	CSection();
	CSection(CMyPoint,CMyPoint);
	CSection(CMyPoint,CMyPoint,int,int);
	void SetSection(double x1,double y1,double x2,double y2,int m,int n);
	/////////////////////////////////
	////��ʼ��
	void InitSection();
	/////////////////////////////////
	/////����
	//index=0 �� Ms����Ч�Ż�ǿ��
	//index=1 �� Is����Ч�Ż����
	//index=2 �� x0�������ĺ�����
	//index=3 �� z0��������������
	//index=4 �� b�� ����
	//index=5 �� l��������쳤��
	//index=6 �� alpha�������
	//index=7 �� A�����߷�λ��
	void SetSection(int,int,CDike2D);
	void SetSection(int,int,int,double);
	void SetSection(int,double);
	////////////////////////////////
	//////��ȡ����
	double GetData(int,int,int);
	///////////////////////////////////
	///////�����쳣
	double Cal_Hax(CMyPoint);
	double Cal_Za(CMyPoint);
	double Cal_deltaT(CMyPoint);
	void Cal_Hax(CString forfile);
	void Cal_Za(CString forfile);
	void Cal_deltaT(CString forfile);
	////////////////////////////////////
	//// ����������
	double Cal_Precision(int typeobs);
	//////////////////////////////////
	///////����ģ�͵�2������ˮƽ�봹ֱ�������С����
	double Cal_Norm2(int);
	double Cal_Rx(int);
	double Cal_Rz(int);
	double Cal_R1(int);
	//////////////////////////////////
	//////����
	bool PCGM(const double Msmin,const double Msmax,int &iter,double &pre,int typeobs,
		      CString infile,CString forfile,CString outfile,double IsMOrK=1);
	bool PCGM(const double Msmin,const double Msmax,int iter,double pre,int typeobs);
	//////////////////////////////////
	//////���������
	bool ReadData(CString);
	void WriteGrd(CString,int index=0);
	///////////////////////////////////
	////��������
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
