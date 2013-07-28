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
	// cases:�ܹ��ж����ֿ���,Ȼ���ǵ�һ�ֿ����Եİٷֱ�,�ڶ���...ֱ����N��...
	// δָ���ĸ��ʽ���ƽ��(����ƽ�ֵĻ����һ�����ʻ�����)
	// ��-1��ʾ����
	// possibily_sum:�����Եĺ��Ƕ���
	// ����ֵ��ʾ����ǵڼ������,����0��ʾ����
	if (cases<2 || first_percent>possibility_sum) return 0;

	//��arg_struct����ɱ�����б�
	va_list arg_struct;
	int arg_num = 0;
	int temp = -1;
	vector<int> para(cases);
	para.insert(para.begin(),first_percent);
	auto para_iter = ++para.begin();
	va_start(arg_struct,first_percent);
	while(true) {

		//��arg_struct��ȡ��һ��int�͵����ŵ�temp��
		temp = va_arg(arg_struct,int);
		//��ȡ������Ϊ-1��ֹͣȡ������
		if (temp == -1) break;
		para.insert(para_iter++,temp);
	}
	int sum = 0;

	//��������Ե��ܺ�
	for_each(para.begin(),para_iter,[&](int& i) { sum+=i;});
	if (sum>possibility_sum) {
		return 0;
	}

	// ��δָ���ĸ��ʲ�ȫ
	if (sum != possibility_sum) {
		int percent_per_case = 
			(possibility_sum-sum)/(cases-distance(para.begin(),para_iter));
		for_each(para_iter,para.end(),
			[&](int& possibility) { possibility = percent_per_case;});
		//���һ��case�ĸ��ʲ���ȷ.���ǲ���Ҫ����.
	}

	//�ó������
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