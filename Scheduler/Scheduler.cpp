#include "stdafx.h"
#include "Scheduler.h"
#include "../core/Road.h"
#include "../Core/LightGroup.h"
#include "../Core/Line.h"
#include "../Core/SingleLight.h"
#include "../Core/Vehicle.h"
#include "../Emulator/Driver.h"
#include "../Globals.h"
#include "../Emulator/Emulator.h"


Scheduler::Scheduler() :cross_(GLOBAL_EMU->cross()),initialized(false)
{

}

Scheduler::Scheduler( int min_green, int max_red ):
	cross_(GLOBAL_EMU->cross()),
	min_green_time_(min_green),
	max_red_time_(max_red),
	initialized(false)
{

}


void Scheduler::set_next_light_group( Road& r,LightGroup& lg )
{
	r.set_light_group(&lg);
}



float Scheduler::cal_vehicle( Vehicle& v )
{
	return veh_traits_.veh_vector(v);
}

float Scheduler::cal_line( Line& l )
{
	auto driver_iter = l.drivers()->begin();
	float sum = 0;
	for_each(driver_iter,l.drivers()->end(),[&](Driver& d) {
		int vvv = cal_vehicle(*d.vehicle());
		sum += vvv;
	});
	return sum;
}

float Scheduler::cal_direction( Road& r,Direction& dir )
{
	float sum = 0;
	for_each(r.lines()->begin(),r.lines()->end(),[&](Line& l) {
		if (l.direction() == dir)
		{
			sum += cal_line(l);
		}
	});
	return sum;
}

float Scheduler::cal_road( Road& r )
{
	float sum=0;
	for_each(r.lines()->begin(),r.lines()->end(),[&](Line& l) {
		sum += cal_line(l);
	});
	return sum;
}



// 
// bool RESULT::operator!=( const RESULT& rhs )
// {
// 	
// }
// 
// bool RESULT::operator==( const RESULT& rhs )
// {
// 	
// }
