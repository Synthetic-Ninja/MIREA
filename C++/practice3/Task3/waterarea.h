#include <string>
#include <iostream>
#pragma once


class WaterArea
{
protected:
	std::string name;
	std::string location;
	double area;
	double size;

public:
	WaterArea();
	WaterArea(std::string in_name, std::string in_location, double in_area, double in_size);
	std::string get_name();
	std::string get_location();
	double get_area();
	double get_size();
	void set_params(std::string in_name, std::string in_location, double in_area, double in_size);
	friend std::ostream& operator << (std::ostream &os, WaterArea &waterarea);
	friend std::istream& operator >> (std::istream& in, WaterArea &waterarea);
};

std::ostream& operator << (std::ostream &os, WaterArea &waterarea);
std::istream& operator >> (std::istream& in, WaterArea &waterarea);