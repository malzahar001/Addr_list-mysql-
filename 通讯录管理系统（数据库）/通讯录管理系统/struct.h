#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include <conio.h>
#include <cstring>
using namespace std;
#define MAX 1000 //通讯录最大容量
//联系人结构体
struct Person {
    string m_Name;//姓名
    int m_Sex;//性别：1男 2女
    int m_Age;//年龄
    string m_Phone;//电话
    string m_Addr;//住址
};
//通讯录结构体
struct Addressbooks {
    Person temp;//暂存某人员信息
    int m_Size;//通讯录中人员个数
};
//用户信息结构
struct AdminiInfo {
	int id;       //管理员id
	string AdminiName; //用户名
	string password; //密码
};
//管理函数声明
void showMenu();
void addPerson(Addressbooks* abs);
void showPerson(Addressbooks* abs);
void delPerson(Addressbooks* abs);
void findPerson(Addressbooks* abs);
void alterPerson(Addressbooks* abs);
void clearabs(Addressbooks* abs);

//登录函数声明
bool login(AdminiInfo& Admini);