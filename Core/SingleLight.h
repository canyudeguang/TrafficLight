#pragma once

#include "../Generic.h"




class SingleLight
{
public:
	explicit SingleLight(Direction direction=ALL, 
		LightColor color=WRONG,
		bool on=false): 
	direction_(direction), color_(color), on_(on) {
		}
	Direction direction() const { return direction_; }
	void set_direction(const Direction& direction) { direction_ = direction; }
	
	LightColor color() const { return color_; }
	void set_color(const LightColor& color) { color_ = color; }                                                                                                                                                                                                            
	
	bool light_on() const { return on_; }
	void set_light_on(const bool& light_on) { on_ = light_on; }
	
	bool operator!=(const SingleLight rhs) const {
		return color_!=rhs.color_ 
			|| direction_!=rhs.direction_;
	}

	bool operator==(const SingleLight rhs) const {
		return !(*this!=rhs);
	}

	bool operator < (const SingleLight& rhs) const {
		return dir_level(direction_) > dir_level(rhs.direction_);
	}

	bool operator <= (const SingleLight& rhs) const {
		return dir_level(direction_) > dir_level(rhs.direction_) ||
			dir_level(direction_) == dir_level(rhs.direction_);
	}

	bool operator >= (const SingleLight& rhs) const {
		return dir_level(direction_) < dir_level(rhs.direction_) ||
			dir_level(direction_) == dir_level(rhs.direction_);
	}

	bool operator > (const SingleLight& rhs) const {
		return dir_level(direction_) < dir_level(rhs.direction_);
	}
private:
	Direction direction_;
	LightColor color_;
	bool on_;
};

