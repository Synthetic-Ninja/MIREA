class Cone
{
protected:
	double x, y, z, h, r;

public:
	//Конструкторы
	Cone();
	
	Cone(double radius, double height);
	
	Cone(double radius,
		 double height,
		 double coord_x,
		 double coord_y,
		 double coord_z);

	//Методы
	void set(double radius, double height);

	void set(double radius,
		 	double height,
		 	double coord_x,
		 	double coord_y,
		 	double coord_z);

	void show();
	double get_area();
	double get_volume();

	double get_height();
	double get_radius();
	double get_x();
	double get_y();
	double get_z();
};