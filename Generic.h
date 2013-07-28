#pragma once
#include "stdafx.h"


class string;
class Driver;
class Vehicle;
class Road;
class Cross;
class Emulator;
class LightGroup;
class Scheduler;

using std::pair;
using std::string;
using std::vector;
using std::for_each;
using std::find;
using std::min_element;
using std::accumulate;
using std::unique_ptr;



typedef std::vector<Driver> DriverContainer;
typedef std::vector<Vehicle> VehicleContainer;
typedef std::vector<Road> RoadContainer;
typedef std::vector<LightGroup> LightGroupContainer;


enum Direction {
	
	STRAIGHT = 1, 
	LEFT = 2, 
	RIGHT = 4,
	UTRUN = 8,
	STRAIGHT_LEFT = 3,
	STRAIGHT_RIGHT = 5,
	STRAIGHT_UTRUN = 9,
	LEFT_UTRUN = 10,
	ALL = 0,
};

struct COLOR {
	int r;
	int g;
	int b;
	COLOR(int r,int g,int b):r(r),g(g),b(b){}
	unsigned int rgb() { return RGB(r,g,b);}
};






// enum VehicleType {
// 	CAR,
// 	BUS,
// 	BIKE
// };


class VehicleType {
public:
	bool operator == (const VehicleType& rhs) {
		return (memcmp(this,&rhs,sizeof(VehicleType)) == 0);
	}
	float max_accel_;
	float max_break_;
	float length_min_;
	float length_max_;
	float slow_speed_;
	float max_speed_;
};



enum LightColor {
	RED,
	YELLOW,
	GREEN,
	YELLOW_FLASH,
	WRONG=0
};
// class VehicleType {
// public:
// 	string typename_;
// 	float accelera_speed_;
// 	float break_speed_;
// }



// struct Direction
// 	/*
// 	 *	代表偏离顺时针方向的度数
// 	 */
// {
// private:
// 	int ratio_;
// public:
// 	Direction(int ratio=0):ratio_(ratio) {}
// 	int ratio() {
// 		return ratio_%360;
// 	}
// 	void set_ratio(const int& ratio) {
// 		ratio_ = ratio;
// 	}
// };

//有时间限制的公交车专用道????



template <class ITEM_TYPE, class CONTAINER_TYPE>
bool add_unique(ITEM_TYPE item, CONTAINER_TYPE* container) {
	if ((find_if(container->begin(),container->end(),
		[&](ITEM_TYPE& i) {
			return i==item;
		})) == container->end() ) {
			container->push_back(item);
			return true;
	}
	return false;
}

template <class ITEM_TYPE, class CONTAINER_TYPE>
bool search_for_delete(ITEM_TYPE item, CONTAINER_TYPE* container) {
	auto ct_iter = find_if(container->begin(),container->end(),
		[&](ITEM_TYPE& i) {
			return i==item;
	});
	if (ct_iter != container->end()) {
		container->erase(ct_iter);
		return true;
	}
	return false;
}

// cases:总共有多少种可能,然后是第一种可能性的百分比,第二种...直到第N种...
// 未指明的概率将被平分(不能平分的话最后一个概率会奇葩)
// 用-1表示结束
// possibily_sum:可能性的和是多少
// 返回值表示这次是第几种情况,返回0表示错误
// 还是用整数表达概率吧.省得闹心.
int SelectCase(int cases, int possibility_sum, int first_percent,...);


bool isAcceptable(Direction inside, Direction outside);
WCHAR* directory_path(WCHAR* exe_path, int size, WCHAR* dir_path);
bool FloatEqual( const float& a, const float& b );
bool almost_equal(const float& lhs, const float& rhs, float min_delta = 0.3);
int dir_level(const Direction& dir);
Scheduler* find_scheduler(CString& name);
//void GenerateUnit( TrafficUnit& t);
/*bool VehicleDistanceCompare (const Vehicle& lhs, const Vehicle& rhs);*/