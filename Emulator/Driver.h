#pragma once
#include "../Observer.h"
#include "../Generic.h"
#include "../Core/Vehicle.h"

class LightGroup;
class Road;
class Line;

//extern const float NEAR_RANGE;


class DriverTraits {
	
public:
	DriverTraits():latency_(rand()%3/10.0f+0.4f),dis_to_pre_(rand()%5/10.0f+0.8f){}
	float latency() const { return latency_; }
	void set_latency(const float& latency) { latency_ = latency; }
	float dis_to_pre() const { return dis_to_pre_; }
	void set_dis_to_pre(const float& dis_to_pre) { dis_to_pre_ = dis_to_pre; }
	
private:
	float latency_;
	float dis_to_pre_;
};

class Driver :
	public Observer
{
public:
	Driver(Vehicle v);
	Driver(LightGroup* light_group, Vehicle* previous_vehicle = NULL);
	~Driver(void);
	Driver(const Driver& rhs);
	void slow_down(float distance);
	void stop(float distance);
	void accelarate();
	void do_it();
	void update(Subject* changed_sub);
	
	/*
	 *	decided by if the distance is enough for breaking to pre_vehicle's speed
	 */
	bool is_near(float distance);

	Direction direction() const { return direction_; }
	void set_direction(const Direction& direction) { direction_ = direction; }
	
	Vehicle* vehicle() { return &vehicle_; }
	void set_vehicle(Vehicle v);
	
	float latency() const { return traits_.latency(); }
	void set_latency(const float& latency) { traits_.set_latency(latency); }

	float dis_to_pre() const { return traits_.dis_to_pre(); }
	void set_dis_to_pre(const float& dis_to_pre) { traits_.set_dis_to_pre(dis_to_pre); }
	
	LightGroup* light_group() const { return light_group_; }
	void set_light_group(LightGroup* light_group) { light_group_ = light_group; }
	Vehicle* my_vehicle();
	Vehicle* pre_vehicle();
	Road* my_road() const { return my_road_; }
	void set_my_road(Road*& my_road);
	int line_index() const { return line_index_; }
	void set_line_index(const int& line_index) { line_index_ = line_index; }
	float front_distance();
	void do_last_past();

	bool operator != (const Driver& rhs);
	Driver& operator = (const Driver& rhs);
	bool operator==(const Driver& rhs);
	bool i_am_dieing();
	void catch_up(float pre_speed, float distance);
	float front_vehicle_distance();
	Line* my_line();
	bool overlapped();
	float back_distance();
	Vehicle* next_vehicle();
	float reasonable(float a);
	float safe_distance();
	bool waiting();
private:
	Direction direction_;
	DriverTraits traits_;
	Vehicle vehicle_;
	Road* my_road_;
	int line_index_;
	LightGroup* light_group_;
	bool stopping;
	int wait_count_;

};
