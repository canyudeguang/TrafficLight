


#include "stdafx.h"

#include "../Generic.h"
#include "../Core/Line.h"
#include "../Core/Road.h"
#include "../Core/Vehicle.h"
#include "../Core/Cross.h"
#include "../Core/LightGroup.h"
#include "Generator.h"
#include "Driver.h"
#include "../Globals.h"

/* Driver::
	Direction direction_;
	Vehicle* p_vehicle_;
	Vehicle* pre_vehicle();
	LightGroup* lightgroup_;
*/
Driver* GenerateDriver( Driver* d,Road* r, int line_index, float init_distance/*=10.0f*/ )
{
	
	int num_of_lines = r->lines()->size();
	d->set_direction(r->lines()->at(line_index).direction());
	d->set_light_group(r->light_group());
	d->set_my_road(r);
	d->set_line_index(line_index);
	d->my_line()->reorder();
	int generate_count = 0;
	do
	{
		d->set_vehicle(*GenerateVehicle(d->vehicle(),r->road_id(),line_index,init_distance));
		d->my_line()->reorder();
		++generate_count;
		if (generate_count == 50)
		{
			break;
		}
	} while (d->overlapped());
	return d;
}

DriverContainer* GenerateDrivers( DriverContainer* dc,Road* r,int line_index)
{
	int num_of_vehicles = r->line_at(line_index)->num_of_vehicles();
	for (int vehicle_index = 0; vehicle_index < num_of_vehicles; ++vehicle_index) {

		dc->push_back(*GenerateDriver(&(Driver(Vehicle())),r,line_index));
	}
	return dc;
}

/* Vehicle::
	float length_
	VehicleType type_
	float speed_
	Position position_
*/
Vehicle* GenerateVehicle( Vehicle* v, int road_index, int line_index, float init_distance /*= 10.0f */ )
{
	static float dis=0;
	static int id = line_index;
	if (id != line_index)
	{
		dis = 0;
		id = line_index;
	}
	switch (SelectCase(2,10,8,-1))
	{
	case 1:
		v->set_type(CAR);
		v->set_length((rand()%20)/10.0+3.0);
		break;
	default:
		v->set_type(BUS);
		v->set_length((rand()%20)/10.0+12.0);
		break;
	}
	v->set_speed((rand()%10)/10.0f+1.0f);
	dis+=v->length()*2;
	v->set_position(Position(road_index,line_index,rand()%int(dis)+init_distance));
	
	return v;
}

// void GenerateLine( Line& l )
// {
// 	l.set_line_id(rand()%899+100);
// 	l.set_line_name("I'm a Line.");
// 	//l.set_from_cross(NULL);
// 	//l.set_to_cross(NULL);
// //	l.set_p_my_road(NULL);
// // 	l.set_vehicles(NULL);
// 	int num_of_vehicle = rand()%20;
// 	VehicleContainer* vl = new VehicleContainer();
// 	while(num_of_vehicle--) {
// 		vl->push(GenerateVehicle());
// 	}
// 	l.set_vehicles(vl);
// }

Direction GenerateDirection() {
	Direction dir = LEFT;
	//	1:4:LEFT
	//	2:2:UTRUN.......
	switch (SelectCase(5,12,4,-1))
	{
	case 1: break;
	case 2: 
		{
			dir = UTRUN;
			break;
		}
	case 3:
		{
			dir = STRAIGHT_LEFT;
			break;
		}
	case 4:
		{
			dir = STRAIGHT_UTRUN;
			break;
		}
	case 5:
		{
			dir = LEFT_UTRUN;
			break;
		}
		default:
		break;
	}
	return dir;
}


/*
 *	int index_;
	Direction direction_;
	VehicleContainer* vehicles_;
	Road* p_my_road_;
 */
Line* GenerateLine( Line* l,Road* r, Direction dir )
{
	l->set_index( r->lines()->size());
	l->set_direction(dir);

	l->set_my_road(r);
	return l;
}

/* Road::
	int road_id_;
	string road_name_;
	float length_;
	LineContainer* lines_;
*/
Road* GenerateRoad( Road* r,Cross* c,int index )
{
	static int gen_count=0;
	char temp[10];
	int lineid=0;
	_itoa_s(gen_count++,&temp[0],10,10);
	r->set_road_id(gen_count+1000);
	r->set_my_cross(c);
	r->set_road_name("GeneratedRoad" + string(temp));
	r->set_length(rand()%100+300);
	r->add_line(*GenerateLine(&Line(),r,STRAIGHT));
	r->add_line(*GenerateLine(&Line(),r,STRAIGHT));
	r->add_line(*GenerateLine(&Line(),r,STRAIGHT_LEFT));
	
	return r;
}

/* Cross::
	int cross_id_;
	string cross_name_;
	CrossContainer crosses_;
	LightGroup* light_groups_;
*/
Cross* GenerateCross( Cross* c )
{
	c->set_cross_id(rand()%899+1000);
	c->set_cross_name("GeneratedCross");
	int num_of_roads=DEF_ROADS;
	int nor = num_of_roads;
	while (nor>0) {
		c->add_road(*GenerateRoad(&Road(),c,num_of_roads-nor));
		if (nor == num_of_roads)
		{
			c->road_at(num_of_roads-nor)->set_light_group(&DEF_GREEN_LIGHT);
		}
		else {
			c->road_at(num_of_roads-nor)->set_light_group(&DEF_RED_LIGHT);
			c->road_at(num_of_roads-nor)->set_duration(
				(num_of_roads-nor)*(DEF_GREEN_LIGHT.duration()+DEF_YELLOW_LIGHT.duration()));
		}
		--nor;
	}
	return c;
}
