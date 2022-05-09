#include"struct.h"
using namespace std;
void add_Person(Person* temp);
//1、添加联系人
void addPerson(Addressbooks* abs) {  //由地址传递来修改实参
    //判断通讯录是否已经满了，如果满了就不再添加
    if (abs->m_Size == MAX) {
        cout << "通讯录已满，无法添加！" << endl;
        return;
    }
    //添加具体联系人

    //姓名
    string name;
    cout << "请输入姓名： " << endl;
    cin >> abs->temp.m_Name;
    //性别
    cout << "请输入性别： " << endl;
    cout << "1 --- 男" << endl;
    cout << "2 --- 女" << endl;
    int sex = 0;
    while (true) {
        cin >> sex;
        //如果输入正确，退出循环
        if (sex == 1 || sex == 2) {
            abs->temp.m_Sex = sex;
            break;
        }
        else cout << "输入错误,请重新输入性别" << endl;
    }
    //年龄
    cout << "请输入年龄： " << endl;
    int age = 0;
    cin >> age;
    abs->temp.m_Age = age;

    //电话
    cout << "请输入联系电话： " << endl;
    string phone;
    cin >> phone;
    abs->temp.m_Phone = phone;

    //住址
    cout << "请输入家庭住址： " << endl;
    string address;
    cin >> address;
    abs->temp.m_Addr = address;


    abs->m_Size++;//增加已录入的联系人个数
    add_Person(&abs->temp); //插入数据库

    system("pause");
    system("cls");//清屏操作
    return;
}