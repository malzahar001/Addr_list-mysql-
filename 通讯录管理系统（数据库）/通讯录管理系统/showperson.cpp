#include"struct.h"
using namespace std;
void show_Person();
//2、显示所有联系人
void showPerson(Addressbooks* abs) {
    //判断通讯录中人数是否为0，如果为0，提示记录为空
    //如果不为0，显示记录的联系人信息
    show_Person();
    system("pause");
    system("cls");//清屏
}