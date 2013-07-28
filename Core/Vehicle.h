#pragma once

#include "../Generic.h"
#include "Position.h"




class Vehicle {
public:

	Vehicle(float length,
		float start_time,VehicleType type) : 
			length_(length), 
			//start_time_(start_time),
			type_(type) {}
	Vehicle(){}

	//getters and mutators
	float length() { return length_; }
	void set_length(const float& length) { length_ = length; }

	float max_accel() const { return type_.max_accel_; }
	void set_max_accel(const float& max_accel) { type_.max_accel_ = max_accel; }

	float max_break() const { return type_.max_break_; }
	void set_max_break(const float& max_break) { type_.max_break_ = max_break; }

	float slow_speed() const { return  type_.slow_speed_; }
	void set_slow_speed(const float& slow_speed) {  type_.slow_speed_ = slow_speed; }

	float length_min() const { return  type_.length_min_; }
	void set_length_min(const float& length_min) {  type_.length_min_ = length_min; }

	float length_max() const { return  type_.length_max_; }
	void set_length_max(const float& length_max) {  type_.length_max_ = length_max; }

	float max_speed() const { return type_.max_speed_; }
	void set_max_speed(const float& max_speed) { type_.max_speed_ = max_speed; }

	float speed() const { return speed_; }
	void set_speed(const float& speed) { speed_ = speed; }

	VehicleType type() { return type_; }
	void set_type(const VehicleType& type) { type_ = type; }

// 	
	float m_to_cross() const {
		return position_.meters_to_cross();
	}

	void set_m_to_cross(float m_to_cross) {
		position_.set_meters_to_cross(m_to_cross);
	}

	void vehicle_controler();

	Position position() const { return position_; }
	void set_position(const Position& position) { position_ = position; }
	
	Vehicle& operator = (const Vehicle& rhs){
		length_ = rhs.length_;
		type_ = rhs.type_;
		speed_ = rhs.speed_;
		position_ = rhs.position_;
		return *this;
	}

	bool operator!=(const Vehicle& rhs){
		return 
			memcmp(this,&rhs,sizeof(Vehicle)) != 0;
	}

	bool operator==(const Vehicle& rhs) {
		return !(*this != rhs);
	}
private:
	//车长
	float length_;

	// 起步至5m/s所需时间
// 	float start_time_;

	// 车子类型
	VehicleType type_;
	// 当前车速
	float speed_;

	//车辆位置
	Position position_;

	//所在的道
	//Line* my_line_;

};