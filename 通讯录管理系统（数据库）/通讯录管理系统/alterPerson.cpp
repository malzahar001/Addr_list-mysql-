#include"struct.h"
using namespace std;
//修改：先查找，然后删除，然后插入
bool check_Person(Person* temp);
void delete_Person(Person* temp);
void add_Person(Person* temp);
//5、修改联系人信息
void alterPerson(Addressbooks* abs) {
    cout << "请输入您要修改的联系人" << endl;
    string name;
    cin >> name;
    //判断指定的联系人是否存在通讯录中
    if (!check_Person(&abs->temp))
        cout << "查无此人" << endl;
    else {
        delete_Person(&abs->temp);
        cout << "请输入新姓名" << endl;
        cin >> abs->temp.m_Name;
        cout << "请输入新性别 1---男 2---女" << endl;
        while (true) {
            cin >> abs->temp.m_Sex;
            if (abs->temp.m_Sex == 1 || abs->temp.m_Sex == 2)
                break;
            else
                cout << "性别输入错误，请重新输入性别" << endl;
        }
        cout << "请输入新年龄" << endl;
        cin >> abs->temp.m_Age;
        cout << "请输入新电话" << endl;
        cin >> abs->temp.m_Phone;
        cout << "请输入新住址" << endl;
        cin >> abs->temp.m_Addr;
        cout << "修改成功" << endl;
        add_Person(&abs->temp);
    }
    system("pause");
    system("cls");//清屏
}