#include <vector>
#include <string>
#include "waterarea.h"


class Ocean: public WaterArea
{
private:
	std::vector<WaterArea> child_water_areas;

public:
	Ocean();
	Ocean(WaterArea child_object);
	Ocean(std::string in_name, std::string in_location, double in_area, double in_size, WaterArea child_object);
	Ocean(std::string in_name, std::string in_location, double in_area, double in_size);
	Ocean(std::vector<WaterArea> child_objects);
	Ocean(std::string in_name, std::string in_location, double in_area, double in_size, std::vector<WaterArea> child_objects);
	std::vector<WaterArea> get_childs();
	void add_child(WaterArea child);
	void add_childs(std::vector<WaterArea> childs);
};