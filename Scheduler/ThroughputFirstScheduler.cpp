/************************************************************************/
/* 先算出红灯最长的那条路的绿灯时间，然后其他道路的绿灯时间根据比重设置
* 
* 红灯时间为其他路口的绿灯和黄灯时间总和*/
/************************************************************************/

#include "stdafx.h"
#include "ThroughputFirstScheduler.h"
#include "../Emulator/Emulator.h"
#include "../Globals.h"
#include "../Core/LightGroup.h"
#include "../Core/Road.h"
#include "../Core/Line.h"
#include "../Core/Cross.h"
#include "../Generic.h"

extern int DEF_MIN_GREEN = 15;
extern int DEF_MAX_RED = 120;
float GREEN_TIME_PER_VEHICLE = 1.8f;

// ThroughputFirstScheduler::ThroughputFirstScheduler(void):
// 	cur_period_(0),Scheduler(-1,-1)
// {
// 	cal_result_ = new RESULT_CONTAINER;
// 	//initial();
// }

ThroughputFirstScheduler::ThroughputFirstScheduler( 
	int min_green, int max_red) :
Scheduler(min_green,max_red),cur_period_(0)
{
	cal_result_ = new RESULT_CONTAINER;
	set_name(CString(_T("吞吐量优先")));
	//initial();
}


ThroughputFirstScheduler::~ThroughputFirstScheduler(void)
{
	delete cal_result_;
}


void ThroughputFirstScheduler::initial() {
	//cross_ = GLOBAL_EMU->cross();
	period_ = 1;
	road_start_ = NULL;
	name_ = L"吞吐量优先";
	cal_result_->resize(cross_->num_of_roads());
	for (int road_index=0; road_index<cross_->num_of_roads(); ++road_index)
	{
		/*for (int line_index=0; line_index<cross_->num_of_roads(); ++line_index)
		{
		if (
		find_if(cal_result_->begin(),cal_result_->end(),[&](RESULT& result) {
		return *result.road_ == *cross_->road_at(road_index) &&
		result.dir_ == cross_->road_at(road_index)->line_at(line_index)->direction();
		}) != cal_result_->end())
		{
		cal_result_->push_back(
		RESULT(cross_->road_at(road_index),
		cross_->road_at(road_index)->line_at(line_index)->direction()));
		}
		}*/
		cal_result_->at(road_index).road_ = cross_->road_at(road_index);

	}
	veh_traits_.set_max_accel_fac(Factor(8.0f,3));
	veh_traits_.set_max_break_fac(Factor(5.0f,2.5));
	veh_traits_.set_max_speed_fac(Factor(20.0f,2.5));
	veh_traits_.set_slow_speed_fac(Factor(4.0f,3));
	veh_traits_.set_cur_speed_fac(Factor(10.0f,2.5));
	veh_traits_.set_length_fac(Factor(3.0f,3.5));
}

void ThroughputFirstScheduler::first_time_calculate() {
	if (!initialized)
	{
		initial();
		initialized=true;
	}
	if (cross_ != NULL)
	{
		cal_results();
		int red_time = 0;
		cross_->road_at(0)->set_light_group(&DEF_GREEN_LIGHT);
		cross_->road_at(0)->set_duration(find_green_time(*cross_->road_at(0)));
		for (int road_index=1; road_index<cross_->num_of_roads(); ++road_index)
		{
			red_time += cal_result_->at(road_index-1).green_time_ + DEF_YELLOW_TIME;
			cross_->road_at(road_index)->set_light_group(&DEF_RED_LIGHT);
			cross_->road_at(road_index)->set_duration(red_time);
		}
	}
}

LightGroup ThroughputFirstScheduler::calculate( Road& r )
{
	if (!initialized)
	{
		initial();
		initialized=true;
	}
	if (road_start_ == NULL)
	{
		road_start_ = &r;
	}
	LightGroup* last_group = r.light_group();
	if (*road_start_ == r)
	{
		++cur_period_;
		if (cur_period_/3 == period_)
		{
			//cal_results();
			first_time_calculate();
			cur_period_=0;
			return *r.light_group();
		}

	}
	switch (last_group->light_enabled(ALL))
	{
	case RED:
		return now_is_red(r);
		break;
	case YELLOW:
		return now_is_yellow(r);
		break;
	case GREEN:
		return now_is_green(r);
		break;
	}
}

float ThroughputFirstScheduler::cal_abc( Road& r )
{
	float sum_abc = 0;
	int my_index = 0;
	for (int road_index=0; road_index<cross_->num_of_roads(); ++road_index)
	{
		if (*cross_->road_at(road_index) != r) 
		{
			sum_abc += cal_result_->at(road_index).road_sum_;
		}
		else
		{
			my_index = road_index;
		}
	}

	sum_abc /= cal_result_->at(my_index).road_sum_;
	return sum_abc;
}

//算出所有路的总和和各自的绿灯时间，存放在cal_result_里
void ThroughputFirstScheduler::cal_results()
{
	for (int road_index = 0; road_index < cross_->num_of_roads(); ++road_index)
	{
		cal_result_->at(road_index).road_sum_ = cal_road(*cross_->road_at(road_index));
	}
	result_sum_ = 
		accumulate(cal_result_->begin(),cal_result_->end(),0.0f,[&](float sum,RESULT result) {
			return sum+result.road_sum_;
	});

	//先找出红灯最长的那条路，即绿灯最短的那条，计算它的绿灯时间
	auto min_green_iter = min_element(cal_result_->begin(),cal_result_->end(),[&](RESULT& a,RESULT& b) {
		return a.road_sum_ < b.road_sum_;
	});
	if (min_green_iter->road_->no_drivers())
	{
		min_green_iter->green_time_ = min_green_time_;
	}
	else
	{
		int needed_green = GREEN_TIME_PER_VEHICLE * min_green_iter->road_->num_of_vehicles();
		min_green_iter->green_time_ = 
			min(
			(max_red_time_ - (cross_->num_of_roads()-1)*DEF_YELLOW_TIME) / cal_abc(*min_green_iter->road_),
			needed_green);
	}
	if (min_green_iter->green_time_ < min_green_time_)
	{
		min_green_iter->green_time_ = min_green_time_;
	}


	//算出其余道路的绿灯时间
	for (int road_index = 0; road_index < cross_->num_of_roads(); ++road_index)
	{
		if (*cross_->road_at(road_index) != *min_green_iter->road_)
		{
			if (cross_->road_at(road_index)->no_drivers())
			{
				cal_result_->at(road_index).green_time_ = 
					min_green_time_;
			} 
			else
			{
				int green_time = cal_result_->at(road_index).road_sum_ / min_green_iter->road_sum_ * min_green_iter->green_time_;
				if (green_time<min_green_time_)
				{
					cal_result_->at(road_index).green_time_ = min_green_time_;
					break;
				}
				cal_result_->at(road_index).green_time_ = green_time;
			}

		}
	}

}

int ThroughputFirstScheduler::find_green_time(Road& r) {
	return (find_if(cal_result_->begin(),cal_result_->end(),[&](RESULT& result) {

		return *(result.road_) == r;
	}))->green_time_;
}

int ThroughputFirstScheduler::cal_red_time(Road& r) {
	return
		accumulate(cal_result_->begin(),cal_result_->end(),0,
		[&](int red_light_sum, RESULT& result) {
			if (*result.road_ != r)
			{
				return red_light_sum + result.green_time_ + DEF_YELLOW_TIME;
			}
			else
			{
				return red_light_sum;
			}
	});
}

LightGroup ThroughputFirstScheduler::now_is_red(Road& r) {
	LightGroup next_light = DEF_GREEN_LIGHT;
	next_light.set_duration(find_green_time(r));
	return next_light;

}

LightGroup ThroughputFirstScheduler::now_is_green(Road& r) {
	LightGroup next_light = DEF_YELLOW_LIGHT;
	next_light.set_duration(DEF_YELLOW_TIME);
	return next_light;
}

LightGroup ThroughputFirstScheduler::now_is_yellow( Road& r )
{
	LightGroup next_light = DEF_RED_LIGHT;
	next_light.set_duration(cal_red_time(r));
	return next_light;
}


void ThroughputFirstScheduler::sort_results() {
	std::sort(cal_result_->begin(),cal_result_->end(),
		[&](RESULT& lhs, RESULT&rhs) {
			return lhs.road_sum_ > rhs.road_sum_;
	});
}

//void ThroughputFirstScheduler::group_results() {
//	sort_results();
//	unique_ptr<RESULT> groups(new RESULT[cross_->num_of_roads()]);
//	
//}