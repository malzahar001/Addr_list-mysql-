#include"struct.h"
using namespace std;
//�޸ģ��Ȳ��ң�Ȼ��ɾ����Ȼ�����
bool check_Person(Person* temp);
void delete_Person(Person* temp);
void add_Person(Person* temp);
//5���޸���ϵ����Ϣ
void alterPerson(Addressbooks* abs) {
    cout << "��������Ҫ�޸ĵ���ϵ��" << endl;
    string name;
    cin >> name;
    //�ж�ָ������ϵ���Ƿ����ͨѶ¼��
    if (!check_Person(&abs->temp))
        cout << "���޴���" << endl;
    else {
        delete_Person(&abs->temp);
        cout << "������������" << endl;
        cin >> abs->temp.m_Name;
        cout << "���������Ա� 1---�� 2---Ů" << endl;
        while (true) {
            cin >> abs->temp.m_Sex;
            if (abs->temp.m_Sex == 1 || abs->temp.m_Sex == 2)
                break;
            else
                cout << "�Ա�������������������Ա�" << endl;
        }
        cout << "������������" << endl;
        cin >> abs->temp.m_Age;
        cout << "�������µ绰" << endl;
        cin >> abs->temp.m_Phone;
        cout << "��������סַ" << endl;
        cin >> abs->temp.m_Addr;
        cout << "�޸ĳɹ�" << endl;
        add_Person(&abs->temp);
    }
    system("pause");
    system("cls");//����
}