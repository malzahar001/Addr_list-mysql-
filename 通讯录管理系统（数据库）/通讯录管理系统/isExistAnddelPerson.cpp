#include"struct.h"
using namespace std;
void delete_Person(Person* temp);
bool check_Person(Person* temp);
//3、删除指定的联系人
void delPerson(Addressbooks* abs) {
    cout << "请输入删除联系人姓名： " << endl;
    string name;
    cin >> name;
    abs->temp.m_Name = name;
    if (check_Person(&abs->temp)) {
        delete_Person(&abs->temp);
    }
    else cout << "删除失败" << endl;
    system("pause");
    system("cls");//清屏
}