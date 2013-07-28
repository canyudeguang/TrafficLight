#pragma once
#include "../stdafx.h"

int straight_arrow(CPoint* arrow,int x5,int y5,int ratio);
int straight_left_arrow(CPoint* arrow,int x5,int y5,int ratio,int from=0,int to=0);
int left_arrow(CPoint* arrow,int x5,int y5,int ratio,int from=0,int to=0);
int uturn_arrow(CPoint* arrow,int x5,int y5,int ratio,int from=0,int to=0);
int right_arrow(CPoint* arrow,int x5,int y5,int ratio,int from=0,int to=0);