#include"struct.h"
using namespace std;
void add_Person(Person* temp);
//1�������ϵ��
void addPerson(Addressbooks* abs) {  //�ɵ�ַ�������޸�ʵ��
    //�ж�ͨѶ¼�Ƿ��Ѿ����ˣ�������˾Ͳ������
    if (abs->m_Size == MAX) {
        cout << "ͨѶ¼�������޷���ӣ�" << endl;
        return;
    }
    //��Ӿ�����ϵ��

    //����
    string name;
    cout << "������������ " << endl;
    cin >> abs->temp.m_Name;
    //�Ա�
    cout << "�������Ա� " << endl;
    cout << "1 --- ��" << endl;
    cout << "2 --- Ů" << endl;
    int sex = 0;
    while (true) {
        cin >> sex;
        //���������ȷ���˳�ѭ��
        if (sex == 1 || sex == 2) {
            abs->temp.m_Sex = sex;
            break;
        }
        else cout << "�������,�����������Ա�" << endl;
    }
    //����
    cout << "���������䣺 " << endl;
    int age = 0;
    cin >> age;
    abs->temp.m_Age = age;

    //�绰
    cout << "��������ϵ�绰�� " << endl;
    string phone;
    cin >> phone;
    abs->temp.m_Phone = phone;

    //סַ
    cout << "�������ͥסַ�� " << endl;
    string address;
    cin >> address;
    abs->temp.m_Addr = address;


    abs->m_Size++;//������¼�����ϵ�˸���
    add_Person(&abs->temp); //�������ݿ�

    system("pause");
    system("cls");//��������
    return;
}