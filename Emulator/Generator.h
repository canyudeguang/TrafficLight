#pragma once

class Line;
class Road;
class Cross;
class LightGroup;
class Driver;
class Vehicle;


//void GenerateLine(Line& l);
Road* GenerateRoad(Road* r,Cross* c,int index);
Cross* GenerateCross(Cross* c);
Driver* GenerateDriver( Driver* d,Road* r, int line_index, float init_distance=10.0f);
//LightGroup* GenerateLightGroup(LightGroup* lg);
Vehicle* GenerateVehicle(Vehicle* v, int road_id, int line_id, float init_distance = 10.0f );
DriverContainer* GenerateDrivers(DriverContainer* dc,Road* r,int line_index);

Direction GenerateDirection();
Line* GenerateLine( Line* l,Road* r, Direction dir );