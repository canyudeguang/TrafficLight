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

	//��������·�ڵĽ����rΪ��ʼ·��
	virtual LightGroup calculate(Road& r)=0;

	//��һ������ʱ��ҪΪ���е�·�ĺ��̵ƽ��г�ʼ��
	virtual void first_time_calculate() {};

	//����һ������ͳ��ֵ
	virtual float cal_vehicle(Vehicle& v);

	//����һ��������ͳ��ֵ
	virtual float cal_line(Line& l);

	//����һ�������ͳ��ֵ
	virtual float cal_direction(Road& r,Direction& dir);

	//����һ����·��ͳ��ֵ
	virtual float cal_road(Road& r);

	//�ڽ���в���·r��·��ʱ��
	virtual int find_green_time(Road& r)=0;

	//��ʼ�������㷨
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
	(Cross*) &cross_;			//��ǰ��Ҫ�����·��
	CString name_;				//�㷨����
	VehicleTraits veh_traits_;	//��������
	int min_green_time_;		//����̵�ʱ��
	int max_red_time_;			//����ʱ��
	bool initialized;			//�㷨�Ƿ��ѳ�ʼ��
};

/************************************************************************/
/* ����������ʱ��ͼ��������·��Ȩ���ܺͣ�
 * Ȼ���ٸ����㷨��������ʷ����̵ƺͺ��ʱ��
 * 

 ͳ�Ƹ��������ͳ��ֵ
�źŵ��ܿ��Ƶķ���(�����о��ã�
��������ķ���ʵ������ã�
��ͳ��ֵ����С����

����С˳�򡢷��򲻳�ͻ��ԭ�����

ͳ��ÿһ���ͳ��ֵ

�ݴ�����������̵�ʱ��

*/
/************************************************************************/