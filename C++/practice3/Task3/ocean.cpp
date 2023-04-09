#include <vector>
#include <string>
#include "ocean.h"


Ocean::Ocean(): WaterArea(){}

Ocean::Ocean(std::string in_name, std::string in_location, double in_area, double in_size): WaterArea(in_name, in_location, in_area, in_size){}

Ocean::Ocean(std::string in_name, std::string in_location, double in_area, double in_size, WaterArea child_object): WaterArea(in_name, in_location, in_area, in_size)
{
	add_child(child_object);
}

Ocean::Ocean(std::string in_name, std::string in_location, double in_area, double in_size, std::vector<WaterArea> child_objects): WaterArea(in_name, in_location, in_area, in_size)
{
	add_childs(child_objects);
}

void Ocean::add_child(WaterArea child)
{
	child_water_areas.push_back(child);
}

void Ocean::add_childs(std::vector<WaterArea> childs)
{
	child_water_areas.insert(child_water_areas.end(), childs.begin(), childs.end());
}

std::vector<WaterArea> Ocean::get_childs()
{
	return child_water_areas;
}
