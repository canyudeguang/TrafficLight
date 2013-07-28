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
	//4��·���ԵĽ����������������������������1
	//float result_,int green_time
	 RESULT_CONTAINER* cal_result_;

	//��ǰ·��ռ��
	//float my_weight_;

	//������ܺ�
	float result_sum_;

	//��ʱ��
	float total_time_;

	//��ʼ������·
	Road* road_start_;

	//�˴κ��̵Ƴ���������
	//Ϊ0ʱ��ʾÿһ�εƵ��л����ᴥ������
	// >0ʱ��ʾ���ٸ����̻Ƶ�ת��
	int period_;
	int cur_period_;
};

