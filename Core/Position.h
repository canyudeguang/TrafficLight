#pragma once
#include "../Generic.h"


//todo ���ݾ���������λ��
class Position
{
public:
	Position(void){}
	~Position(void){}
	Position(int road_id,int line_index,float m_to_cross)
		:road_id_(road_id),line_index_(line_index),meters_to_cross_(m_to_cross) {}
#ifdef USE_ABSOLUTE_COOR
	//��������,��������
	float x_;
	float y_;
#else                    

	float meters_to_cross() const { return meters_to_cross_; }
	void set_meters_to_cross(const float& meters_to_cross) { meters_to_cross_ = meters_to_cross; }

	int road_id() const { return road_id_; }
	void set_road_id(const int& road_id) { road_id_ = road_id; }
	
	int line_index() const { return line_index_; }
	void set_line_index(const int& line_index) { line_index_ = line_index; }
	

private:
	//��·�ڵľ���
	float meters_to_cross_;
	
	//��ǰ���ڵ�·
	int road_id_;

	//��ǰ���ڵĵ�
	int line_index_;
	
#endif
};

