#pragma once

class Line;
class Road;
class Cross;
class LightGroup;
class Driver;
class Vehicle;



Road* GenerateRoad(Road* r,Cross* c,int index);
Cross* GenerateCross(Cross* c);
Driver* GenerateDriver( Driver* d,Road* r, int line_index, float init_distance=10.0f);

Vehicle* GenerateVehicle(Vehicle* v, int road_id, int line_id, float init_distance = 10.0f );
DriverContainer* GenerateDrivers(DriverContainer* dc,Road* r,int line_index);

Direction GenerateDirection();
Line* GenerateLine( Line* l,Road* r, Direction dir );