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



	//��Ա����
	//��ȡ����
	double GetData(int index);

	//����Hax
	double Cal_Hax(double x,double z);


	//����Za
	double Cal_Za(double x,double z);

	//����delta_T(��T)
	double Cal_delta_T(double x,double z);

	//����delta_g����g��
	double Cal_delta_g(double x,double z);

private:
	//��Ա����
	double Ms;	//��Ч�Ż�ǿ��  ��λ A/m
	double Is;	//��Ч�����    ��λ ��
	double x0;	//������x����
	double z0;	//������z����
	double b;	//��ˮƽ���Ϊ2b
	double l;	//���������Ϊ2l
	double alpha;	//������Ϊalpha
	double A ;      //���߷�λ��
	double I ;      //�ش����

};

#endif // !defined(AFX_CUBOID_H__CD73D895_1FC7_4F51_8219_DF9F9F7694F9__INCLUDED_)
