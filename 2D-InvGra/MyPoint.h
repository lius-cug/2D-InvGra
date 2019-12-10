/////////////////////////
///////////
#ifndef CMyPoint_LIUSHUANG_200903 
#define CMyPoint_LIUSHUANG_200903

class CMyPoint
{
private :
	double x;
	double z;
	double data;
public:
	CMyPoint();
	CMyPoint(double X,double Z);
	double GetX();
	double GetZ();
	double GetData();
	void SetX(double X);
	void SetZ(double Z);
	void SetData(double Data);
	virtual~CMyPoint();
};

#endif 
