#include "stdafx.h"

#include "Line.h"
#include "Road.h"
#include "LightGroup.h"
#include "../Scheduler/Scheduler.h"
Road::Road()
{
	lines_ = new LineContainer();
	light_group_ = new LightGroup();
}

Road::Road(const Road& rhs )
{
	road_id_ = rhs.road_id_;
	road_name_ = rhs.road_name_;
	length_ = rhs.length_;
	lines_ = new LineContainer(*rhs.lines());
	light_group_ = new LightGroup(*rhs.light_group());
	copied();
}

void Road::copied() {
	for_each(lines_->begin(),lines_->end(),[&](Line& l) {
		l.set_my_road(this);
	});
}

Road::~Road(void)
{
	if (lines_!=NULL) {
		delete lines_;
	}
	delete light_group_;
}



void Road::display( std::ostream& os )
{
	os<<"road_id_: "<<road_id_<<"\t";
	os<<"road_name_: "<<road_name_<<"\t";
	//	os<<"num_of_lines_: "<<num_of_lines_<<"\t";
	// 	if (road_->empty()) {
	// 		os<<"No lines to show"<<std::endl;
	// 		return;
	// 	}
	//	auto tl_iter = road_->begin();
	//	for(;tl_iter!=road_->end();++tl_iter) {
	//		tl_iter->display(os);
	//	}
}

void Road::displayall( std::ostream& os) {
	os<<"\troad_id_: "<<road_id_<<"\t";
	os<<"road_name_: "<<road_name_<<"\t";
	//	os<<"num_of_lines_: "<<num_of_lines_<<std::endl;
	// 	if (road_->empty()) {
	// 		os<<"No lines to show"<<std::endl;
	// 		return;
	// 	}
	// 	auto tl_iter = road_->begin();
	// 	for(;tl_iter!=road_->end();++tl_iter) {
	// 		tl_iter->displayall(os);
	// 	}
}
// Road::Road( int road_id, int num_of_lines, string road_name ) :
// 	road_id_(road_id), road_name_(road_name)
// {
// //	road_ = new RoadType(num_of_lines_);
// }

void Road::set_direction( int index,Direction dir )
{
	if (index < lines_->size()) {
		lines_->at(index).set_index(index);
		lines_->at(index).set_direction(dir);
		//lines_->at(index).first = index;
		//lines_->at(index).second = dir;
	}
}

void Road::duration_decrease() {
	light_group_->time_decrease();
	if (duration() == 0)
	{
		// 		set_next_light_group(&(scheduler_->calculate(*this)));
		// 		set_light_group(next_light_group_);
		// 		set_next_light_group(&(scheduler_->calculate(*this)));
		set_light_group(&(scheduler_->calculate(*this)));
	}
}

bool Road::add_line( LineType& lt )
{
	return add_unique<LineType,LineContainer>(lt,lines_);
}

bool Road::del_line( LineType& lt )
{
	return search_for_delete<LineType,LineContainer>(lt,lines_);
}

bool Road::add_line_light( LineType& line,SingleLight& sl )
{
	if (!isAcceptable(line.direction() ,sl.direction()))
		return false;
	lines_->push_back(line);
	light_group_->add_light(sl);
	return true;
}

Line* Road::line_at( int line_index )
{
	return &(lines()->at(line_index));
}

bool Road::no_drivers() {
	for(int line_index=0; line_index<=num_of_lines(); ++line_index) {
		if ( !(lines_->empty()) )
		{
			return false;
		}
	}
	return true;
}

int Road::num_of_lines() const
{
	return lines_->size();
}

void Road::set_duration( int sec )
{
	light_group_->set_duration(sec);
}

int Road::duration()
{
	return light_group_->duration();
}

bool Road::operator!=( const Road& rhs )
{
	return 
		road_id_ != rhs.road_id_ ||
		road_name_ != rhs.road_name_ ||
		length_ != rhs.length_ ||
		//equal(lines_->begin(),lines_->end(),rhs.lines_->begin()) ||
		//*lines_ != *rhs.lines_ ||
		*light_group_ != *rhs.light_group_;
}

bool Road::operator==( const Road& rhs )
{
	return !(*this != rhs);
}

void Road::set_light_group( LightGroup* light_group )
{
	if (light_group_!=light_group && light_group!=NULL)
	{
		delete light_group_;
		light_group_ = new LightGroup(*light_group);
	}
	copied();
}

// void Road::set_next_light_group( LightGroup* next_light_group )
// {
// 	if (next_light_group_!=next_light_group && next_light_group_!= NULL)
// 	{
// 		delete next_light_group_;
// 		next_light_group_ = new LightGroup(*next_light_group);
// 	}
// }
// 
// 

bool Road::is_right(Road& r) {
	if (right_road_ != NULL)
	{
		return r == *right_road_;
	}
	return false;
}

bool Road::is_left(Road& r) {
	if (left_road_ != NULL)
	{
		return r == *left_road_;
	}
	return false;
}

bool Road::is_front(Road& r) {
	if (front_road_ != NULL)
	{
		return r == *front_road_;
	}
	return false;
}

bool Road::road_dir_conflict(Direction d, Road& another_r, Direction another_d) {
	switch (d)
	{
	case STRAIGHT:
		if (is_left(another_r))
		{
			return another_d == STRAIGHT;
		}
		else if (is_front(another_r))
		{
			return another_d ==LEFT;
		}
		else if (is_right(another_r))
		{
			return another_d == STRAIGHT ||
				another_d == LEFT;
		}
		break;
	case LEFT:
		if (is_left(another_r))
		{
			return another_d ==LEFT ||
				another_d == STRAIGHT;
		}
		else if (is_front(another_r))
		{
			return another_d == STRAIGHT;
		}
		else if (is_right(another_r))
		{
			return another_d == LEFT;
		}
		break;
	case RIGHT:
		return false;
		break;
	case UTRUN:
		break;
	case STRAIGHT_LEFT:
		break;
	case STRAIGHT_RIGHT:
		break;
	case STRAIGHT_UTRUN:
		break;
	case LEFT_UTRUN:
		break;
	case ALL:
		for (int line_index=0; line_index<num_of_lines(); line_index++)
		{
// 			if (line_at(line_index)->direction()==ALL)
// 			{
				if (road_dir_conflict(
					line_at(line_index)->direction(),
					another_r,another_d))
				{
					return true;
				}
			//}

		}
		return false;
		break;
	default:
		break;
	}
	return true;
}

int Road::num_of_vehicles()
{
	return accumulate(lines_->begin(),lines_->end(),0,[&](int sum, Line& l) {
		return sum+l.num_of_vehicles();
	});
}
