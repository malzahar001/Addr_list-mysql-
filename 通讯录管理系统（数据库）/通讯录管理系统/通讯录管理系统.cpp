#include <iostream>
#include <string>
#include"struct.h"
using namespace std;

int main()
{
    /************************
    *1.用户身份验证
    *
    ************************/
    AdminiInfo Admini;  //当前未填的用户信息
    //判断是否成功登录
    if (login(Admini) == false) {
        cout << "登录失败，请重新登录！" << endl;
        ::system("pause");
        exit(-1);   //立即推出程序，类似return 0;
    }
    else {
        cout << "登录成功，管理员id:" << Admini.id <<  endl;
        cout << "请开始你的表演！" << endl;
        system("pause");
        system("cls");//清屏操作
    }
    /************************
    *2.管理操作
    *
    ************************/
    int select = 0;
    Addressbooks abs;
    abs.m_Size = 0;
    while (true) {
        showMenu();
        cin >> select;
        switch (select) {
        case 1:  //添加联系人
            addPerson(&abs);
            break;
        case 2:  //显示联系人
            showPerson(&abs);
            break;
        case 3:  //删除联系人
            delPerson(&abs);
            break;
        case 4:  //查找联系人
            findPerson(&abs);
            break;
        case 5:  //修改联系人
            alterPerson(&abs);
            break;
        case 6:  //清空联系人
            clearabs(&abs);
            break;
        case 0:  //退出系统
            cout << "欢迎下次使用" << endl;
            system("pause");
            return 0;
            break;
        default:
            break;
        }
    }
    system("pause");
    return 0;
}
