#include "struct.h"
#include "defData.h"
using namespace std;
//功能是通过用户名和密码获取用户信息，获取成功返回true，失败false
bool fetch_Admini_info(AdminiInfo& Admini);  //调用令一个源文件的函数必须先声明

//实现多次登录功能，并返回是否成功登录的判断
bool login(AdminiInfo& Admini) {
    bool ret = false;
    int times = 0;
    do {
        cout << "输入账号：";
        cin >> Admini.AdminiName;
        cout << "输入密码：";
        cin >> Admini.password;

        ret = fetch_Admini_info(Admini);//尝试登录，并返回值，true为成功登录
        times++;

        if (times >= MAX_RETRY_TIMES) {  //超过最大重登次数就返回ret的默认值false
            break;
        }
        if (ret == false) {
            cout << "登录失败，请重新输入！" << endl;
        }
    } while (!ret);
    return ret;
}
