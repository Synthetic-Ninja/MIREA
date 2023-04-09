#define WATTERAREA_INCLUDED

#include <vector>
#include <string>


#ifdef WATTERAREA_INCLUDED
#include "waterarea.h"
#endif

class Bay: public WaterArea
{
private:
	std::vector<WaterArea> parent_water_areas;

public:
	Bay();
	Bay(std::string in_name, std::string in_location, double in_area, double in_size);
	Bay(std::string in_name, std::string in_location, double in_area, double in_size, WaterArea parent_object);
	Bay(std::string in_name, std::string in_location, double in_area, double in_size, std::vector<WaterArea> parent_objects);
	std::vector<WaterArea> get_parents();
	void add_parent(WaterArea parent_object);
	void add_parents(std::vector<WaterArea> parent_objects);
};