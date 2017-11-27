#include <map>
#include <fstream>
#include <iostream>

class Object {
	size_t x_, y_;
	char type_;
	
public:
	Object() = delete;
	Object(size_t x, size_t y, char c) :x_(x), y_(y), type_(c){}
	
	size_t x_coordinate() const noexcept { return x_; }
	size_t y_coordinate() const noexcept { return y_; }
	char return_type() const noexcept { return type_; }

	std::pair<const Object, bool> find_nearest(std::multimap<const Object, bool>& Map) const noexcept;
	bool operator< (const Object& B) const noexcept;
	
	~Object() = default;
};

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

bool Object::operator< (const Object& B) const noexcept{
	if (x_ < B.x_) return true;
	else return false;
}

std::ostream& operator<< (std::ostream& of, const Object& A) {
	of <<'(' <<  A.x_coordinate() << ',' << A.y_coordinate() << ") type:" << A.return_type();
	return of;
}