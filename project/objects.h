#include <map>
#include <fstream>
#include <iostream>
#include <iterator> 

class Object;
enum obj_type {object, road};
using const_map_it = std::multimap<const Object, bool>::const_iterator;

class Object {
	size_t x_, y_;
	obj_type type_;
	
public:
	Object() = delete;
	Object(size_t x, size_t y, obj_type c) :x_(x), y_(y), type_(c){}
	
	size_t x_coordinate() const noexcept { return x_; }
	size_t y_coordinate() const noexcept { return y_; }
	obj_type return_type() const noexcept { return type_; }

	//std::pair<const Object, bool> find_nearest(std::multimap<const Object, bool>& Map) const noexcept;
	const_map_it Object::find_nearest(std::multimap<const Object, bool>& Map, const_map_it left, const_map_it right) const noexcept;
	bool operator< (const Object& B) const noexcept;
	
	~Object() = default;
};

const_map_it Object::find_nearest(std::multimap<const Object, bool>& Map, const_map_it left, const_map_it right) const noexcept{
	if (Map.size() < 2) return Map.cbegin();
	
	if (left == right) { 
		return left;
	}

	auto middle = left;
	std::advance(middle, std::distance(left, right) / 2);
	
	auto left_pair = this->find_nearest(Map, left, middle);
	auto right_pair = this->find_nearest(Map, ++middle, right);
	size_t left_distance(0), right_distance(0);

	if (left_pair->first.y_ >= y_)
		left_distance = (x_ - left_pair->first.x_) + (left_pair->first.y_ - y_);
	else 
		left_distance = (x_ - left_pair->first.x_) + (y_ - left_pair->first.y_);

	if (right_pair->first.y_ >= y_)
		right_distance = (x_ - right_pair->first.x_) + (right_pair->first.y_ - y_);
	else
		right_distance = (x_ - right_pair->first.x_) + (y_ - right_pair->first.y_);

	if (left_distance <= right_distance) {
		return left_pair;
	}
	else {
		return right_pair;
	}
}


/*
std::pair<const Object, bool> Object::find_nearest(std::multimap<const Object, bool>& Map) const noexcept {
	if (Map.size() < 2) return {*this, 0};
	
	size_t distance(0);
	auto it(Map.begin());
	auto res_it(Map.end());
	
	
	while (it != Map.end() && it->first.x_ != x_ + 1 ) {
		if (it->second) {
			size_t current;
			if (y_ >= it->first.y_)
				 current = (x_ - it->first.x_) + (y_ - it->first.y_);
			else  current = (x_ - it->first.x_) + (it->first.y_ - y_);
			if (distance == 0 || distance > current) {
				distance = current;
				res_it = it;
			} 
		}
		++it;
	}
	
	if (res_it != Map.end()) return *res_it;
	else return { *this, 0 };
}
*/
bool Object::operator< (const Object& B) const noexcept{
	if (x_ < B.x_) return true;
	else return false;
}

std::ostream& operator<< (std::ostream& of, const Object& A) {
	std::string type;
	if (A.return_type()) type = "Road";
	else type = "Object";
	of <<'(' <<  A.x_coordinate() << ',' << A.y_coordinate() << ") type:" << type;
	return of;
}
