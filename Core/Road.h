#pragma once
#include <utility>
#include <vector>
#include "../Generic.h"
#include "SingleLight.h"

using std::pair;
using std::vector;

class LightGroup;
class Line;
class Scheduler;

typedef Line LineType;
typedef vector<LineType> LineContainer;

class Road
{
public:
	//Road(int road_id, int num_of_lines, string road_name);

	Road();
	~Road();
	Road(const Road& rhs);
 	int num_of_lines() const;
// 	void set_num_of_lines(int num_of_lines) { num_of_lines_ = num_of_lines; }
	
	int road_id() const { return road_id_; }
	void set_road_id(const int& road_id) { road_id_ = road_id; }
	
	string road_name() const { return road_name_; }
	void set_road_name(const string& road_name) { road_name_ = road_name; }
	
	bool operator != (const Road& rhs);
	bool  operator==(const Road& rhs);
	
	float length() const { return length_; }
	void set_length(const float& length) { length_ = length; }
	
	bool add_line(LineType& lt);
	bool del_line(LineType& lt);

	void set_direction(int index,Direction dir);
	//LightStatus light_status(const Line& line) const;
	void display(std::ostream& os);
	void displayall( std::ostream& os);

	Line* line_at(int line_index) ;
	LineContainer* lines() const { return lines_; }
	void set_lines(LineContainer*& lines) { lines_ = lines; }
	
	LightGroup* light_group() const { return light_group_; }
	void set_light_group(LightGroup* light_group);
	
// 	LightGroup* next_light_group  () const{ return next_light_group_; }
// 	void set_next_light_group(LightGroup* next_light_group);
	
	Scheduler* scheduler() { return scheduler_; }
	void set_scheduler(Scheduler* scheduler) { scheduler_ = scheduler; }
	
	Cross* my_cross() const { return my_cross_; }
	void set_my_cross(Cross* my_cross) { my_cross_ = my_cross; }
	
	Road* left_road() const { return left_road_; }
	void set_left_road(Road*& left_road) { left_road_ = left_road; }
	Road* right_road() const { return right_road_; }
	void set_right_road(Road*& right_road) { right_road_ = right_road; }
	Road* front_road() const { return front_road_; }
	void set_front_road(Road*& front_road) { front_road_ = front_road; }
	
	int num_of_vehicles();
	bool add_line_light(LineType& line,SingleLight& sl);
	//int index() const { return index_; }
	//void set_index(const int& index) { index_ = index; }
	int duration();
	void set_duration(int sec);
	void copied();
	void duration_decrease();
	bool no_drivers();
	bool road_dir_conflict(Direction d, Road& another_r, Direction another_d);
	bool is_right(Road& r);
	bool is_left(Road& r);
	bool is_front(Road& r);
private:
	
	//int index_;
	//int num_of_lines_;
	int road_id_;
	string road_name_;
	float length_;
	LineContainer* lines_;
	LightGroup* light_group_;
	//LightGroup* next_light_group_;
	Scheduler* scheduler_;
	Cross* my_cross_;

	Road* left_road_;
	Road* right_road_;
	Road* front_road_;
};

