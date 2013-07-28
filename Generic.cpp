//#include <random>


#include "stdafx.h"
#include "Generic.h"
#include "Core/Vehicle.h"
#include "Globals.h"
#include "Scheduler/Scheduler.h"
bool almost_equal( const float& lhs, const float& rhs, float min_delta /*= 0.3*/ )
{

	return abs(rhs-lhs) < min_delta;
}

Scheduler* find_scheduler(CString& name) {
	auto scheduler_iter = 
		find_if(SCHEDULERS->begin(),SCHEDULERS->end(),[&](Scheduler*& s) {
			return s->name() == name;
	});
	if (scheduler_iter != SCHEDULERS->end())
	{
		return *scheduler_iter;
	}
	else
	{
		return NULL;
	}
}

bool isAcceptable( Direction inside, Direction outside )
{
	//| &
	if( ((inside|outside) & outside) != outside) {
		return false;
	}
	return true;
}

int dir_level( const Direction& dir )
{
	int in_level = 0;
	switch (dir)
	{
	case STRAIGHT:
	case LEFT:
	case RIGHT:
	case UTRUN:
		in_level = 0;
		break;
	case STRAIGHT_LEFT:
	case STRAIGHT_RIGHT:
	case STRAIGHT_UTRUN:
	case LEFT_UTRUN:
		in_level = 1;
		break;
	case ALL:
		in_level = 2;
		break;
	}
	return in_level;
}

int SelectCase(int cases, int possibility_sum, int first_percent,... )    
{
	// cases:总共有多少种可能,然后是第一种可能性的百分比,第二种...直到第N种...
	// 未指明的概率将被平分(不能平分的话最后一个概率会奇葩)
	// 用-1表示结束
	// possibily_sum:可能性的和是多少
	// 返回值表示这次是第几种情况,返回0表示错误
	if (cases<2 || first_percent>possibility_sum) return 0;

	//由arg_struct保存可变参数列表
	va_list arg_struct;
	int arg_num = 0;
	int temp = -1;
	vector<int> para(cases);
	para.insert(para.begin(),first_percent);
	auto para_iter = ++para.begin();
	va_start(arg_struct,first_percent);
	while(true) {

		//从arg_struct中取出一个int型的数放到temp中
		temp = va_arg(arg_struct,int);
		//当取出的数为-1是停止取出参数
		if (temp == -1) break;
		para.insert(para_iter++,temp);
	}
	int sum = 0;

	//求出可能性的总和
	for_each(para.begin(),para_iter,[&](int& i) { sum+=i;});
	if (sum>possibility_sum) {
		return 0;
	}

	// 把未指明的概率补全
	if (sum != possibility_sum) {
		int percent_per_case = 
			(possibility_sum-sum)/(cases-distance(para.begin(),para_iter));
		for_each(para_iter,para.end(),
			[&](int& possibility) { possibility = percent_per_case;});
		//最后一个case的概率不正确.但是不需要计算.
	}

	//得出随机数
	int rand_num = rand()%possibility_sum;
	int return_val = 1;
	para_iter = para.begin();
	rand_num -= *para_iter;
	while(rand_num>0) {
		rand_num -= *para_iter;
		++return_val;
		++para_iter;
	}
	return return_val;
}

bool FloatEqual( const float& a, const float& b )
{
	return abs(a-b)<FLT_EPSILON;
}

WCHAR* directory_path(WCHAR* exe_path, int size, WCHAR* dir_path) {
	bool found = false;
	int index = size-1;
	int found_index = 0;
	for (; index>=0; --index) {
		if (exe_path[index] == WCHAR('\\')) {
			found_index = index;
			found = true;
			break;
		}
	}
	if (found)
	{
		dir_path[found_index--] = WCHAR('\0');
		for (; found_index>=0; --found_index) {
			dir_path[found_index] = exe_path[found_index];
		}
	}
	return dir_path;
}