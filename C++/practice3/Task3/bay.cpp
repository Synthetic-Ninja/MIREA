#include <vector>
#include <string>
#include "bay.h"



Bay::Bay(): WaterArea(){}

Bay::Bay(std::string in_name, std::string in_location, double in_area, double in_size): WaterArea(in_name, in_location, in_area, in_size){}

Bay::Bay(std::string in_name, std::string in_location, double in_area, double in_size, WaterArea parent_object): WaterArea(in_name, in_location, in_area, in_size)
{
	add_parent( parent_object);
}

Bay::Bay(std::string in_name, std::string in_location, double in_area, double in_size, std::vector<WaterArea> parent_objects): WaterArea( in_name, in_location, in_area,  in_size)
{
	add_parents(parent_objects);
}

void Bay::add_parent(WaterArea parent_object)
{
	parent_water_areas.push_back(parent_object);
}

void Bay::add_parents(std::vector<WaterArea> parent_objects)
{
	parent_water_areas.insert(parent_water_areas.end(), parent_objects.begin(), parent_objects.end());
}