#include "stdafx.h"


#include "Emulator.h"
#include "Generator.h"
#include "../Generic.h"
#include "../Core/Cross.h"
#include "../Core/Line.h"
#include "../Core/Road.h"
#include "../Core/Vehicle.h"
#include "../Core/LightGroup.h"
#include "Driver.h"
#include "../Globals.h"
#include "../Scheduler/Scheduler.h"

extern bool thread_exit = false;
Emulator::Emulator():initialized_(false),thread_id_drivers_(0)
{
	cross_ = NULL;
}

Emulator::~Emulator()
{
	delete cross_;
}

void Emulator::initial() {
	if (cross_ != NULL && !initialized_) {
		delete cross_;
	}
	cross_ = new Cross();
	GenerateCross(cross_);
	set_num_of_roads(DEF_ROADS);
	for (int road_index=0; road_index<DEF_ROADS; ++road_index) {
		set_num_of_lines(DEF_LINES,road_index);
		for (int line_index=0;line_index<DEF_LINES;++line_index) {
			set_num_of_vehicles(rand()%30,line_index,road_index);
		}
	}
	set_scheduler(SELECTED_SCHEDULER);
	SELECTED_SCHEDULER->initial();
	SELECTED_SCHEDULER->first_time_calculate();
	initialized_ = true;
}

bool Emulator::start()
{
	if (!initialized_) initial();
	thread_exit = false;
	if (thread_id_drivers_>0) {
		resume();
		return true;
	}
	thread_id_drivers_ = CreateThread(NULL,0,thread_drivers_start,(LPVOID)cross_,0,NULL);
	if (thread_id_drivers_>0) {
		return true;
	}
	else
	{
		return false;
	}

}

void Emulator::pause() {
	if (thread_id_drivers_>0) {
		SuspendThread(thread_id_drivers_);
	}
}

void Emulator::resume() {
	if (thread_id_drivers_>0) {
		ResumeThread(thread_id_drivers_);
	}
}

void Emulator::stop() {
	thread_exit = true;
	initialized_ = false;
	thread_id_drivers_ = 0;
}


void Emulator::restart()
{
	delete cross_;
	cross_ = new Cross();
	initial();
}


DWORD __stdcall thread_drivers_start( void* cross )
{
	Cross* c = static_cast<Cross*>( cross);
	while (!thread_exit)
	{
		auto road_iter = c->roads()->begin();
		for (; road_iter!=c->roads()->end(); ++road_iter)
		{
			road_iter->duration_decrease();
			auto line_iter = road_iter->lines()->begin();
			for (; line_iter!=road_iter->lines()->end(); ++line_iter) {
				if (almost_equal(
					line_iter->processed_count() * TIME_DELIM_SEC,
					1.0f / (line_iter->drivers_per_second()),
					TIME_DELIM_SEC))
				{
					line_iter->time_for_add_driver();
				}
				else {
					line_iter->processed();
				}
				auto drivers = line_iter->drivers();
				for (int driver_index=0; driver_index<line_iter->drivers()->size(); ++driver_index) {
					if (!(drivers->at(driver_index).i_am_dieing())) {
						drivers->at(driver_index).do_it();
					}
					else {
						line_iter->del_driver(drivers->at(driver_index));
						--driver_index;
					}

				}
			}
		}
		Sleep(TIME_DELIM_DRIVER_DO*1000);



	}
	return 0;
}

void Emulator::set_num_of_roads(int n_roads) {
	int count = n_roads - cross_->num_of_roads();
	if (count > 0) {
		while (count-- > 0)
		{
			cross_->add_road(*GenerateRoad(&Road(),cross_,cross_->num_of_roads()));
		}
	}
	else if (count < 0) {
		while (count-- > 0)
		{
			cross_->roads()->pop_back();
		}
	}
}

void Emulator::set_num_of_lines(int n_lines,int road_index) 
{

	Road* r = cross_->road_at(road_index);
	int count = n_lines - r->num_of_lines();
	if (count > 0) {
		while (count-- > 0)
		{
			cross_->road_at(road_index)->add_line(*GenerateLine(&Line(),r,GenerateDirection()));
		}
	}
	else if (count<0) {
		while (count-- > 0)
		{
			r->lines()->pop_back();
		}
	}
}

void Emulator::set_num_of_vehicles(int n_vehicles,int line_index, int road_index) {
	cross_->road_at(road_index)->line_at(line_index)->set_num_of_vehicles(n_vehicles);
}

void Emulator::set_num_of_vehicles(int n_vehicles, Line* l, Road* r) {
	l->set_num_of_vehicles(n_vehicles);
}

int Emulator::num_of_roads()
{
	return cross_->num_of_roads();
}

int Emulator::num_of_lines( int road_index )
{
	return cross_->road_at(road_index)->num_of_lines();
}

int Emulator::num_of_vehicles( int line_index, int road_index )
{
	return cross_->road_at(road_index)->line_at(line_index)->num_of_vehicles();
}

void Emulator::set_scheduler( Scheduler* s )
{
	for_each(cross_->roads()->begin(),cross_->roads()->end(), [&](Road& r) {
		r.set_scheduler(s);
	});

}



