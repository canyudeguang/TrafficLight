#pragma once
#include "../Core/Vehicle.h"



struct Factor
{
	Factor(float fac=0,float weight=0):fac_(fac),weight_(weight){}
	float fac_;
	float weight_;
	float cal(float value) {
		return value*fac_*weight_;
	}
	float r_cal(float value) {
		return fac_/value*weight_;
	}
};


class VehicleTraits
{
public:
	VehicleTraits(){}
	~VehicleTraits(){}

	Factor max_accel_fac() const { return max_accel_fac_; }
	void set_max_accel_fac(const Factor& max_accel_fac) { max_accel_fac_ = max_accel_fac; }
	Factor max_break_fac() const { return max_break_fac_; }
	void set_max_break_fac(const Factor& max_break_fac) { max_break_fac_ = max_break_fac; }
	Factor slow_speed_fac() const { return slow_speed_fac_; }
	void set_slow_speed_fac(const Factor& slow_speed_fac) { slow_speed_fac_ = slow_speed_fac; }
	Factor max_speed_fac() const { return max_speed_fac_; }
	void set_max_speed_fac(const Factor& max_speed_fac) { max_speed_fac_ = max_speed_fac; }
	Factor cur_speed_fac() const { return cur_speed_fac_; }
	void set_cur_speed_fac(const Factor& cur_speed_fac) { cur_speed_fac_ = cur_speed_fac; }
	Factor length_fac() const { return length_fac_; }
	void set_length_fac(const Factor& length_fac) { length_fac_ = length_fac; }


	float veh_vector(Vehicle& v) {
		return
			type_factor(v) +
			speed_factor(v) +
			length_factor(v);
	}

	// A scheduler can only know the factors below!
	float type_factor(Vehicle& v) {
		return 
			max_accel_fac().r_cal(v.max_accel()) +
			abs(max_break_fac().r_cal(v.max_break())) +
			max_speed_fac().r_cal(v.max_speed()) +
			slow_speed_fac().r_cal(v.slow_speed());
	}


	float speed_factor(Vehicle& v) {
		if (almost_equal(v.speed(),0.0f))
		{
			return cur_speed_fac().r_cal(0.1f);
		}
		return cur_speed_fac().r_cal(v.speed());
	}


	float length_factor(Vehicle& v) {
		return length_fac().cal(v.length());
	}
private:
	Factor max_accel_fac_;
	Factor max_break_fac_;
	Factor slow_speed_fac_;
	Factor max_speed_fac_;
	Factor cur_speed_fac_;
	Factor length_fac_;
};

