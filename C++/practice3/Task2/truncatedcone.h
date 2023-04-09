#include "cone.h"
#include <iostream>

class TruncatedСone: public Cone
{
private:
	double h2; // Высота усеченного конуса
	double r2; // Высота верхнего основания

public:
	//Конструкторы
	TruncatedСone();
	TruncatedСone(double radius, double height, double radius2, double height2);
	TruncatedСone(double radius,
				  double height,
				  double radius2,
				  double height2,
		 		  double coord_x,
		 		  double coord_y,
		 		  double coord_z);
	
	TruncatedСone(Cone cone);
	TruncatedСone(Cone cone, double radius2, double height2);

	//Методы

	void set(double radius, double height, double radius2, double height2);

	void set(double radius,
		 	double height,
		 	double radius2,
		 	double height2,
		 	double coord_x,
		 	double coord_y,
		 	double coord_z);

	void show();
	double get_area();
	double get_volume();
	friend std::ostream& operator << (std::ostream &os, TruncatedСone &cone);
	friend std::istream& operator >> (std::istream& in, TruncatedСone &cone);

};


std::ostream& operator << (std::ostream &os, TruncatedСone &cone);
std::istream& operator >> (std::istream& in, TruncatedСone &cone);
bool operator > (TruncatedСone &cone1, TruncatedСone &cone2);
bool operator < (TruncatedСone &cone1, TruncatedСone &cone2);
bool operator == (TruncatedСone &cone1, TruncatedСone &cone2);
bool operator <= (TruncatedСone &cone1, TruncatedСone &cone2);
bool operator >= (TruncatedСone &cone1, TruncatedСone &cone2);



