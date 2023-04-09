#include "waterarea.h"
#include <string>
#include <iostream>

WaterArea::WaterArea()
{
	name = "None";
	location = "None";
	area = 0;
	size = 0;
}


WaterArea::WaterArea(std::string in_name, std::string in_location, double in_area, double in_size)
{
	set_params(in_name, in_location, in_area, in_size);
}


void WaterArea::set_params(std::string in_name, std::string in_location, double in_area, double in_size)
{
	name = in_name;
	location = in_location;
	area = in_area;
	size = in_size;
}

std::string WaterArea::get_name()
{
	return name;
}

std::string WaterArea::get_location()
{
	return location;
}

double WaterArea::get_area()
{
	return area;
}

double WaterArea::get_size()
{
	return size;
}


std::ostream& operator << (std::ostream &os, WaterArea &waterarea)
{
	return os << "Name: " << waterarea.name << "\nLocation: " << waterarea.location <<"\nArea: " << waterarea.area << "\nSize: " << waterarea.size << std::endl;
}

std::istream& operator >> (std::istream& in, WaterArea &waterarea)
{
	std::cout << "Введите имя" << std::endl;
	in >> waterarea.name;
	std::cout << "Введите локацию" << std::endl;
	in >> waterarea.location;
	std::cout << "Введите глубину" << std::endl;
	in >> waterarea.size;
	std::cout << "Введите площадь" << std::endl;
	in >> waterarea.area;
	return in;
}







