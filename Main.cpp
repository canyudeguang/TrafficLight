
#include "stdafx.h"
#include "Generic.h"



using namespace std;



int main() {
	//std::locale::global(std::locale("chs"));
	//wcout.imbue(locale(locale(),"chs",LC_CTYPE));
	setlocale(LC_CTYPE,"chs");
	wcout<<"Chinese after me"<<endl;
	wcout<<"�����й���"<<endl;
	wcout<<"Chinese before me"<<endl;



	/*Road north1road(2001,3,"��·",);
	Road south1road(2002,4,"��·");
	Road east1road(2003,2,"��·");
	Road west1road(2004,2,"��·");*/
// 	Line line1ofnumber1north(1001200101,"��һ·��1",nullptr,nullptr,100,nullptr);
// 	Road temproad[] = {
// 		Road(2001,3,"��1·"),
// 		Road(2002,4,"��1·"),
// 		Road(2003,2,"��1·"),
// 		Road(2004,2,"��1·")};
// 	Cross number1cross(1001,"��Ӧ����",4,CrossType(temproad,temproad+4));
// 	number1cross.display(wcout);
// 	number1cross.displayall(wcout);
}