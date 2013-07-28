
#pragma once
#include "../stdafx.h"

#include "../Generic.h"
#include "SingleLight.h"

class Road;
class Cross;
class Vehicle;



typedef VehicleContainer::iterator itertor;
class VehicleDistanceCompare {
	public:
		bool operator()  (  Vehicle& lhs,  Vehicle& rhs );
		bool operator()  (  Driver& lhs,  Driver& rhs );
};



class Line
{
public:
	Line(int line_id, 
		Direction direction);

	Line();
	Line(const Line& rhs);
	~Line(void);
	

	bool operator != (const Line& rhs);

	int index() const { return index_; }
	void set_index(const int& index) { index_ = index; }
	
// 	string line_name() const { return line_name_; }
// 	void set_line_name(const string& line_name) { line_name_ = line_name; }
		
	bool operator==(const Line& rhs);

	/*void add_vehicle(Vehicle& v);*/

//	void clear_vehicles();
//	VehicleContainer* vehicles() const;
//	void set_vehicles(VehicleContainer* vehicles);

//	Road* p_my_road() const { return my_road_; }
//	void set_p_my_road(Road* p_my_road) { my_road_ = p_my_road; }

	bool operator < (const Line rhs);

	int num_of_vehicles();
	
	void display(std::ostream& os);
	void displayall(std::ostream& os);

	Vehicle& vehicle_at(int index);
	Direction direction() const { return direction_; }
	void set_direction(const Direction& direction) { direction_ = direction; }

	Road* my_road() const { return my_road_; }
	void set_my_road(Road* my_road);
	
	DriverContainer* drivers() const { return drivers_; }
	void set_drivers(DriverContainer*& drivers);

	float drivers_per_second() const { return drivers_per_second_; }
	void set_drivers_per_second(float driver_gen_speed) { drivers_per_second_ = driver_gen_speed; }
	int processed_count() const { return processed_count_; }
	void set_processed_count(int processed_count) { processed_count_ = processed_count; }
	
	void set_num_of_vehicles(int n_vehicles);
	void add_driver(Driver& d);
	void del_driver(Driver& d);
	Vehicle* pre_vehicle(Driver& d);
	Vehicle* next_vehicle(Driver& d);
	void reorder();
	void copied();
	void time_for_add_driver();
	void processed();
private:
	int index_;
	Direction direction_;
	//VehicleContainer* vehicles_;
	Road* my_road_;
	DriverContainer* drivers_;
	
	float drivers_per_second_;
	int processed_count_;



	void sort_vehicles();
	

	//int line_type_;
	// 	Cross* from_cross_;
	// 	Cross* to_cross_;
};

