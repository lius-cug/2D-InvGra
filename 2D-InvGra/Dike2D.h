// Dike2D.h: interface for the CDike2D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUBOID_H__CD73D895_1FC7_4F51_8219_DF9F9F7694F9__INCLUDED_)
#define AFX_CUBOID_H__CD73D895_1FC7_4F51_8219_DF9F9F7694F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDike2D  
{
public:
	void Set(int index,double para);

	void Set(double SET_Ms,double SET_Is,
		     double SET_x0,double SET_z0,
			 double SET_b,double SET_l,
			 double SET_alpha,double SET_A,
			 double SET_I);


	CDike2D(const double C_Ms=0,const double C_Is=0,
		    const double C_x0=0,const double C_z0=0,
			const double C_b=0,const double C_l=0,
			const double C_alpha=0,const double C_A=0,
			const double C_I=0);


	virtual ~CDike2D();



	//成员函数
	//获取参数
	double GetData(int index);

	//计算Hax
	double Cal_Hax(double x,double z);


	//计算Za
	double Cal_Za(double x,double z);

	//计算delta_T(ΔT)
	double Cal_delta_T(double x,double z);

	//计算delta_g（Δg）
	double Cal_delta_g(double x,double z);

private:
	//成员变量
	double Ms;	//有效磁化强度  单位 A/m
	double Is;	//有效磁倾角    单位 度
	double x0;	//板中心x坐标
	double z0;	//板中心z坐标
	double b;	//板水平宽度为2b
	double l;	//板下延深度为2l
	double alpha;	//板的倾角为alpha
	double A ;      //测线方位角
	double I ;      //地磁倾角

};

#endif // !defined(AFX_CUBOID_H__CD73D895_1FC7_4F51_8219_DF9F9F7694F9__INCLUDED_)
