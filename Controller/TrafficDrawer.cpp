#include "stdafx.h"

#include "../Emulator/Emulator.h"
#include "TrafficDrawer.h"
#include "../Core/Cross.h"
#include "../Core/LightGroup.h"
#include "../Core/Road.h"
#include "../Core/Line.h"
#include "../Core/Vehicle.h"
#include "../Core/SingleLight.h"
#include "../Core/Position.h"
#include "../Globals.h"
#include "ArrowDrawer.h"
#include "RectDrawer.h"



CPoint VEHICLE_POINT[4];

void draw_rect( CDC* pDC )
{
	pDC->Draw3dRect(MAIN_RECT_X,MAIN_RECT_Y,MAIN_RECT_WIDTH,MAIN_RECT_HEIGHT,0,0);
}


CPoint left_top(CPoint* points,int count) {
	int lx = points[0].x;
	int ly = points[0].y;
	for (int i=0; i<count; ++i)
	{
		if (ly > points[i].y)
		{
			//lx = points[i].x;
			ly = points[i].y;
		}
		if (lx > points[i].x)
		{
			lx = points[i].x;
		}
	}
	return CPoint(lx,ly);
}

void draw_stop_line( int x1, int y1, int center_to_road, int road_width, int n_lines, int ratio, CDC* pDC )
{
	center_to_road = STOP_LINE;
	int x5 = get_x5(x1,STOP_LINE,ratio);
	int y5 = get_y5(y1,STOP_LINE,ratio);
	int x6 = get_x6(get_x2(x1,road_width,ratio),STOP_LINE,ratio);
	int y6 = get_y6(get_y2(y1,road_width,ratio),STOP_LINE,ratio);

	float fac = (float)n_lines*(float)LINE_WIDTH / road_width;
	int x7 = x5+(x6-x5)*fac;
	int y7 = y5+(y6-y5)*fac;

	CPen line_edge_pen(PS_SOLID,2,RGB(0,0,0));
	auto old_pen = pDC->SelectObject(line_edge_pen);
	pDC->MoveTo(x5,y5);
	pDC->LineTo(x7,y7);
	pDC->MoveTo(x7,y7 );
	pDC->SelectObject(old_pen);

	CPen center_pen(PS_SOLID,2,RGB(255,255,0));
	pDC->SelectObject(center_pen);
	pDC->LineTo(get_x4(x7,MAIN_RECT_WIDTH,ratio),get_y4(y7,MAIN_RECT_WIDTH,ratio));
	pDC->SelectObject(old_pen);


	int line_start_x = x_move_to(x5,LINE_WIDTH,ratio);
	int line_start_y = y_move_to(y5,LINE_WIDTH,ratio);

	CPen line_pen(PS_DASH,1,LINE_EDGE_COLOR.rgb());
	old_pen = pDC->SelectObject(line_pen);
	int total_lines=road_width/LINE_WIDTH;
	while (--total_lines>0) {

		pDC->MoveTo(line_start_x,line_start_y);
		if (total_lines == n_lines) {
			line_start_x = x_move_to(line_start_x,LINE_WIDTH,ratio);
			line_start_y = y_move_to(line_start_y,LINE_WIDTH,ratio);
			continue;
		}
		pDC->LineTo(get_x4(line_start_x,MAIN_RECT_WIDTH,ratio),get_y4(line_start_y,MAIN_RECT_WIDTH,ratio));
		line_start_x = x_move_to(line_start_x,LINE_WIDTH,ratio);
		line_start_y = y_move_to(line_start_y,LINE_WIDTH,ratio);
	}
	pDC->SelectObject(old_pen);


}
//x1:start_of_stop_line_x
//center_to_road
void draw_road(int road_index,int x1, int y1, int road_width,int center_to_road, int n_lines, int ratio, CDC* pDC) {
	/*			(x4,y4)
	*			 /	
	*			/	(600,y3)
	*		(x1,y1)	  /
	*			\	 /b
	*		   a \  /
	*			(x2,y2)
	*
	*/
	int x2 = x1 + road_width*sin(ratio/RAD);
	int y2 = y1-road_width*cos(ratio/RAD);
	int y3 = get_y3(y2,MAIN_RECT_WIDTH,ratio);
	int x4 = x1+(MAIN_RECT_WIDTH-x1)*sin((ratio-90)/RAD);
	int x5 = get_x5(x1,STOP_LINE,ratio);
	int y5 = get_y5(y1,STOP_LINE,ratio);

	CPen road_pen(PS_SOLID,2,RGB(0,0,0));
	auto old_pen = pDC->SelectObject(road_pen);
	pDC->MoveTo(x1,y1);
	pDC->MoveTo(x2,y2);
	pDC->LineTo(get_x3(x2,MAIN_RECT_WIDTH,ratio),y3);
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x4, get_y4(y1,MAIN_RECT_WIDTH,ratio));
	pDC->SelectObject(old_pen);
	draw_back_lines(GLOBAL_EMU->cross()->road_at(road_index),x5,y5,ratio,pDC);
	draw_stop_line(x1,y1,center_to_road,road_width,n_lines,ratio,pDC);
	draw_lights(GLOBAL_EMU->cross()->road_at(road_index),x5,y5,ratio,pDC);

	draw_vehicles(GLOBAL_EMU->cross()->road_at(road_index),x5,y5,ratio,pDC);
}

void draw_back_lines(Road* r,int x5,int y5,int ratio,CDC* pDC) {
	int line_start_x = get_x2(x5,1,ratio);
	int line_start_y = get_y2(y5,1,ratio);
	CPoint line_points[4];

	auto old_brush = pDC->SelectObject(LINE_BACK_BRUSH);
	for (int line_index=0; line_index<r->num_of_lines(); ++line_index) {
		line_points[0].x = line_start_x;
		line_points[0].y = line_start_y;
		line_points[1].x = get_x2(line_start_x,LINE_WIDTH-2,ratio);
		line_points[1].y = get_y2(line_start_y,LINE_WIDTH-2,ratio);
		line_points[2].x = get_x3(line_points[1].x,MAIN_RECT_WIDTH,ratio);
		line_points[2].y = get_y3(line_points[1].y,MAIN_RECT_WIDTH,ratio);
		line_points[3].x = get_x4(line_start_x,MAIN_RECT_WIDTH,ratio);
		line_points[3].y = get_y4(line_start_y,MAIN_RECT_WIDTH,ratio);
		pDC->Polygon(line_points,4);
		line_start_x = get_x2(line_start_x,LINE_WIDTH,ratio);
		line_start_y = get_y2(line_start_y,LINE_WIDTH,ratio);
	}
	pDC->SelectObject(old_brush);
}

DWORD __stdcall draw_roads4( CDC* pDC )
{
	Emulator* emu = GLOBAL_EMU;
	if (emu->num_of_roads() == 4) {
		int corner = 360 / emu->num_of_roads();
		int road_id = 0;
		int line_index = 0;
		int v_num_of_lines = emu->num_of_lines(0)+emu->num_of_lines(2);
		int h_num_of_lines = emu->num_of_lines(1)+emu->num_of_lines(3);
		int center_to_up_road = h_num_of_lines / 2 * LINE_WIDTH;
		int center_to_left_road = v_num_of_lines / 2 * LINE_WIDTH;
		int x1 = CENTER_X - center_to_left_road;
		int y1 = CENTER_Y - center_to_up_road;

		draw_road(0,x1,y1,v_num_of_lines*LINE_WIDTH,center_to_up_road,emu->num_of_lines(0),90,pDC);
		draw_road(1,CENTER_X+center_to_left_road,CENTER_Y-center_to_up_road,h_num_of_lines*LINE_WIDTH,center_to_left_road,emu->num_of_lines(1),180,pDC);
		draw_road(2,CENTER_X+center_to_left_road,CENTER_Y+center_to_up_road,v_num_of_lines*LINE_WIDTH,center_to_up_road,emu->num_of_lines(2),270,pDC);
		draw_road(3,CENTER_X-center_to_left_road,CENTER_Y+center_to_up_road,h_num_of_lines*LINE_WIDTH,center_to_left_road,emu->num_of_lines(3),0,pDC);

	}
	return 0;
}


void draw_vehicles( Road* r, int x5, int y5, int ratio, CDC* pDC )
{

	int veh_line_start_x = get_x2(x5,(LINE_WIDTH-VEH_WIDTH)/2,ratio);
	int veh_line_start_y = get_y2(y5,(LINE_WIDTH-VEH_WIDTH)/2,ratio);
	int line_start_x = x5;
	int line_start_y = y5;
	for (int line_index=0; line_index<r->num_of_lines(); ++line_index) {
		draw_arrow(r->line_at(line_index),line_start_x,line_start_y,ratio,pDC);
		for (int veh_index=0; veh_index<r->line_at(line_index)->num_of_vehicles(); ++veh_index) {
			Vehicle& v=r->line_at(line_index)->vehicle_at(veh_index);
			draw_vehicle(v,
				get_x4(veh_line_start_x,v.m_to_cross()*VIRTUAL_RATIO,ratio),
				get_y4(veh_line_start_y,v.m_to_cross()*VIRTUAL_RATIO,ratio),
				ratio,
				pDC
				);
		}
		line_start_x = get_x2(line_start_x,LINE_WIDTH,ratio);
		line_start_y = get_y2(line_start_y,LINE_WIDTH,ratio);
		veh_line_start_x = get_x2(veh_line_start_x,LINE_WIDTH,ratio);
		veh_line_start_y = get_y2(veh_line_start_y,LINE_WIDTH,ratio);
	}
}

void draw_vehicle(Vehicle& v, int u_r_x, int u_r_y, int ratio, CDC* pDC) {
	int length = v.length();
	
	//CPoint VEHICLE_POINT[4];
	VEHICLE_POINT[0].x = u_r_x;
	VEHICLE_POINT[0].y = u_r_y;
	VEHICLE_POINT[1].x = get_x2(u_r_x,VEH_WIDTH,ratio);
	VEHICLE_POINT[1].y = get_y2(u_r_y,VEH_WIDTH,ratio);
	VEHICLE_POINT[2].x = get_x3(VEHICLE_POINT[1].x,length*VIRTUAL_RATIO,ratio);
	VEHICLE_POINT[2].y = get_y3(VEHICLE_POINT[1].y,length*VIRTUAL_RATIO,ratio);
	VEHICLE_POINT[3].x = get_x4(u_r_x,length*VIRTUAL_RATIO,ratio);
	VEHICLE_POINT[3].y = get_y4(u_r_y,length*VIRTUAL_RATIO,ratio);

	CBrush* veh_brush = NULL;
	if (v.type() == CAR)
	{
		veh_brush = &CAR_BRUSH;
	}
	else if (v.type() == BUS) {
		veh_brush = &BUS_BRUSH;
	}
	auto old_brush = pDC->SelectObject(*veh_brush);
	pDC->Polygon(VEHICLE_POINT,4);
	pDC->SelectObject(old_brush);
}

void draw_lights( Road* r,int x5, int y5 , int road_ratio, CDC* pDC )
{
	int ratio = road_ratio-90;
	
	int u_l_x = get_x4(x5,LIGHT_RADIUM*2,ratio);
	int u_l_y = get_y4(y5,LIGHT_RADIUM*2,ratio);
	int l_l_x = get_x2(x5,LIGHT_RADIUM*2,ratio);
	int l_l_y = get_y2(y5,LIGHT_RADIUM*2,ratio);
	LightContainer* lc = r->light_group()->lights();
	auto old_pen = pDC->SelectObject(DISABLED_BRUSH);
	for (auto light_iter=lc->begin(); light_iter != lc->end(); ++light_iter) {
		pDC->SelectObject(DISABLED_BRUSH);
		if (light_iter->light_on()) {
			switch (light_iter->color())
			{
			case GREEN:
				pDC->SelectObject(GREEN_BRUSH);
				break;
			case YELLOW:
				pDC->SelectObject(YELLOW_BRUSH);
				break;
			case RED:
				pDC->SelectObject(RED_BRUSH);
				break;
			default:
				break;
			}
		}
		pDC->Ellipse(u_l_x,u_l_y,l_l_x,l_l_y);
		u_l_x = get_x4(u_l_x,LIGHT_RADIUM*2,ratio);
		u_l_y = get_y4(u_l_y,LIGHT_RADIUM*2,ratio);
		l_l_x = get_x4(l_l_x,LIGHT_RADIUM*2,ratio);
		l_l_y = get_y4(l_l_y,LIGHT_RADIUM*2,ratio);
	}
	CPoint textpoint[2];
	textpoint[0].x = u_l_x;
	textpoint[0].y = u_l_y;
	textpoint[1].x = l_l_x;
	textpoint[1].y = l_l_y;
	int text_x = get_x4(get_x2(left_top(textpoint,2).x,5,ratio),5,ratio);
	int text_y = get_y4(get_y2(left_top(textpoint,2).y,5,ratio),5,ratio);
	CString dur;
	dur.Format(_T("%d"),r->light_group()->duration());
	pDC->TextOutW(text_x,text_y,dur);
	pDC->SelectObject(old_pen);
}


void draw_arrow(Line* l,int x5, int y5, int ratio,CDC* pDC) {
	CBrush arrow_brush(ARROW_COLOR.rgb());
	CPen arrow_pen(PS_SOLID,1,ARROW_COLOR.rgb());
	auto ole_pen = pDC->SelectObject(arrow_pen);
	auto old_brush = pDC->SelectObject(arrow_brush);
	CPoint arrow[MAX_ARROWS];
	int point_count=0;
	switch (l->direction())
	{
	case STRAIGHT:
		point_count=straight_arrow(arrow,x5,y5,ratio);
		break;
	case LEFT:
		point_count=left_arrow(arrow,x5,y5,ratio);
		break;
	case RIGHT:
		point_count=right_arrow(arrow,x5,y5,ratio);
		break;
	case UTRUN:
		point_count=uturn_arrow(arrow,x5,y5,ratio);
		break;
	case STRAIGHT_LEFT:
		point_count=straight_left_arrow(arrow,x5,y5,ratio);
		break;
	case STRAIGHT_RIGHT:
		//point_count=straight_right_arrow(arrow,x5,y5,ratio);
		break;
	default:
		return;
		break;
	}
	pDC->Polygon(arrow,point_count);
	pDC->SelectObject(old_brush);
	pDC->SelectObject(arrow_pen);

}