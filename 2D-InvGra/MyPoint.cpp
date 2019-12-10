////////////////////////////
///////
#include "stdafx.h"
#include "MyPoint.h"
CMyPoint::CMyPoint()
{}
CMyPoint::CMyPoint(double X,double Z){x=X;z=Z;}
double CMyPoint::GetX()
{return x;}
double CMyPoint::GetZ()
{return z;}
double CMyPoint::GetData()
{return data;}
void CMyPoint::SetX(double X)
{x=X;}
void CMyPoint::SetZ(double Z)
{z=Z;}
void CMyPoint::SetData(double Data)
{data=Data;}
CMyPoint::~CMyPoint()
{}