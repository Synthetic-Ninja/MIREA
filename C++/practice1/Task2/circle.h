class Circle
{
public:
	Circle(double r, double x, double y);
	void set_circle(double r, double x, double y);
	double square();
	bool triangle_around(double a, double b, double c);
	bool triangle_in(double a, double b, double c);
	bool check_circle(double r, double x_cntr, double y_cntr);

private:
	double radius;
	double x_center;
	double y_center;

}; 
