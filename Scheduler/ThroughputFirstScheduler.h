#pragma once
#include "Scheduler.h"
#include "../Globals.h"
class Road;



typedef vector<RESULT> RESULT_CONTAINER;
//typedef pair<float,int> RESULT;
class ThroughputFirstScheduler :
	public Scheduler
{
public:
	//ThroughputFirstScheduler(void);
	ThroughputFirstScheduler(int min_green  = DEF_MIN_GREEN, int max_red = DEF_MAX_RED);
	virtual ~ThroughputFirstScheduler(void);
	void initial();
	LightGroup calculate(Road& r);
	LightGroup now_is_red(Road& r);
	void cal_results();
	LightGroup now_is_yellow(Road& r);
	LightGroup now_is_green(Road& r);
	float cal_abc(Road& r);
	int find_green_time(Road& r);
	int cal_red_time(Road& r);
	void first_time_calculate();
	int period() const { return period_; }
	void set_period(const int& period) { period_ = period; }
	void sort_results();
	//void group_results();
private:
	//4条路各自的结果！！！！！！！！！！！！！1
	//float result_,int green_time
	 RESULT_CONTAINER* cal_result_;

	//当前路的占比
	//float my_weight_;

	//结果的总和
	float result_sum_;

	//总时间
	float total_time_;

	//开始的那条路
	Road* road_start_;

	//此次红绿灯持续的周期
	//为0时表示每一次灯的切换都会触发计算
	// >0时表示多少个红绿黄的转换
	int period_;
	int cur_period_;
};

