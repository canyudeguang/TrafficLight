/************************************************************************/
/* 一个LightGroup对象相当于一组SingleLight的一个状态;                                                      */
/************************************************************************/

#include <vector>
#include "../Generic.h"
#include "../Subject.h"
#include "../Globals.h"

using std::vector;

class SingleLight;


typedef vector<SingleLight> LightContainer;

class LightGroup : public Subject {
public:
	LightGroup();
	~LightGroup();
	LightGroup(LightContainer* lc,int duration);
	LightGroup(const LightGroup& rhs);
	LightContainer* lights() const {
		return lights_;
	}

	void time_decrease();
	
	int duration() const { return duration_; }
	void set_duration(const int& duration) { duration_ = duration; }
	
	LightColor light_enabled(Direction dir_to_eva);

	bool operator == (const LightGroup& rhs);

	bool add_light(SingleLight& sl);
	bool del_light(SingleLight& sl);
	bool LightGroup::operator != (const LightGroup& rhs);

private:
	LightContainer* lights_;
	int duration_;
	int count;
};
