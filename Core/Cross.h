#pragma once
#include <vector>
#include "../Generic.h"
//#include "Road.h"

class Road;
class LightGroup;



class Cross
{
public:
//	Cross(int cross_id, string cross_name, int num_of_roads, RoadContainer& cross);
	Cross();
	~Cross(void);
	Cross(Cross& rhs);

	bool operator != (const Cross& rhs);
	bool operator == (const Cross& rhs);

	int cross_id() const {return cross_id_;}
	void set_cross_id(int cross_id){ cross_id_ = cross_id;}

	string cross_name() const { return cross_name_;}
	void set_cross_name(string name) {cross_name_ = name;}

 	int  num_of_roads() const;
// 	void set_num_of_roads(const int & num_of_roads) { num_of_roads_ = num_of_roads; }

// 	RoadContainer*& crosses() {
// 		return roads_;
// 	}

	bool add_road(Road& road);
	bool del_road( Road& road );

	bool add_light_group(LightGroup& lg);
	bool del_light_group(LightGroup& lg);

	void display(std::ostream& os);
	void displayall( std::ostream& os );

// 	LightGroupContainer*& light_groups() {
// 		return light_groups_;
// 	}
	RoadContainer* roads() const { return roads_; }
	void set_roads(RoadContainer*& roads) { roads_ = roads; }
	
	void set_scheduler(Scheduler* s);
	Road* road_at(int road_index);

	RoadContainer* roads() { return roads_; }
	void time_decrease();
	void copied();
private:

	

	int cross_id_;
	string cross_name_;
	RoadContainer* roads_;
	//LightGroupContainer* light_groups_;
};

