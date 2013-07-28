

#include "stdafx.h"

#include "FixedScheduler.h"
#include "../Core/Line.h"
#include "../Core/Road.h"
#include "../Emulator/Emulator.h"
#include "../Emulator/Driver.h"
#include "../Core/Cross.h"


FixedScheduler::FixedScheduler(void)
{
	initial();
	set_name(CString(_T("定额配时")));
}


FixedScheduler::~FixedScheduler(void)
{

}

// float DefaultScheduler::cal_vehicle( Vehicle& v )
// {
// 	
// }
// 
// float DefaultScheduler::cal_line( Line& l )
// {
// 	
// }
// 
// float DefaultScheduler::cal_direction( Road& r,Direction& dir )
// {
// 	
// }
// 
// 
// float DefaultScheduler::cal_road( Road& r )
// {
// 
// }

void FixedScheduler::first_time_calculate() {
	if (cross_ != NULL) 
	{
		int red_time =0;
		cross_->road_at(0)->set_light_group(&DEF_GREEN_LIGHT);
		cross_->road_at(0)->set_duration(min_green_time_);
		for (int road_index=1; road_index<cross_->num_of_roads(); ++road_index)
		{
			red_time += min_green_time_ + DEF_YELLOW_TIME;
			cross_->road_at(road_index)->set_light_group(&DEF_RED_LIGHT);
			cross_->road_at(road_index)->set_duration(red_time);
		}
	}
}

LightGroup FixedScheduler::calculate( Road& r )
{
	LightGroup* last_group = r.light_group();
	int red_base = DEF_GREEN_LIGHT.duration() + DEF_YELLOW_LIGHT.duration();
	LightGroup red_light = LightGroup(DEF_RED_LIGHT);
	LightGroup green_light = LightGroup(DEF_GREEN_LIGHT);
	switch (last_group->light_enabled(ALL))
	{
	case RED:
		green_light.set_duration(find_green_time(r));
		return green_light;
		break;
	case YELLOW:

		red_light.set_duration(cal_red_time(r));
		return red_light;
		break;
	case GREEN:
		return DEF_YELLOW_LIGHT;
		break;
	}
}

int FixedScheduler::find_green_time(Road& r) {
	return min_green_time_;
}

int FixedScheduler::cal_red_time(Road& r) {
	return
		accumulate(cross_->roads()->begin(),cross_->roads()->end(),0,
		[&](int red_light_sum, Road& lambda_r) {
			if (lambda_r != r)
			{
				return red_light_sum + find_green_time(lambda_r) + DEF_YELLOW_TIME;
			}
			else
			{
				return red_light_sum;
			}
		});
}
void FixedScheduler::initial()
{
	//cross_ = GLOBAL_EMU->cross();
	name_ = L"定额配时";
	min_green_time_ = 20;
	max_red_time_ = 100;

}
