#include "stdafx.h"
#include "Cross.h"
#include "Road.h"
#include "LightGroup.h"



Cross::Cross()
{
	roads_ = new RoadContainer();
	//light_groups_ = new LightGroupContainer();
}

Cross::Cross( Cross& rhs )
{
	cross_id_ = rhs.cross_id_;
	cross_name_ = rhs.cross_name_;
	roads_ = new RoadContainer(*rhs.roads());
	copied();
}

Cross::~Cross(void)
{
	//if (roads_ != NULL) 
		delete roads_;
// 	if (light_groups_ != NULL)
// 		delete light_groups_;
}

void Cross::copied() {
	for_each(roads_->begin(),roads_->end(),[&](Road& r) {
		r.set_my_cross(this);
	});
}
void Cross::time_decrease() {
	for_each(roads_->begin(),roads_->end(),[&](Road& r) {
		r.duration_decrease();

	});
}
bool Cross::add_road( Road& road )
{
// 	if ((find_if(roads_->begin(),roads_->end(), 
// 		[&](Road& r) {
// 			return r==road;
// 		})) == roads_->end() ) {
// 			roads_->push_back(road);
// 			return true;
// 	}
// 	return false;
	return add_unique<Road,RoadContainer>(road,roads_);
}

bool Cross::del_road( Road& road ) {
// 	auto road_iter = find_if(roads_->begin(),roads_->end(), 
// 		[&](Road& r) {return r==road;});
// 	if (road_iter!=roads_->end()) {
// 			roads_->erase(road_iter);
// 			return true;
// 	}
// 	return false;
	return search_for_delete<Road,RoadContainer>(road,roads_);
}


void Cross::display( std::ostream& os )
{
	os<<"cross_id_: "<<cross_id_<<"\t";
	os<<"cross_name_: "<<cross_name_<<"\t";
//	os<<"num_of_roads_: "<<num_of_roads_<<std::endl;
	for_each(roads_->begin(),roads_->end(),[&](Road& r) {
		os<<"\t"<<"road_id_: "<<r.road_id()<<"\t";
		os<<"road_name_: "<<r.road_name()<<"\t";
		os<<std::endl;
	});
}

void Cross::displayall(std::ostream& os )
{
	os<<"cross_id_: "<<cross_id_<<"\t";
	os<<"cross_name_: "<<cross_name_<<"\t";
//	os<<"num_of_roads_: "<<num_of_roads_<<std::endl;
	for_each(roads_->begin(),roads_->end(),[&](Road& r) {
		/*os<<"road_id_: "<<r.road_id()<<"\t";
		os<<"road_name_: "<<r.road_name()<<"\t";*/
		r.displayall(os);
		//os<<endl;
	});
}



Road* Cross::road_at( int road_index )
{
// 	return &*std::find_if(roads_->begin(),roads_->end(),[&](Road& r) {
// 		return (r.road_id() == road_id);
// 	});
	return roads_->empty()? NULL : &(roads_->at(road_index));
}

int Cross::num_of_roads() const
{
	if (roads_->empty())
	{
		return 0;
	}
	return roads_->size();
}

bool Cross::operator!=( const Cross& rhs )
{
	return
		cross_id_ != rhs.cross_id_ ||
		cross_name_ != rhs.cross_name_ ||
		equal(roads_->begin(),roads_->end(),rhs.roads_->begin());
		/**roads_ != *rhs.roads_;*/
}

bool Cross::operator==( const Cross& rhs )
{
	return !(*this != rhs);
}

void Cross::set_scheduler( Scheduler* s )
{
	for_each(roads_->begin(),roads_->end(),[&](Road& r) {
		r.set_scheduler(s);
	});
}



