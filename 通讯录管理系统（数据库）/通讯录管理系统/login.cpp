#include "struct.h"
#include "defData.h"
using namespace std;
//������ͨ���û����������ȡ�û���Ϣ����ȡ�ɹ�����true��ʧ��false
bool fetch_Admini_info(AdminiInfo& Admini);  //������һ��Դ�ļ��ĺ�������������

//ʵ�ֶ�ε�¼���ܣ��������Ƿ�ɹ���¼���ж�
bool login(AdminiInfo& Admini) {
    bool ret = false;
    int times = 0;
    do {
        cout << "�����˺ţ�";
        cin >> Admini.AdminiName;
        cout << "�������룺";
        cin >> Admini.password;

        ret = fetch_Admini_info(Admini);//���Ե�¼��������ֵ��trueΪ�ɹ���¼
        times++;

        if (times >= MAX_RETRY_TIMES) {  //��������صǴ����ͷ���ret��Ĭ��ֵfalse
            break;
        }
        if (ret == false) {
            cout << "��¼ʧ�ܣ����������룡" << endl;
        }
    } while (!ret);
    return ret;
}
