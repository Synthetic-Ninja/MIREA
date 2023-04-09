#include <cmath>
#include <iostream>

#include "truncatedcone.h"


TruncatedСone::TruncatedСone()
{
	h2 = 1;
	r2 = 1;
}

TruncatedСone::TruncatedСone(double radius, double height,
							 double radius2, double height2)
{
	set(radius, height, radius2, height2);
}

TruncatedСone::TruncatedСone(double radius,
				  			 double height,
				  			 double radius2,
				  			 double height2,
		 		  			 double coord_x,
		 		  			 double coord_y,
		 		  			 double coord_z)
{
	set(radius, height, radius2, height2, coord_x, coord_y, coord_z);
}

TruncatedСone::TruncatedСone(Cone cone)
{
	double radius2 = 1;
	double height2 = 1;
	set(cone.get_radius(), cone.get_height(),
	    radius2, height2, cone.get_x(),
	    cone.get_y(), cone.get_z()
	    );
}


TruncatedСone::TruncatedСone(Cone cone, double radius2, double height2)
{
	set(cone.get_radius(), cone.get_height(),
	    radius2, height2, cone.get_x(),
	    cone.get_y(), cone.get_z()
	    );
}


void TruncatedСone::set(double radius, double height, double radius2, double height2)
{
	Cone::set(radius, height);
	h2 = height2;
	r2 = radius2;
}

void TruncatedСone::set(double radius,
		 				double height,
	 	 				double radius2,
	 	 				double height2,
	 	 				double coord_x,
	 	 				double coord_y,
	 	 				double coord_z)
{
	Cone::set(radius, height, coord_x, coord_y, coord_z);
	h2 = height2;
	r2 = radius2;
}


void TruncatedСone::show()
{
	std::cout << "Конус с коориднатами x: " << x << " y: " << y << " z: " << z << std::endl;
	std::cout << "Высота всего конуса h: " << h << std::endl;
	std::cout << "Высота усеченного конуса h: " << h2 << std::endl;
	std::cout << "Радиус нижнего основания r: " << r << std::endl;
	std::cout << "Радиус верхнего основания r2: " << r2 << std::endl;
}

double TruncatedСone::get_area()
{
	double full_area = Cone::get_area();
	double l = h - h2;
	return full_area - (M_PI * r2 * (r2 + sqrt(pow(r2, 2) + pow(l, 2))));
}

double TruncatedСone::get_volume()
{
	double full_volume = Cone::get_volume();
	double l = h - h2;
	return full_volume - ((M_PI * pow(r2, 2) * l) / 3);

}

std::ostream& operator << (std::ostream &os, TruncatedСone &cone)
{
	return os << "Усеченный конус\nx:" << cone.get_x() << "\ny: " << cone.get_y() << "\nz: " << cone.get_z() << "\nr1: " << cone.get_radius() << "\nr2: " << cone.r2 << "\nh: " << cone.h2 << "\narea: " << cone.get_area() << "\nvolume: " << cone.get_volume() << std::endl;
}

std::istream& operator >> (std::istream& in, TruncatedСone &cone)
{
	double r, h, r2, h2, x, y, z;

	in >> r >> h >> r2 >> h2 >> x >> y >> z;
	cone.set(r, h, r2, h2, x, y, z);
	return in;
}

bool operator > (TruncatedСone &cone1, TruncatedСone &cone2)
{
	return cone1.get_volume() > cone2.get_volume();
}

bool operator < (TruncatedСone &cone1, TruncatedСone &cone2)
{
	return cone1.get_volume() < cone2.get_volume();
}

bool operator == (TruncatedСone &cone1, TruncatedСone &cone2)
{
	return cone1.get_volume() == cone2.get_volume();
}

bool operator <= (TruncatedСone &cone1, TruncatedСone &cone2)
{
	return cone1.get_volume() <= cone2.get_volume();
}

bool operator >= (TruncatedСone &cone1, TruncatedСone &cone2)
{
	return cone1.get_volume() >= cone2.get_volume();
}




