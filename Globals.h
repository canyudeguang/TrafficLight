#pragma once

#include "stdafx.h"
#include "Generic.h"

class Line;
class Road;
class Emulator;
class Scheduler;


typedef vector<Scheduler*> SchedulerPointerContainer;
//统一单位为m/s
//精度为0.1m
extern float LEGNTH_PRECISE;

//时间间隔为0.1s
extern float TIME_DELIM_SEC;
extern float TIME_DELIM_DRIVER_DO;

extern Emulator* GLOBAL_EMU;
extern int DEF_ROADS;
extern int DEF_LINES;
extern int DEF_VEHICLES;
extern int DEF_YELLOW_TIME;


extern float SAFE_DISTANCE_MULTI;
#define MAX_ARROWS 20


extern BOOL DATA_CHANGED;
extern float REAL_METERS;
extern float MAX_REAL_METERS;
extern float REAL_LINE_WIDTH;
extern float REAL_STOP_LINE;
//1.6-2.1
extern float REAL_VEH_WIDTH;
extern float REAL_ARROW_WIDTH;
extern float RAD;

//600 / 150
extern float VIRTUAL_RATIO;

extern int MAIN_RECT_X;
extern int MAIN_RECT_Y;
extern int MAIN_RECT_WIDTH;
extern int MAIN_RECT_HEIGHT;
extern int LINE_WIDTH;
extern int VEH_WIDTH;
//extern int LIGHT_WIDTH;
extern int CENTER_X;
extern int CENTER_Y;
extern int STOP_LINE;
extern int LIGHT_RADIUM;
//extern int ARROW_WIDTH;
extern int ARROW_DISTANCE;
extern float ARROW_VIRTUAL_RATIO;


extern Road* SELECTED_ROAD;
extern Line* SELECTED_LINE;


extern COLOR BACKGROUND_COLOR;
extern COLOR ROAD_EDGE_COLOR;
extern COLOR ROAD_COLOR;
extern COLOR LINE_BACK_COLOR;
extern COLOR LINE_EDGE_COLOR;
extern COLOR CAR_COLOR;
extern COLOR BUS_COLOR;
extern COLOR ARROW_COLOR;
//extern bool DO_IT_NOW;



extern const int PATH_MAX;
extern WCHAR* EXE_PATH;
extern WCHAR DIR_PATH[];


extern CDC MEM_DC;
extern CBitmap MEM_DC_BITMAP;
extern CRect RECT_PIC;
extern CWnd* pPIC;
extern CDC* pPIC_DC;
extern CBrush LINE_BACK_BRUSH;
extern CBrush CAR_BRUSH;
extern CBrush BUS_BRUSH;
extern CBrush RED_BRUSH;
extern CBrush YELLOW_BRUSH;
extern CBrush GREEN_BRUSH;
extern CBrush DISABLED_BRUSH;


extern Scheduler* SELECTED_SCHEDULER;
extern SchedulerPointerContainer* SCHEDULERS;

extern LightGroup DEF_RED_LIGHT;
extern LightGroup DEF_YELLOW_LIGHT;
extern LightGroup DEF_GREEN_LIGHT;



extern VehicleType CAR;
extern VehicleType BUS;

