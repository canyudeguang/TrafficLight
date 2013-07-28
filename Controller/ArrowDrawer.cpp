#include "stdafx.h"
#include "ArrowDrawer.h"
#include "RectDrawer.h"
#include "../Globals.h"
/*
*	可以只画其中的某几个点。from >>> to
*/

float fifteen = 0.2f;
float twenty = 0.25f;
float twentytwentyfive = 0.275f;
int straight_arrow( CPoint* arrow,int x5,int y5,int ratio )
{
	int min_size = 8;

	arrow[0].x = get_x3(get_x2(x5,LINE_WIDTH/2,ratio),ARROW_DISTANCE,ratio);
	arrow[0].y = get_y3(get_y2(y5,LINE_WIDTH/2,ratio),ARROW_DISTANCE,ratio);


	arrow[1].x = get_x1(get_x4(arrow[0].x,1.2*ARROW_VIRTUAL_RATIO,ratio),twentytwentyfive*ARROW_VIRTUAL_RATIO,ratio);
	arrow[1].y = get_y1(get_y4(arrow[0].y,1.2*ARROW_VIRTUAL_RATIO,ratio),twentytwentyfive*ARROW_VIRTUAL_RATIO,ratio);


	arrow[2].x = get_x2(arrow[1].x,fifteen*ARROW_VIRTUAL_RATIO,ratio);
	arrow[2].y = get_y2(arrow[1].y,fifteen*ARROW_VIRTUAL_RATIO,ratio);


	arrow[3].x = get_x4(arrow[2].x,1.8*ARROW_VIRTUAL_RATIO,ratio);
	arrow[3].y = get_y4(arrow[2].y,1.8*ARROW_VIRTUAL_RATIO,ratio);


	arrow[4].x = get_x2(arrow[3].x,fifteen*ARROW_VIRTUAL_RATIO,ratio);
	arrow[4].y = get_y2(arrow[3].y,fifteen*ARROW_VIRTUAL_RATIO,ratio);


	arrow[5].x = get_x2_from_x3(arrow[4].x,1.8*ARROW_VIRTUAL_RATIO,ratio);
	arrow[5].y = get_y2_from_y3(arrow[4].y,1.8*ARROW_VIRTUAL_RATIO,ratio);


	arrow[6].x = get_x2(arrow[5].x,fifteen*ARROW_VIRTUAL_RATIO,ratio);
	arrow[6].y = get_y2(arrow[5].y,fifteen*ARROW_VIRTUAL_RATIO,ratio);


	arrow[7].x = arrow[0].x;
	arrow[7].y = arrow[0].y;


	return min_size;
}

int straight_left_arrow( CPoint* arrow,int x5,int y5,int ratio,int from/*=0*/,int to/*=0*/ )
{
	int min_size = 14;
	arrow[0].x = get_x3(get_x2(x5,LINE_WIDTH/2-0.2*ARROW_VIRTUAL_RATIO,ratio),ARROW_DISTANCE,ratio);
	arrow[0].y = get_y3(get_y2(y5,LINE_WIDTH/2-0.2*ARROW_VIRTUAL_RATIO,ratio),ARROW_DISTANCE,ratio);


	arrow[1].x = get_x1(get_x4(arrow[0].x,1.2*ARROW_VIRTUAL_RATIO,ratio),twentytwentyfive*ARROW_VIRTUAL_RATIO,ratio);
	arrow[1].y = get_y1(get_y4(arrow[0].y,1.2*ARROW_VIRTUAL_RATIO,ratio),twentytwentyfive*ARROW_VIRTUAL_RATIO,ratio);


	arrow[2].x = get_x2(arrow[1].x,fifteen*ARROW_VIRTUAL_RATIO,ratio);
	arrow[2].y = get_y2(arrow[1].y,fifteen*ARROW_VIRTUAL_RATIO,ratio);


	arrow[3].x = get_x4(arrow[2].x,1.8*ARROW_VIRTUAL_RATIO,ratio);
	arrow[3].y = get_y4(arrow[2].y,1.8*ARROW_VIRTUAL_RATIO,ratio);


	arrow[4].x = get_x2(arrow[3].x,fifteen*ARROW_VIRTUAL_RATIO,ratio);
	arrow[4].y = get_y2(arrow[3].y,fifteen*ARROW_VIRTUAL_RATIO,ratio);

	arrow[5].x=get_x2_from_x3(arrow[4].x,twenty*ARROW_VIRTUAL_RATIO,ratio);
	arrow[5].y=get_y2_from_y3(arrow[4].y,twenty*ARROW_VIRTUAL_RATIO,ratio);


	arrow[6].x=get_x2_from_x3(get_x2(arrow[5].x,0.4*ARROW_VIRTUAL_RATIO,ratio),0.4*ARROW_VIRTUAL_RATIO,ratio);
	arrow[6].y=get_y2_from_y3(get_y2(arrow[5].y,0.4*ARROW_VIRTUAL_RATIO,ratio),0.4*ARROW_VIRTUAL_RATIO,ratio);


	arrow[7].x=get_x3(arrow[6].x,0.45*ARROW_VIRTUAL_RATIO,ratio);
	arrow[7].y=get_y3(arrow[6].y,0.45*ARROW_VIRTUAL_RATIO,ratio);


	arrow[8].x=get_x2_from_x3(get_x2(arrow[7].x,twenty*ARROW_VIRTUAL_RATIO,ratio),0.8*ARROW_VIRTUAL_RATIO,ratio);
	arrow[8].y=get_y2_from_y3(get_y2(arrow[7].y,twenty*ARROW_VIRTUAL_RATIO,ratio),0.8*ARROW_VIRTUAL_RATIO,ratio);


	arrow[9].x=get_x2_from_x3(arrow[7].x,1.55*ARROW_VIRTUAL_RATIO,ratio);
	arrow[9].y=get_y2_from_y3(arrow[7].y,1.55*ARROW_VIRTUAL_RATIO,ratio);

	arrow[10].x=get_x4(arrow[9].x,0.5*ARROW_VIRTUAL_RATIO,ratio);
	arrow[10].y=get_y4(arrow[9].y,0.5*ARROW_VIRTUAL_RATIO,ratio);

	arrow[11].x=get_x2_from_x3(arrow[5].x,0.5*ARROW_VIRTUAL_RATIO,ratio);
	arrow[11].y=get_y2_from_y3(arrow[5].y,0.5*ARROW_VIRTUAL_RATIO,ratio);

	arrow[12].x=get_x2_from_x3(arrow[11].x,1.2*ARROW_VIRTUAL_RATIO,ratio);
	arrow[12].y=get_y2_from_y3(arrow[11].y,1.2*ARROW_VIRTUAL_RATIO,ratio);

	arrow[13].x=get_x2(arrow[12].x,fifteen*ARROW_VIRTUAL_RATIO,ratio);
	arrow[13].y=get_y2(arrow[12].y,fifteen*ARROW_VIRTUAL_RATIO,ratio);


	arrow[14].x=arrow[0].x;
	arrow[14].y=arrow[0].y;


	return min_size;
}

int right_arrow( CPoint* arrow,int x5,int y5,int ratio,int from/*=0*/,int to/*=0*/ )
{
	int min_size = 10;

	arrow[0].x=get_x4(get_x1(get_x2(x5,LINE_WIDTH/2,ratio),twenty*ARROW_VIRTUAL_RATIO,ratio),ARROW_DISTANCE,ratio);
	arrow[0].y=get_y4(get_y1(get_y2(y5,LINE_WIDTH/2,ratio),twenty*ARROW_VIRTUAL_RATIO,ratio),ARROW_DISTANCE,ratio);

	arrow[1].x=get_x1(get_x4(arrow[0].x,0.8*ARROW_VIRTUAL_RATIO,ratio),0.2*ARROW_VIRTUAL_RATIO,ratio);
	arrow[1].y=get_y1(get_y4(arrow[0].y,0.8*ARROW_VIRTUAL_RATIO,ratio),0.2*ARROW_VIRTUAL_RATIO,ratio);

	arrow[2].x=get_x3(get_x2(arrow[1].x,twenty*ARROW_VIRTUAL_RATIO,ratio),0.85*ARROW_VIRTUAL_RATIO,ratio);
	arrow[2].y=get_y3(get_y2(arrow[1].y,twenty*ARROW_VIRTUAL_RATIO,ratio),0.85*ARROW_VIRTUAL_RATIO,ratio);

	arrow[3].x=get_x2_from_x3(arrow[2].x,0.55*ARROW_VIRTUAL_RATIO,ratio);
	arrow[3].y=get_y2_from_y3(arrow[2].y,0.55*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[4].x=get_x3(get_x2(arrow[3].x,0.4*ARROW_VIRTUAL_RATIO,ratio),0.45*ARROW_VIRTUAL_RATIO,ratio);
	arrow[4].y=get_y3(get_y2(arrow[3].y,0.4*ARROW_VIRTUAL_RATIO,ratio),0.45*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[5].x=get_x4(arrow[4].x,1.35*ARROW_VIRTUAL_RATIO,ratio);
	arrow[5].y=get_y4(arrow[4].y,1.35*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[6].x=get_x2(arrow[5].x,fifteen*ARROW_VIRTUAL_RATIO,ratio);
	arrow[6].y=get_y2(arrow[5].y,fifteen*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[7].x=get_x2_from_x3(arrow[6].x,1.85*ARROW_VIRTUAL_RATIO,ratio);
	arrow[7].y=get_y2_from_y3(arrow[6].y,1.85*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[8].x=get_x2_from_x3(arrow[3].x,0.6*ARROW_VIRTUAL_RATIO,ratio);
	arrow[8].y=get_y2_from_y3(arrow[3].y,0.6*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[9].x=arrow[0].x;
	arrow[9].y=arrow[0].y;
	
	return min_size;
}

int uturn_arrow( CPoint* arrow,int x5,int y5,int ratio,int from/*=0*/,int to/*=0*/ )
{
	int min_size = 12;
	arrow[0].x=get_x4(get_x2(x5,LINE_WIDTH/2+0.35*ARROW_VIRTUAL_RATIO,ratio),ARROW_DISTANCE,ratio);
	arrow[0].y=get_y4(get_y2(y5,LINE_WIDTH/2+0.35*ARROW_VIRTUAL_RATIO,ratio),ARROW_DISTANCE,ratio);
	
	arrow[1].x=get_x1(arrow[0].x,0.9*ARROW_VIRTUAL_RATIO,ratio);
	arrow[1].y=get_y1(arrow[0].y,0.9*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[2].x=get_x4(arrow[1].x,3*ARROW_VIRTUAL_RATIO,ratio);
	arrow[2].y=get_y4(arrow[1].y,3*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[3].x=get_x2(arrow[2].x,twenty*ARROW_VIRTUAL_RATIO,ratio);
	arrow[3].y=get_y2(arrow[2].y,twenty*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[4].x=get_x2_from_x3(arrow[3].x,2.55*ARROW_VIRTUAL_RATIO,ratio);
	arrow[4].y=get_y2_from_y3(arrow[3].y,2.55*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[5].x=get_x2(arrow[4].x,0.5*ARROW_VIRTUAL_RATIO,ratio);
	arrow[5].y=get_y2(arrow[4].y,0.5*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[6].x=get_x4(arrow[5].x,0.55*ARROW_VIRTUAL_RATIO,ratio);
	arrow[6].y=get_y4(arrow[5].y,0.55*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[7].x=get_x1(arrow[6].x,twenty*ARROW_VIRTUAL_RATIO,ratio);
	arrow[7].y=get_y1(arrow[6].y,twenty*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[8].x=get_x3(get_x2(arrow[7].x,0.3*ARROW_VIRTUAL_RATIO,ratio),1.2*ARROW_VIRTUAL_RATIO,ratio);
	arrow[8].y=get_y3(get_y2(arrow[7].y,0.3*ARROW_VIRTUAL_RATIO,ratio),1.2*ARROW_VIRTUAL_RATIO,ratio);
	
	arrow[9].x=get_x2_from_x3(get_x2(arrow[8].x,0.3*ARROW_VIRTUAL_RATIO,ratio),1.2*ARROW_VIRTUAL_RATIO,ratio);
	arrow[9].y=get_y2_from_y3(get_y2(arrow[8].y,0.3*ARROW_VIRTUAL_RATIO,ratio),1.2*ARROW_VIRTUAL_RATIO,ratio);

	arrow[10].x=get_x1(arrow[9].x,twenty*ARROW_VIRTUAL_RATIO,ratio);
	arrow[10].y=get_y1(arrow[9].y,twenty*ARROW_VIRTUAL_RATIO,ratio);


	arrow[11].x=arrow[0].x;
	arrow[11].y=arrow[9].y;




	return min_size;
}

int left_arrow( CPoint* arrow,int x5,int y5,int ratio,int from/*=0*/,int to/*=0*/ )
{
	//ratio+=180;
	int min_size=10;
	arrow[0].x = get_x4(get_x2(x5,LINE_WIDTH/2+0.175*ARROW_VIRTUAL_RATIO,ratio),ARROW_DISTANCE,ratio);
	arrow[0].y = get_y4(get_y2(y5,LINE_WIDTH/2+0.175*ARROW_VIRTUAL_RATIO,ratio),ARROW_DISTANCE,ratio);

	arrow[1].x = get_x4(arrow[0].x,0.5*ARROW_VIRTUAL_RATIO,ratio);
	arrow[1].y = get_y4(arrow[0].y,0.5*ARROW_VIRTUAL_RATIO,ratio);

	arrow[2].x = get_x1(get_x4(arrow[1].x,0.65*ARROW_VIRTUAL_RATIO,ratio),0.55*ARROW_VIRTUAL_RATIO,ratio);
	arrow[2].y = get_y1(get_y4(arrow[1].y,0.65*ARROW_VIRTUAL_RATIO,ratio),0.55*ARROW_VIRTUAL_RATIO,ratio);

	arrow[3].x = get_x4(arrow[2].x,1.85*ARROW_VIRTUAL_RATIO,ratio);
	arrow[3].y = get_y4(arrow[2].y,1.85*ARROW_VIRTUAL_RATIO,ratio);

	arrow[4].x = get_x2(arrow[3].x,fifteen*ARROW_VIRTUAL_RATIO,ratio);
	arrow[4].y = get_y2(arrow[3].y,fifteen*ARROW_VIRTUAL_RATIO,ratio);

	arrow[5].x = get_x2_from_x3(arrow[4].x,1.35*ARROW_VIRTUAL_RATIO,ratio);
	arrow[5].y = get_y2_from_y3(arrow[4].y,1.35*ARROW_VIRTUAL_RATIO,ratio);

	arrow[6].x = get_x2_from_x3(get_x2(arrow[5].x,0.4*ARROW_VIRTUAL_RATIO,ratio),0.45*ARROW_VIRTUAL_RATIO,ratio);
	arrow[6].y = get_y2_from_y3(get_y2(arrow[5].y,0.4*ARROW_VIRTUAL_RATIO,ratio),0.45*ARROW_VIRTUAL_RATIO,ratio);

	arrow[7].x = get_x4(arrow[6].x,0.45*ARROW_VIRTUAL_RATIO,ratio);
	arrow[7].y = get_y4(arrow[6].y,0.45*ARROW_VIRTUAL_RATIO,ratio);

	arrow[8].x = get_x2(get_x2_from_x3(arrow[7].x,0.75*ARROW_VIRTUAL_RATIO,ratio),twenty *ARROW_VIRTUAL_RATIO,ratio);
	arrow[8].y = get_y2(get_y2_from_y3(arrow[7].y,0.75*ARROW_VIRTUAL_RATIO,ratio),twenty*ARROW_VIRTUAL_RATIO,ratio);

	arrow[9].x = arrow[0].x;
	arrow[9].y = arrow[0].y;
	return min_size;

}