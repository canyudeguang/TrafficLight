#pragma  once

#include "../stdafx.h"

#include "../Generic.h"
#include "../Core/core.h"

class Driver;
class Cross;
class Scheduler;
class Line;
class Road;

extern bool thread_exit;

enum EMU_STATE
{
	STOPPED,
	STARTED,
	SUSPENDED
};
class Emulator
{
public:
	Emulator();
	~Emulator();
	void set_num_of_roads(int n_roads);
	void set_num_of_lines(int n_lines,int road_index) ;
	void set_num_of_vehicles(int n_vehicles,int line_index, int road_index);
	void set_num_of_vehicles(int n_vehicles, Line* l, Road* r);
	void set_scheduler(Scheduler* s);
	int num_of_roads();

	int num_of_lines(int road_id);

	int num_of_vehicles(int line_index, int road_id);
	
	Cross*& cross() { return cross_; }
	void set_cross(Cross*& cross) { cross_ = cross; }
	void restart();
// 	DriverContainer* drivers() const { return drivers_; }
// 	void set_drivers(DriverContainer*& drivers) { drivers_ = drivers; }
	void initial();
	bool start();
	void pause();
	void resume();
	void stop();
	//void thread_drivers_start();
protected:
private:
	Cross* cross_;
	//DriverContainer* drivers_;
	bool initialized_;
	HANDLE thread_id_drivers_;
	
};
DWORD __stdcall thread_drivers_start(void* cross);