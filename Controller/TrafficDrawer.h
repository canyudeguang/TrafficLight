#pragma once

#include "../stdafx.h"

#include "../Generic.h"

class Emulator;
class Line;


/*
*	DrawOutRect()
*	DrawRoads()
*	DrawVehicles()
*	DrawLights()
*/

void draw_rect(CDC* pDC);
DWORD __stdcall draw_roads4(CDC* pDC);
void draw_lights(Road* r,int x5, int y5 , int road_ratio, CDC* pDC);
void draw_vehicle(Vehicle& v, int u_r_x, int u_r_y, int ratio, CDC* pDC);
void draw_vehicles(Road* r, int x5, int y5, int ratio, CDC* pDC );
void draw_back_lines(Road* r,int x5,int y5,int ratio,CDC* pDC);
void draw_arrow(Line* l,int x5, int y5, int ratio,CDC* pDC);
CPoint left_top(CPoint* points,int count);