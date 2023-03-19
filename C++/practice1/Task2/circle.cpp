#include "circle.h"
#include <math.h>
#include "triangle.h"


Circle::Circle(double r, double x, double y)
{
	radius = r;
	x_center = x;
	y_center = y;
}

void Circle::set_circle(double r, double x, double y)
{
	radius = r;
	x_center = x;
	y_center = y;	
}


double Circle::square()
{
	return M_PI * pow(radius, 2);
}


bool Circle::triangle_around(double a, double b, double c)
{
	Triangle triangle(a, b, c);
	if (!triangle.exst_tr()) return false;
	double circle_radius_around_triangle = (a * b * c) / (4 * triangle.square());
	return (round(radius * 100) / 100) == (round(circle_radius_around_triangle * 100) / 100);

}


bool Circle::triangle_in(double a, double b, double c)
{
	Triangle triangle(a, b, c);
	if (!triangle.exst_tr()) return false;
	double circle_radius_in_triangle = triangle.square() / (0.5 * triangle.perimetr());
	return (round(radius * 100) / 100) == (round(circle_radius_in_triangle * 100) / 100);
}


bool Circle::check_circle(double r, double x_cntr, double y_cntr)
{
	double distance_between_centers = pow((pow(x_cntr - x_center, 2) + pow(y_cntr - y_center, 2)), 0.5);
	return (distance_between_centers < (r + radius)) && (distance_between_centers > abs(r - radius));
}



















