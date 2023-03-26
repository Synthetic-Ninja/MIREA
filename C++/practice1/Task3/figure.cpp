#include <cmath>
#include <iostream>
#include "figure.h"
#include "triangle.h"



Figure::Figure(double x1, double x2, double x3, double x4, 
			   double y1, double y2, double y3, double y4)
{
 	this->x1 = x1;
 	this->x2 = x2;
 	this->x3 = x3;
 	this->x4 = x4;
 	this->y1 = y1;
 	this->y2 = y2;
 	this->y3 = y3;
 	this->y4 = y4;

 	AB = get_distance(x2, x1, y2, y1);
 	BC = get_distance(x3, x2, y3, y2);
 	CD = get_distance(x4, x3, y4, y3);
 	AD = get_distance(x1, x4, y1, y4);
 	BD = get_distance(x4, x2, y4, y2);

 	P = get_perimetr();
 	S = get_square();


}

void Figure::show()
{
	std::cout << "Четырехугольник с вершинами : " << "(" << x1 << ";" << y1 << ") " 
							                      << "(" << x2 << ";" << y2 << ") " 
							                      << "(" << x3 << ";" << y3 << ") " 
							                      << "(" << x4 << ";" << y4 << ") " 
							                      << std::endl;
    
    std::cout << "Периметр: " << P << std::endl;
    std::cout << "Площадь: " << S << std::endl;
     

}

bool Figure::is_prug()
{
	double diag1 = BD;
	double diag2 = get_distance(x3, x1, y3, y1);

	return diag1 == diag2;
}

bool Figure::is_square()
{

	return is_romb() && is_prug();
}

bool Figure::is_romb()
{
	return AB == BC and BC == CD and CD == AD and AD == AB;
}

bool Figure::is_in_circle()
{
	return (AB + CD) == (BC + AD);
}

bool Figure::is_out_circle()
{

	float v1x = x2 - x1;
	float v1y = y2 - y1;
	float v2x = x4 - x1;
	float v2y = y4 - y1;
	float v3x = x3 - x2;
	float v3y = y3 - y2;

	float v1len = sqrt(pow(v1x, 2) + pow(v1y, 2));
	float v2len = sqrt(pow(v2x, 2) + pow(v2y, 2));
	float v3len = sqrt(pow(v3x, 2) + pow(v3y, 2));

	float vec1 = v1x * v2x + v1y * v2y;
	float vec2 = v2x * v3x + v2y * v3y;

	float alpha = acos(vec1 / (v1len * v2len));
	float beta = acos(vec2 / (v2len * v3len));

	return abs(M_PI / 2 - alpha - beta) < 0.001;


}

double Figure::get_distance(double coord_x1, double coord_x2, double coord_y1, double coord_y2)
{
	return sqrt(pow((coord_x2 - coord_x1), 2) + pow((coord_y2 - coord_y1), 2));
}

double Figure::get_perimetr()
{
	return AB + BC + CD + AD;
}

double Figure::get_square()
{
	Triangle triangle1 = Triangle(AB, BD, AD);
	Triangle triangle2 = Triangle(BC, CD, BD);

	return triangle1.square() + triangle2.square();
}







