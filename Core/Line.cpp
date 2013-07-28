#include "stdafx.h"

#include "Line.h"
#include "Road.h"
#include "Cross.h"
#include "Vehicle.h"
#include "../Emulator/Driver.h"
#include "../Globals.h"
#include "../Emulator/Generator.h"



Line::Line( int line_index, Direction direction ) :
	index_(line_index),direction_(direction),
	drivers_per_second_((rand()%200+500)/3600.0f),
	processed_count_(0)
{
	//	vehicles_ = new VehicleContainer();
	drivers_ = new DriverContainer();
}

Line::Line():drivers_per_second_((rand()%200+500)/3600.0f),
	processed_count_(0)
{
	index_=0;
	drivers_ = new DriverContainer();
}

Line::Line(const Line& rhs) {
	index_ = rhs.index_;
	direction_ = rhs.direction_;
	my_road_ = rhs.my_road_;
	drivers_per_second_ = rhs.drivers_per_second_;
	processed_count_ = rhs.processed_count_;
	drivers_ = new DriverContainer(*rhs.drivers());
	copied();
}
Line::~Line(void)
{
	delete drivers_;
}

void Line::copied() {
	for_each(drivers_->begin(),drivers_->end(),[&](Driver& d ) {
		d.set_my_road(my_road_);
	});
	reorder();
}


int Line::num_of_vehicles()
{
	return drivers_->size();
}

void Line::reorder() {
	std::sort(drivers_->begin(),drivers_->end(),[&](Driver& ld,Driver& rd ) {
		return rd.my_vehicle()->m_to_cross() > ld.my_vehicle()->m_to_cross();
	});
	
}

bool Line::operator<( const Line rhs )
{
	return index_ < rhs.index_;
}

Vehicle& Line::vehicle_at( int index )
{
	return (*drivers_->at(index).vehicle());
}

void Line::set_drivers( DriverContainer*& drivers )
{
	if ((drivers != NULL) && drivers_ != drivers) {
		delete drivers_;
		drivers_ = new DriverContainer(*drivers); 
	}
	copied();
}

void Line::add_driver( Driver& d )
{

	drivers_->push_back(d);
	d.set_my_road(my_road_);
}

void Line::time_for_add_driver() {
	add_driver(*GenerateDriver(&Driver(Vehicle()),my_road_,index_,REAL_METERS));
	reorder();
	processed_count_=0;
}

void Line::processed() {
	++processed_count_;
}
Vehicle* Line::next_vehicle(Driver& d) {
	reorder();
	if (drivers_->empty())
	{
		return NULL;
	}
	if (d.my_road()->road_id() != my_road()->road_id() ||
		d.line_index() != index_ )
		return d.my_road()->line_at(d.line_index())->next_vehicle(d);
	auto driver_iter = find(drivers_->begin(),drivers_->end(),d);
	if (driver_iter != drivers_->end()) {
		//�ҵ���d
		if (*driver_iter != *drivers_->rbegin())
		{
			//d�������һ���������Է���d�ĺ�һ��
			return ((driver_iter+1)->my_vehicle());
		}
		else
		{
			//d�����һ����������NULL
			return NULL;
		}
	}
	else {
		//û���ҵ�d���Ǿ��Ҹպñ���Զ�ĳ�
		auto first_further = find_if(drivers_->begin(),drivers_->end(),[&](Driver& lambda_d) {
			return d.my_vehicle()->m_to_cross() < lambda_d.my_vehicle()->m_to_cross();
		});
		if (first_further != drivers_->end())
		{
			return (first_further)->my_vehicle();
		}
		else
		{//���еĳ�����d������ô����NULL��
			return NULL;
		}
	}// the driver is not found in this line;
	return NULL;


}
Vehicle* Line::pre_vehicle( Driver& d )
{
	reorder();
	//û�г���ʱ�򷵻�NULL��û��ǰ��
	if (drivers_->empty())
	{
		return NULL;
	}

	//����d������
	auto driver_iter = find(drivers_->begin(),drivers_->end(),d);
	if (driver_iter != drivers_->end()) {
		//�ҵ���d
		if (driver_iter != drivers_->begin())
		{
			//d���ǵ�һ���������Է���d��ǰһ��
			return ((driver_iter-1)->my_vehicle());
		}
		else
		{
			//d�ǵ�һ����������NULL
			return NULL;
		}
	}
	else {
		//û���ҵ�d���Ǿ��Ҹպñ���Զ�ĳ���ǰһ��
		auto first_further = find_if(drivers_->begin(),drivers_->end(),[&](Driver& lambda_d) {
			return d.my_vehicle()->m_to_cross() < lambda_d.my_vehicle()->m_to_cross();
		});
		if (first_further != drivers_->end())
		{
			//�ҵ���һ���պñ�dԶ�ĳ�
			if (first_further != drivers_->begin())
			{//�����ⲿ�����ǿ�ͷ���򷵻��ⲿ����ǰһ����
				return (first_further-1)->my_vehicle();
			}
			else
			{//�ҵ����ڿ�ͷ�ĳ�������NULL
				return NULL;
			}
		}
		else
		{//���еĳ�����d������ô������Զ����һ������
			return drivers_->rbegin()->my_vehicle();
		}
	}// the driver is not found in this line;
	return NULL;

}

void Line::del_driver( Driver& d )
{
	auto driver_iter = std::find(drivers_->begin(),drivers_->end(),d);
	if (driver_iter != drivers_->end()) {
		drivers_->erase(driver_iter);
	}
	reorder();
}

bool Line::operator!=( const Line& rhs )
{
	return
		index_ != rhs.index_ ||
		direction_ != rhs.direction_ ||
		*my_road_ != *rhs.my_road_ ||
		equal(drivers_->begin(),drivers_->end(),rhs.drivers_->begin());
	//*drivers_ != *rhs.drivers_;
}

bool Line::operator==( const Line& rhs )
{
	return !(*this != rhs);
}

void Line::set_my_road( Road* my_road )
{
	my_road_ = my_road;
	for_each(drivers_->begin(),drivers_->end(),[&](Driver& d) {
		d.set_my_road(my_road_);
	});
}

void Line::set_num_of_vehicles( int n_vehicles )
{
	if (n_vehicles<0)
	{
		n_vehicles = 0;
	}
	int count = n_vehicles-num_of_vehicles();
	if (count > 0)
	{
		while (count-- > 0)
		{
			add_driver(
				*GenerateDriver(
				&Driver(Vehicle()),
				my_road_,index()));
		}
		reorder();
	} 
	else
	{
		while (count++ < 0)
		{
			drivers_->pop_back();
		}
		reorder();
	}
	
}

//float VehicleColumn::distance_to_front( const Vehicle& vehicle )
//{
//	//�ⷽ���о���һ������
//	auto my_iter = std::find(vehicle_line_.begin(),vehicle_line_.end(),vehicle);
//	if (my_iter == vehicle_line_.begin()) {
//		return 0;
//	}
//	if (my_iter == vehicle_line_.end()) {
//		//��ô˵��������??
//		return std::numeric_limits<float>::max();
//	}
//	return distance_between(vehicle,*(--my_iter));
//}


bool VehicleDistanceCompare::operator()(  Vehicle& lhs,  Vehicle& rhs ) 
{
	return lhs.m_to_cross() > rhs.m_to_cross();
}

bool VehicleDistanceCompare::operator()(  Driver& lhs,  Driver& rhs )  
{
	return lhs.my_vehicle()->m_to_cross() > rhs.my_vehicle()->m_to_cross();
}

