#include <vector>
#include <string>
#include "sea.h"

Sea::Sea():WaterArea(){};

Sea::Sea(std::string in_name, std::string in_location, double in_area, double in_size): WaterArea(in_name, in_location, in_area, in_size){}

Sea::Sea(std::string in_name, std::string in_location, double in_area, double in_size, WaterArea parent_object,  WaterArea child_object)
{
	add_parent(parent_object);
	add_child(child_object);
}



void Sea::add_parent(WaterArea parent_object)
{
	parent_water_areas.push_back(parent_object);
}

void Sea::add_child(WaterArea child_object)
{
	child_water_areas.push_back(child_object);
}


void Sea::add_parents(std::vector<WaterArea> parent_objects)
{
	parent_water_areas.insert(parent_water_areas.end(), parent_objects.begin(), parent_objects.end());
}

void Sea::add_childs(std::vector<WaterArea> child_objects)
{
	child_water_areas.insert(child_water_areas.end(), child_objects.begin(), child_objects.end());
}

std::vector<WaterArea> Sea::get_parent_objects()
{
	return parent_water_areas;
}

std::vector<WaterArea> Sea::get_child_objects()
{
	return child_water_areas;
}








