#include <cmath>
#include <iostream>
#include "cone.h"


//Конструкторы

Cone::Cone()
{
	x = y = z = 0;
	h = r = 1;
}
	

Cone::Cone(double radius, double height)
{
	set(radius, height);
}


	 
Cone::Cone(double radius, double height, double coord_x,
		   double coord_y,double coord_z)
{
	set(radius, height, coord_x, coord_y, coord_z);
}


//Методы

void Cone::set(double radius, double height)
{
	x = y = z = 0;
	h = height;
	r = radius;
}


	

void Cone::set(double radius,double height,double coord_x,
	     double coord_y,double coord_z)
{
	x = coord_x;
	y = coord_y;
	z = coord_z;

	h = height;
	r = radius;
}


double Cone::get_area()
{
 return M_PI * r * (r + sqrt(pow(r, 2) + pow(h, 2)));
}

double Cone::get_volume()
{
	return (M_PI * pow(r, 2) * h) / 3;
}


void Cone::show()
{
	std::cout << "Конус с коориднатами x: " << x << " y: " << y << " z: " << z << std::endl;
	std::cout << "Высота конуса h: " << h << std::endl;
	std::cout << "Радиус основания r: " << r << std::endl;
}

double Cone::get_height()
{
	return h;
}

double Cone::get_radius()
{
	return r;
}

double Cone::get_x()
{
	return x;
}

double Cone::get_y()
{
	return y;
}

double Cone::get_z()
{
	return z;
}













