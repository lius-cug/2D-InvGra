// Dike2D.cpp: implementation of the CDike2D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "���Ȱ�״������.h"
#include "Dike2D.h"
#include "math.h"

#define PI 3.14159265358979

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CDike2D::CDike2D(const double C_Ms, const double C_Is,
				 const double C_x0, const double C_z0,
				 const double C_b, const double C_l,
				 const double C_alpha,const double C_A,
				 const double C_I)
{
	Ms=C_Ms;
	Is=C_Is;
	x0=C_x0;
	z0=C_z0;
	b=C_b;
	l=C_l;
	alpha=C_alpha;
	A=C_A;
	I=C_I;
}


CDike2D::~CDike2D()
{
}
/*
���㹫ʽ��<���������ݻ��������뷽��>ҦҦ����--�й����ʴ�ѧ������2002��8�µ�һ��P90
<Ӧ�õ�������ѧԭ��> ��ʤҳ����--�й����ʴ�ѧ������2004��1�µ�һ��P168
*/
double CDike2D::Cal_Hax(double x,double z)
{
	double is,a;
	is=Is*PI/180;
	a=alpha*PI/180;
	double Hax=0;
	double x1,x2,x3,x4,z1,z2,U,V;
	x1=x-x0+b+l*cos(a);
	x2=x-x0+b-l*cos(a);
	x3=x-x0-b+l*cos(a);
	x4=x-x0-b-l*cos(a);
	z1=z0-z-l*sin(a);
	z2=z0-z+l*sin(a);
	U=log((z2*z2+x2*x2)*(z1*z1+x3*x3)/((z1*z1+x1*x1)*(z2*z2+x4*x4)));
	V=atan(2*b*z1/(z1*z1+(x1-b)*(x1-b)-b*b))-atan(2*b*z2/(z2*z2+(x2-b)*(x2-b)-b*b));
	Hax=2*Ms*sin(a)*(cos(a-is)*U/2-sin(a-is)*V);
	return 100*Hax;// ���ش��쳣��λ��nT
}





double CDike2D::Cal_Za(double x,double z)
{
	double is,a;
	is=Is*PI/180;
	a=alpha*PI/180;
	double Za=0;
	double x1,x2,x3,x4,z1,z2,U,V;
	x1=x-x0+b+l*cos(a);
	x2=x-x0+b-l*cos(a);
	x3=x-x0-b+l*cos(a);
	x4=x-x0-b-l*cos(a);
	z1=z0-z-l*sin(a);
	z2=z0-z+l*sin(a);
	U=log((z2*z2+x2*x2)*(z1*z1+x3*x3)/((z1*z1+x1*x1)*(z2*z2+x4*x4)));
	V=atan(2*b*z1/(z1*z1+(x1-b)*(x1-b)-b*b))-atan(2*b*z2/(z2*z2+(x2-b)*(x2-b)-b*b));
	Za=2*Ms*sin(a)*(sin(a-is)*U/2+cos(a-is)*V);
	return 100*Za;// ���ش��쳣��λ��nT
}


/*
double CDike2D::Cal_delta_T(double x,double z)
{
	double a,i;
	a=A*PI/180;
	i=I*PI/180;
	return Cal_Hax(x,z)*cos(i)*cos(a)+Cal_Za(x,z)*sin(i);
}

*/

void CDike2D::Set(double SET_Ms,double SET_Is,
				  double SET_x0,double SET_z0,
				  double SET_b,double SET_l,
				  double SET_alpha,double SET_A,
				  double SET_I)
{
	Ms=SET_Ms;
	Is=SET_Is;
	x0=SET_x0;
    z0=SET_z0;
	b=SET_b;
	l=SET_l;
	alpha=SET_alpha;
	A=SET_A;
	I=SET_I;
}

void CDike2D::Set(int index, double para)
{
	switch(index)
	{
	case 0:Ms=para;break;
	case 1:Is=para;break;
	case 2:x0=para;break;
	case 3:z0=para;break;
	case 4:b=para;break;
	case 5:l=para;break;
	case 6:alpha=para;break;
	case 7:A=para;break;
	case 8:I=para;break;
	default:break;
	}
}

double CDike2D::GetData(int index)
{
	switch(index)
	{
	case 0:return Ms;break;
	case 1:return Is;break;
	case 2:return x0;break;
	case 3:return z0;break;
	case 4:return b;break;
	case 5:return l;break;
	case 6:return alpha;break;
	case 7:return A;break;
	case 8:return I;break;
	default:return 0;break;
	}
}


double CDike2D::Cal_delta_T(double x,double z)
{
	
	
	double CalLog(double XP, double D1, double D2);
	double CalAtn(double XP,double Dn);	
		
    double Xk=x;
	double Zk=z;
	double X0=x0;
	double Z0=z0;
	double XL=2*b;
	double ZL=2*l;
	double Density=Ms;
	
	// function RV=mm_Int2DCube(Xk,Zk,X0,Z0,XL,ZL,sUnit)
	// ���㵥�����޳�ˮƽ�����������ֵ
	// ���幫ʽ����������̽���Ͻ����ֲᡷ��135ҳ
	// function RV=IntFunc(Xk,Zk,X0,Z0,XL,ZL)
	// (Xk,Zk) Ϊ�۲������
	// (X0,Z0) Ϊ��������������
	// (XL,ZL) Ϊ�����峤����
	// sUnit��ʾ���굥λ��'km'��'m'
	// echo off
    double AA = XL / 2;
    double D1 = Zk + Z0 - ZL / 2;
    double D2 = Zk + Z0 + ZL / 2;
    double XX = Xk-X0;
    
    double P1 = (XX + AA) * CalLog(XX + AA, D1, D2); 
    double P2 =  (XX - AA) * CalLog(XX - AA, D1, D2);
    double P3 =  2 * D2 * (CalAtn(XX + AA, D2) - CalAtn(XX - AA, D2));
    double P4 =  2 * D1 * (CalAtn(XX + AA, D1) - CalAtn(XX - AA, D1));
	// ע��˴�����Ϊ������m���ܶ�g/cm^3�������쳣mGal
    double PSUM  =  (P1-P2+P3-P4);
	//   if lower(sUnit) == 'km'
	//       RV = PSUM * 6.672;
	//   else
    return PSUM * 0.006672*Density;
	//   end
	
}

double CalLog(double XP, double D1, double D2)
{
	double P1 = (XP * XP + D2 * D2);
	double P2 = (XP * XP + D1 * D1);
	return log(P1 / P2);
}

double CalAtn(double XP,double Dn)
{
	double P1=0.0;

	if(fabs(Dn)<=0.000001)
		 P1 = PI/2;
	else
		 P1 = atan(XP / Dn);
	return P1 + PI / 2;
}
