#include "objects.h"

bool construct(std::multimap<const Object, bool>& Map) noexcept {
	if (Map.empty()) return false;
	
	auto it = Map.begin();
	it->second = true;
	++it;

	while (it != Map.end()){
		if (!it->second) {
			
			size_t y_road, x_road = it->first.x_coordinate();
			
			//std::pair<const Object, bool> nearest_pair = it->first.find_nearest(Map);
			auto right_it = it;
			--right_it;

			auto nearest_pair = it->first.find_nearest(Map, Map.cbegin(), right_it);
			if (!nearest_pair->second) return false;
			const Object nearest_object = nearest_pair->first;
			 

			if (nearest_object.y_coordinate() == it->first.y_coordinate()) {
				y_road = it->first.y_coordinate();
				if(nearest_object.x_coordinate() != it->first.x_coordinate()) 
					--x_road;
			}
			else if (nearest_object.y_coordinate() < it->first.y_coordinate()) {
				for (y_road = it->first.y_coordinate() - 1; y_road > nearest_object.y_coordinate(); --y_road) {
					Object road(x_road, y_road, obj_type::road);
					Map.insert({ road, 1});
				}
			}
			else{
				for (y_road = it->first.y_coordinate() + 1; y_road < nearest_object.y_coordinate(); ++y_road) {
					Object road(x_road, y_road, obj_type::road);
					Map.insert({ road, 1 });
				}
			}

			while (x_road != nearest_object.x_coordinate()) {
				Object road(x_road, y_road, obj_type::road);
				Map.insert({ road, 1 });
				--x_road;
			}
			it->second = true;
		}
		++it;
	}
	return true;
}
