#include "stdafx.h"
#include "vehicle.h"
#include "SingleLight.h"

// float Vehicle::vehicle_delim() {
// 	return 1;
// }
// 
// //��Ӧʱ��
// float Vehicle::time_delay() {
// 	return 0.3f;
// }
// 
// 
// void Vehicle::start() {
// 	//���������߳�vehicle_controler()
// }
// 
// 
// void Vehicle::pause() {
// 	//��ͣ�����߳�
// }
// 
// void Vehicle::resume() {
// 	//resume the controler thread
// }


//void Vehicle::move(float meter) {
//	position_.set_meters_to_cross(position_.meters_to_cross() - meter);
//}
//δ����ͣ���ߵĳ�������ʻ״̬
//����·�ڵĳ�������ǰ������Լ���
//���̵�����ʱ���г�����ǰ��.���Է�Ӧʱ��

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

