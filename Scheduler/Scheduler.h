#pragma once
#include "../stdafx.h"
#include "VehicleTraits.h"
#include "../Core/Road.h"



class LightGroup;
class Cross;
class Line;



class RESULT
{
public:
	RESULT(Road* r,Direction dir, float road_sum=0, int green_time=0) :
		road_(r), dir_(dir), 
		road_sum_(road_sum), 
		green_time_(green_time) 
	{}

	RESULT() : road_(NULL),road_sum_(0),green_time_(0) 
	{}


	bool operator != (const RESULT& rhs) const {
		if (road_!=NULL)
		{
			return road_sum_ != rhs.road_sum_ ||
				green_time_ != rhs.green_time_ ||
				*road_ != *rhs.road_ ||
				dir_ != rhs.dir_;
		}
		else {
			return road_sum_ != rhs.road_sum_ ||
				green_time_ != rhs.green_time_ ||
				dir_ != rhs.dir_;
		}
	}

	bool operator==(const RESULT& rhs) const {
		return !(*this != rhs);
	}

	Road* road_;
	Direction dir_;
	float road_sum_;
	int green_time_;
	
};

extern int DEF_MIN_GREEN;
extern int DEF_MAX_RED;

class Scheduler {
public:
	Scheduler();
	Scheduler(int min_green, int max_red ) ;
	void set_next_light_group(Road& r,LightGroup& lg);

	//计算整个路口的结果，r为起始路口
	virtual LightGroup calculate(Road& r)=0;

	//第一次运行时需要为所有道路的红绿灯进行初始化
	virtual void first_time_calculate() {};

	//计算一辆车的统计值
	virtual float cal_vehicle(Vehicle& v);

	//计算一条车道的统计值
	virtual float cal_line(Line& l);

	//计算一个方向的统计值
	virtual float cal_direction(Road& r,Direction& dir);

	//计算一条道路的统计值
	virtual float cal_road(Road& r);

	//在结果中查找路r的路灯时间
	virtual int find_green_time(Road& r)=0;

	//初始化整个算法
	virtual void initial()=0;

	// getter,setter
	void set_cross(Cross* cross) { cross_ = cross; }
	int min_green_time() const { return min_green_time_; }
	void set_min_green_time(const int min_green_time) { min_green_time_ = min_green_time; }
	int max_red_time() const { return max_red_time_; }
	void set_max_red_time(int max_red_time) { max_red_time_ = max_red_time; }
	CString name() const { return name_; }
	void set_name(CString& name) { name_ = name; }
	
protected:
	(Cross*) &cross_;			//当前所要计算的路口
	CString name_;				//算法名称
	VehicleTraits veh_traits_;	//车辆特性
	int min_green_time_;		//最短绿灯时间
	int max_red_time_;			//最长红灯时间
	bool initialized;			//算法是否已初始化
};

/************************************************************************/
/* 有请求来的时候就计算出各条路的权重总和，
 * 然后再根据算法本身的性质分配绿灯和红灯时间
 * 

 统计各个方向的统计值
信号灯能控制的方向(理论研究用）
车道本身的方向（实际情况用）
将统计值按大小排序

按大小顺序、方向不冲突的原则分组

统计每一组的统计值

据此算出各方向绿灯时间

*/
/************************************************************************/