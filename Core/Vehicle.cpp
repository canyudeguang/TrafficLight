#include "stdafx.h"
#include "vehicle.h"
#include "SingleLight.h"

// float Vehicle::vehicle_delim() {
// 	return 1;
// }
// 
// //反应时间
// float Vehicle::time_delay() {
// 	return 0.3f;
// }
// 
// 
// void Vehicle::start() {
// 	//启动控制线程vehicle_controler()
// }
// 
// 
// void Vehicle::pause() {
// 	//暂停控制线程
// }
// 
// void Vehicle::resume() {
// 	//resume the controler thread
// }


//void Vehicle::move(float meter) {
//	position_.set_meters_to_cross(position_.meters_to_cross() - meter);
//}
//未到达停车线的车都是行驶状态
//出了路口的车以匀速前进后忽略计算
//当绿灯亮起时所有车都向前进.忽略反应时间

//void Vehicle::vehicle_controler()
//{
//	time_t timestamp = time(0);
//	while (1)
//	{
//		if ( (time()-timestamp) > TIME_DELIM_SEC) {
//			switch (status_)
//			{
//			case 0:return;
//			case 1: 
//				{
//					//timestamp += TIME_DELIM_SEC;
//					//float dis =  speed_*cos(direction_.ratio())*TIME_DELIM_SEC;
//					////float dis_to_obs = distance_to_obstruction(*this);
//					//if (dis > dis_to_obs+vehicle_delim()) {
//					//	dis = dis_to_obs+vehicle_delim();
//					//}
//					//position_.set_meters_to_cross(position_.meters_to_cross() - dis);
//					//break;
//				}
//			default:
//				break;
//			}
//			
//		}
//	}
//}

//void Vehicle::display(std::ostream& os) {
//	os<<"vehicle_id_: "<<vehicle_id_<<"\t";
//	os<<"length_: "<<length_<<"\t";
//	os<<"start_time_: "<<start_time_<<"\t";
//	os<<"type_: "<<type_<<"\t";
//	os<<"speed_: "<<speed_<<"\t";
//	os<<"status_: "<<status_<<"\t";
//	std::cout<<"Position: "<<position_->meters_to_cross();
//	os<<std::endl;
//}
//} 

