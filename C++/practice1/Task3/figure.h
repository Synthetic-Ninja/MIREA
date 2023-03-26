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

	double x1, x2, x3, x4, y1, y2, y3, y4;
	double AB, BC, CD, AD, BD;
	double S;
	double P;
	double get_distance(double coord_x1, double coord_x2,
	 					double coord_y1, double coord_y2);
	double get_perimetr();
	double get_square();



};

