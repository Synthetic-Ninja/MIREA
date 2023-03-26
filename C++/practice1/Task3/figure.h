class Figure
{
public:

	Figure(double x1, double x2, double x3, double x4, 
			 double y1, double y2, double y3, double y4);

	void show();
	bool is_prug();
	bool is_square();
	bool is_romb();
	bool is_in_circle();
	bool is_out_circle();

private:

	double x1,x2,x3,x4;
	double y1,y2,y3,y4;
	double S;
	double P;

};

