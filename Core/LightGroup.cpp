#include "stdafx.h"
#include "SingleLight.h"
#include "LightGroup.h"


LightGroup::LightGroup():count(0)
{
	lights_ = new LightContainer();
}

LightGroup::LightGroup(const LightGroup& rhs ):count(0)
{
	lights_ = new LightContainer(*(rhs.lights()));
	duration_ = rhs.duration_;
}

LightGroup::LightGroup( LightContainer* lc,int duration ) :count(0)
{
	lights_ = new LightContainer(*lc);
	duration_ = duration;
}

LightGroup::~LightGroup()
{
	if (lights_ != NULL) {
		delete lights_;
	}
}


//Need test
LightColor LightGroup::light_enabled( Direction dir_to_eva )
{
	int in_level = dir_level(dir_to_eva);

	auto light_iter = lights_->begin();
	//Direction min_dir = light_iter->direction();
	auto min_dir_iter = light_iter;
	for (; light_iter!=lights_->end(); ++light_iter) {
		if (light_iter->light_on())
		{
			if (isAcceptable(dir_to_eva,light_iter->direction()))
			{
				if (*min_dir_iter <= *light_iter)
				{
					min_dir_iter=light_iter;
				}
			}
		}
	}
	
	return min_dir_iter->color();
}

bool LightGroup::operator != (const LightGroup& rhs) {
	return
		*lights_ != *rhs.lights_ ||
		duration_ != rhs.duration_;
}
bool LightGroup::operator==(const  LightGroup& rhs )
{
	return !(*this != rhs);
}

bool LightGroup::add_light( SingleLight& sl )
{
	return add_unique<SingleLight,LightContainer>(sl,lights_);
}

bool LightGroup::del_light( SingleLight& sl )
{
	return search_for_delete<SingleLight,LightContainer>(sl,lights_);
}

void LightGroup::time_decrease()
{
	++count;
	if (FloatEqual(count*TIME_DELIM_SEC, 1.0f)) {
		--duration_;
		count = 0;
	}
}
