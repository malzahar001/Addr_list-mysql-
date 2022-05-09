#include"struct.h"
using namespace std;
void find_Person(Person* temp);
//4、查找指定联系人信息
void findPerson(Addressbooks* abs) {
    cout << "请输入您要查找的联系人" << endl;
    string name;
    cin >> name;
    abs->temp.m_Name = name;
    cout << abs->temp.m_Name << endl;
    //判断指定的联系人是否存在通讯录中
    find_Person(&abs->temp);
    system("pause");
    system("cls");//清屏
}
