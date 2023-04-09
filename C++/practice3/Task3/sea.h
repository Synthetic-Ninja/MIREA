#include <vector>
#include <string>
#include "waterarea.h"


class Sea: public WaterArea
{
private:
	std::vector<WaterArea> parent_water_areas;
	std::vector<WaterArea> child_water_areas;

public:
	Sea();
	Sea(std::string in_name, std::string in_location, double in_area, double in_size);
	Sea(std::string in_name, std::string in_location, double in_area, double in_size, WaterArea parent_object,  WaterArea child_object);
	void add_parent(WaterArea parent_object);
	void add_child(WaterArea child_object);
	void add_parents(std::vector<WaterArea> parent_objects);
	void add_childs(std::vector<WaterArea> child_objects);
	std::vector<WaterArea> get_parent_objects();
	std::vector<WaterArea> get_child_objects();

};