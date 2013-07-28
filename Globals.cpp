#include "stdafx.h"
#include "Generic.h"
#include "Core/LightGroup.h"

class Emulator;
class Scheduler;
class Line;

extern float LEGNTH_PRECISE = 0.00001f;
//时间间隔为0.1s
#ifdef _DEBUG
extern float TIME_DELIM_SEC = 0.1f;
#else
extern float TIME_DELIM_SEC = 0.025f;
#endif

extern float TIME_DELIM_DRIVER_DO = 0.025f;

extern Emulator* GLOBAL_EMU = NULL;
extern int DEF_ROADS = 4;
extern int DEF_LINES = 3;
extern int DEF_VEHICLES = 50;

extern float SAFE_DISTANCE_MULTI = 1.2f;

extern float RAD = 180.0f / 3.1415926f;
extern BOOL DATA_CHANGED = TRUE;

extern float REAL_METERS = 150.0f;
extern float REAL_LINE_WIDTH = 3.5f;
extern float REAL_STOP_LINE = 4.0f;
extern float MAX_REAL_METERS = 1000.0f;
//1.6-2.1
extern float REAL_VEH_WIDTH = 1.8f;
extern float REAL_ARROW_WIDTH = 1.3f;
extern int DEF_YELLOW_TIME = 3;

//600 / 150



extern int MAIN_RECT_X = 0;
extern int MAIN_RECT_Y = 0;
extern int MAIN_RECT_WIDTH = 600;
extern int MAIN_RECT_HEIGHT = 600;

float VIRTUAL_RATIO = MAIN_RECT_WIDTH/REAL_METERS;

extern int LINE_WIDTH = REAL_LINE_WIDTH * VIRTUAL_RATIO;
extern int VEH_WIDTH = REAL_VEH_WIDTH * VIRTUAL_RATIO;
//extern int LIGHT_WIDTH = LINE_WIDTH / 5;
extern int CENTER_X = MAIN_RECT_X + MAIN_RECT_WIDTH / 2;
extern int CENTER_Y = MAIN_RECT_Y + MAIN_RECT_HEIGHT / 2;
extern int STOP_LINE = REAL_STOP_LINE * VIRTUAL_RATIO;
extern int LIGHT_RADIUM = LINE_WIDTH / 2;
//extern int ARROW_WIDTH = LINE_WIDTH * 0.8f;
extern int ARROW_DISTANCE = 2*LINE_WIDTH;
extern float ARROW_VIRTUAL_RATIO = 
	REAL_LINE_WIDTH / REAL_ARROW_WIDTH * VIRTUAL_RATIO * 1;/*LINE_WIDTH*1.0f/REAL_ARROW_WIDTH*/;

extern Road* SELECTED_ROAD = NULL;
extern Line* SELECTED_LINE = NULL;




extern COLOR BACKGROUND_COLOR(240,240,240);
extern COLOR ROAD_EDGE_COLOR(255,255,255);
extern COLOR ROAD_COLOR(200,200,200);
extern COLOR LINE_EDGE_COLOR(100,100,100);
extern COLOR CAR_COLOR(50,50,50);
extern COLOR BUS_COLOR(80,80,80);
extern COLOR LINE_BACK_COLOR(150,150,150);
extern COLOR ARROW_COLOR(244,244,244);
//extern bool DO_IT_NOW = false;

extern const int PATH_MAX = 513;
extern WCHAR* EXE_PATH=NULL;
extern WCHAR DIR_PATH[PATH_MAX]={0};

extern CDC MEM_DC=CDC();
extern CBitmap MEM_DC_BITMAP=CBitmap();
extern CRect RECT_PIC=CRect();
extern CWnd* pPIC = NULL;
extern CDC* pPIC_DC = NULL;
extern CBrush LINE_BACK_BRUSH(LINE_BACK_COLOR.rgb());
extern CBrush CAR_BRUSH(CAR_COLOR.rgb());
extern CBrush BUS_BRUSH(BUS_COLOR.rgb());
extern CBrush RED_BRUSH(RGB(255,0,0));
extern CBrush YELLOW_BRUSH(RGB(255,255,0));
extern CBrush GREEN_BRUSH(RGB(0,255,0));
extern CBrush DISABLED_BRUSH(RGB(30,20,30));

extern Scheduler* SELECTED_SCHEDULER=NULL;
extern SchedulerPointerContainer* SCHEDULERS=new SchedulerPointerContainer();

extern LightGroup DEF_RED_LIGHT=LightGroup();
extern LightGroup DEF_YELLOW_LIGHT=LightGroup();
extern LightGroup DEF_GREEN_LIGHT=LightGroup();

extern VehicleType CAR = {
	4.0f,	//max_accel_factor_
	-3.0f,	//max_break_factor_
	3.0f,	//length_min_
	5.0f,	//length_max_
	3.0f,	//slow_speed_
	12.0f	//max_speed_
};

extern VehicleType BUS = {
	3.0f,	//max_accel_factor_
	-2.3f,	//max_break_factor_
	12.0f,	//length_min_
	14.0f,	//length_max_
	2.5f,	//slow_speed_
	8.0f	//max_speed_
};