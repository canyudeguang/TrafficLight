/************************************************************************/
/* 
车辆在遇到黄灯,红灯和正在闪的绿灯(在停车线1-2个车位以外的)会停车.停车时如果前面
没有车就在停车线停,若有车的话就间隔前车一部分距离停下.(无论什么灯当有大型前车遮
挡时看不到灯). 车辆在看到绿灯亮起之后起步,绝大部分是前车起步了后车才起步.起步到
一定速度保持大致匀速通过停车线,通过停车线后缓慢加速.
绿灯时间比较充裕,并且前面较空旷的时候会加速
绿灯时间比较少的时候会减速

2as = Vt^2 - V0^2
a = (Vt^2 - V0^2)/2s
Vt = sqrt(V0^2+2as)
Vt = v0 + at
*/


/************************************************************************/




/************************************************************************/
/* 模拟过程中考虑剩余红绿灯时间！！！                                                                  */
/************************************************************************/
#include "stdafx.h"


#include "Driver.h"
#include "../Core/Vehicle.h"
#include "../Core/LightGroup.h"
#include "../Core/Road.h"
#include "../Core/Line.h"
#include "../Globals.h"
using std::pow;

float DIE_METER = -6.0f;
Driver::Driver(Vehicle v):vehicle_(v),wait_count_(0)
{
	light_group_ = NULL;
}

Driver::Driver( const Driver& rhs )
{
	vehicle_ = rhs.vehicle_;
	direction_ = rhs.direction_;
	my_road_ = rhs.my_road_;
	line_index_ = rhs.line_index_;
	light_group_ = rhs.light_group_;
	wait_count_ = rhs.wait_count_;
}




Driver::~Driver(void)
{
}


Vehicle* Driver::pre_vehicle() {
	return my_line()->pre_vehicle(*this);
}

Vehicle* Driver::my_vehicle() {
	return &vehicle_;
}


float Driver::front_distance() {
	float front_vehicle_dis;
	if ( pre_vehicle() != NULL) {
		front_vehicle_dis = front_vehicle_distance() - dis_to_pre();
	}
	else {
		front_vehicle_dis = my_vehicle()->m_to_cross();
		if (front_vehicle_dis<0)
		{
			return MAX_REAL_METERS;
		}
	}

	return front_vehicle_dis;
}

float Driver::front_vehicle_distance() {
	if ( pre_vehicle() != NULL) {
		float m_vehicle = my_vehicle()->m_to_cross() - pre_vehicle()->m_to_cross() - pre_vehicle()->length();

		return m_vehicle;
	}
	return my_vehicle()->m_to_cross() > 0 ?
		my_vehicle()->m_to_cross():
		my_road_->length();
}
void Driver::update(Subject* changed_sub) {
	if (light_group_ != NULL) {
		*light_group_ = *(static_cast<LightGroup*>(changed_sub));
	}
}



bool Driver::is_near( float distance )
{
	float my_speed = my_vehicle()->speed();
	float to_speed = 0;
	float fac;
	if (almost_equal(distance,0))
	{
		return true;
	}
	if (pre_vehicle()!=NULL) 
	{
		if (pre_vehicle()->m_to_cross()>0)
		{
			to_speed = pre_vehicle()->speed();
		}
	}
	fac = (pow(to_speed,2) - (pow(my_speed,2))) /2 /distance;
	return (fac < my_vehicle()->max_break());
}

bool Driver::waiting() {
	float cur_count = wait_count_*TIME_DELIM_SEC;

	return cur_count<latency();
}




/************************************************************************/
/* (黄,红)  + 近  = 停
绿+ 近 = 减速
远 = 加速
远近区别= NEAR_RANGE
*/
/************************************************************************/

#ifndef _DEBUG
#define assert(x) ;
#endif
bool Driver::i_am_dieing() {
	return my_vehicle()->m_to_cross() < DIE_METER;
}

void Driver::do_last_past() {
	if ((my_vehicle()->m_to_cross()<1.0f/VIRTUAL_RATIO) && 
		stopping) {
			my_vehicle()->set_speed(0);
			return;
	}
	float cur_meter = my_vehicle()->m_to_cross();
	float next_meter = my_vehicle()->m_to_cross() - my_vehicle()->speed() *TIME_DELIM_SEC;

	my_vehicle()->set_m_to_cross(next_meter);

	if (front_distance()<0 && stopping)
	{

		my_vehicle()->set_m_to_cross(cur_meter);return;
	}
	//assert(front_distance()>=0);
}

Vehicle* Driver::next_vehicle() {
	return my_line()->next_vehicle(*this);
}

float Driver::back_distance() {
	if (next_vehicle() != NULL)
	{
		return next_vehicle()->m_to_cross() - my_vehicle()->m_to_cross() - my_vehicle()->length();
	}
	return REAL_METERS;
}

bool Driver::overlapped(){
	return front_distance()<2 || back_distance()<2 || front_vehicle_distance()<0;
}

void Driver::do_it() {
	//车辆按上一个时间片的驾驶员决策行驶
	do_last_past();

	//司机是否还没来得及反应
// 	if (waiting())
// 	{
// 		++wait_count_;
// 		return;
// 	}
// 	else
// 	{
// 		wait_count_=0;
// 	}
	if (!waiting())
	{
		wait_count_=0;
		return;
	}
	++wait_count_;

	float m_cross = my_vehicle()->m_to_cross();
	float m_vehicle = 0;
	if (pre_vehicle()!=NULL)
	{
		m_vehicle = front_vehicle_distance();
	}

	if (light_group_ != NULL) {
		if (m_cross < 0)					//车头已经超出停车线
		{
			accelarate();
			return;
		}
		if (almost_equal(m_cross,0))		//车辆处在停车线
		{
			if (light_group_->light_enabled(direction_) == GREEN)
			{
				accelarate();
			}
			else {
				stop(m_cross);
				if (my_road_->road_name() != "GeneratedRoad0")
				{
					return;
				}
			}
		}
		else if (is_near(m_cross)) {		//车辆距停车线较近

			if (pre_vehicle() == NULL)
			{
				if (light_group_->light_enabled(direction_) != GREEN)
				{
					stop(m_cross);
					if (my_road_->road_name() != "GeneratedRoad0")
					{
						return;
					}
				}
				else {
					slow_down(m_cross);
				}
			}
			else {
				catch_up(pre_vehicle()->speed(),front_distance());
			}
		}
		else {								//车辆距停车线较远
			if (pre_vehicle() == NULL)
			{
				accelarate();
			}
			else {
				catch_up(pre_vehicle()->speed(),front_distance());
			}
		}
	}
}

void Driver::slow_down( float distance )
{
	stopping = false;
	float cur_speed = my_vehicle()->speed();
	float to_speed = my_vehicle()->slow_speed();
	/*if (to_speed < cur_speed) {*/
	float a = pow(to_speed,2) - pow(cur_speed,2) / distance / 2;
	a = reasonable(a);

	my_vehicle()->set_speed( my_vehicle()->speed() + a * TIME_DELIM_SEC);
	if(my_vehicle()->speed()<0) my_vehicle()->set_speed(0);
	/*}*/
}

void Driver::stop( float distance )
{
	stopping = true;
	float cur_speed = my_vehicle()->speed();
	if (cur_speed > 0 && distance!=0)
	{
		float a = (0-pow(cur_speed,2)) / distance / 2;
		if (a < my_vehicle()->max_break())
		{
			a = my_vehicle()->max_break();
		}
		my_vehicle()->set_speed( my_vehicle()->speed() + a * TIME_DELIM_SEC);
		if (my_vehicle()->speed() <0)
		{
			my_vehicle()->set_speed(0);
		}
	}
	else {
		my_vehicle()->set_speed(0);
	}

}

float Driver::reasonable(float a) {
	if (a > my_vehicle()->max_accel())
	{
		a = my_vehicle()->max_accel();
	}
	if (a < my_vehicle()->max_break())
	{
		a = my_vehicle()->max_break();
	}
	return a;
}

float Driver::safe_distance() {
	if (pre_vehicle() != NULL)
	{
		float t1 = latency();						//本车反应时间
		float a1 = pre_vehicle()->max_break();		//前车刹车加速度
		float a2 = my_vehicle()->max_break();		//本车刹车加速度
		float v1 = pre_vehicle()->speed();			//前车速度
		float v2 = my_vehicle()->speed();			//本车速度
		float vk = v1 +a1*t1;						//本车开始刹车时前车的速度
		float s1 = v1*t1 +a1*t1*t1/2;				//前车刹车至vk速度时所走过的路程
		float s2 = v2*t1;							//驾驶员反应过来时车辆所行驶的距离
		if (almost_equal(a1,a2))
		{
			float safe = t1*(v2-v1)-a1*t1*t1/2;		//两车加速度相近时
			if (safe<0)
			{
				safe = 0;
			}
			return
				safe*SAFE_DISTANCE_MULTI*SAFE_DISTANCE_MULTI + dis_to_pre();
		}
		else
		{
			float safe = s2 - s1 + pow((v2-vk),2) /(a1-a2) /2;
			return 
				(safe) + dis_to_pre();
		}

	}
	return 0.0f;
}

void Driver::accelarate()
{
	stopping = false;
	float a;

 	if (almost_equal(my_vehicle()->m_to_cross(),0.0f) ||
 		my_vehicle()->m_to_cross()<0 ||
 		almost_equal(front_distance(),MAX_REAL_METERS))
 	{
		float next_speed = my_vehicle()->speed() + my_vehicle()->max_accel() * TIME_DELIM_SEC;
		my_vehicle()->set_speed(next_speed);
		return;
 	}
 	float accel_distance = front_distance() - safe_distance();
 	if (accel_distance < 0)
 	{
 		return;
 	}
 	a = (pow(my_vehicle()->max_speed(),2) - pow(my_vehicle()->speed(),2) )/2 /accel_distance;
 	a=reasonable(a);
 	float next_speed = my_vehicle()->speed() + a * TIME_DELIM_SEC;
 	assert(next_speed>0);
 	my_vehicle()->set_speed(next_speed);
}

void Driver::catch_up(float pre_speed, float distance) {
	stopping = false;
	if (distance<0)
	{
		my_vehicle()->set_speed(pre_speed*0.8);
		return;
	}
	float a = 0;
	if (front_distance() < safe_distance()*1.5)
	{
		a = my_vehicle()->max_break();
	}
	else
	{
		accelarate();
		return;
	}
	float next_speed = my_vehicle()->speed() + a * TIME_DELIM_SEC;
	if (next_speed<0)
	{
		next_speed = 0;
	}
	my_vehicle()->set_speed(next_speed);

}

Line* Driver::my_line() {
	return my_road_->line_at(line_index_);
}

void Driver::set_vehicle( Vehicle v )
{
	stopping = false;
	vehicle_ = v;
}

bool Driver::operator!=( const Driver& rhs )
{
	if (
		vehicle_!= rhs.vehicle_||
		line_index_ != rhs.line_index_ || 
		*my_road_ != *rhs.my_road_
		)
	{
		return true;
	}
	return false;
}

bool Driver::operator==( const Driver& rhs )
{
	return !(*this != rhs);
}

Driver& Driver::operator=( const Driver& rhs )
{
	direction_ = rhs.direction_;
	traits_ = rhs.traits_;
	vehicle_ = rhs.vehicle_;
	my_road_ = rhs.my_road_;
	line_index_ = rhs.line_index_;
	light_group_ = rhs.light_group_;
	return *this;
}

void Driver::set_my_road( Road*& my_road )
{
	my_road_ = my_road; 
	light_group_ = my_road_->light_group();
}

