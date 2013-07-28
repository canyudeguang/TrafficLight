#include "stdafx.h"
#include "RectDrawer.h"
#include "../Globals.h"




int get_x1(int x2, int a, int ratio) {
	return x2 - a * sin((180-ratio)/RAD);
}

int get_y1(int y2, int a, int ratio) {
	return y2 - a*cos((180-ratio)/RAD);
}
int get_x2(int x1, int a, int ratio) {
	return x1 + a*cos((ratio-90)/RAD);
}

int get_y2(int y1, int a, int ratio) {
	return y1+a*sin((ratio-90)/RAD);
}

int get_x3(int x2, int b, int ratio) {
	return x2+b*cos((180-ratio)/RAD);
}

int get_y3(int y2, int b, int ratio) {
	return y2-b*sin((180-ratio)/RAD);
}

int get_x4(int x1, int b, int ratio) {
	return x1+b*sin((ratio-90)/RAD);
}

int get_y4(int y1,int b, int ratio) {
	return y1-b*cos((ratio-90)/RAD);
}

int get_x5(int x1, int stop_line, int ratio) {
	return x1+stop_line*sin((ratio-90)/RAD);
}

int get_y5(int y1, int stop_line, int ratio) {
	return y1-stop_line*cos((ratio-90)/RAD);
}

int get_x6(int x2, int stop_line, int ratio) {
	return x2+stop_line*sin((ratio-90)/RAD);
}
int get_y6(int y2, int stop_line, int ratio) {
	return y2-stop_line*cos((ratio-90)/RAD);
}

int x_move_to(int x,int length, int ratio) {
	return x+length*cos((ratio-90)/RAD);
}

int y_move_to(int y,int length, int ratio) {
	return y+length*sin((ratio-90)/RAD);
}

int get_x2_from_x3(int x,int length, int ratio) {
	return x-length*sin((ratio-90)/RAD);
}

int get_y2_from_y3(int y,int length,int ratio) {
	return y+length*cos((ratio-90)/RAD);
}