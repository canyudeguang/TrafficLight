
#include "stdafx.h"
#include "Generic.h"



using namespace std;



int main() {
	//std::locale::global(std::locale("chs"));
	//wcout.imbue(locale(locale(),"chs",LC_CTYPE));
	setlocale(LC_CTYPE,"chs");
	wcout<<"Chinese after me"<<endl;
	wcout<<"我是中国人"<<endl;
	wcout<<"Chinese before me"<<endl;



	/*Road north1road(2001,3,"北路",);
	Road south1road(2002,4,"南路");
	Road east1road(2003,2,"东路");
	Road west1road(2004,2,"西路");*/
// 	Line line1ofnumber1north(1001200101,"北一路道1",nullptr,nullptr,100,nullptr);
// 	Road temproad[] = {
// 		Road(2001,3,"北1路"),
// 		Road(2002,4,"南1路"),
// 		Road(2003,2,"东1路"),
// 		Road(2004,2,"西1路")};
// 	Cross number1cross(1001,"嘉应立交",4,CrossType(temproad,temproad+4));
// 	number1cross.display(wcout);
// 	number1cross.displayall(wcout);
}