#include"struct.h"
using namespace std;
void delete_Person(Person* temp);
bool check_Person(Person* temp);
//3��ɾ��ָ������ϵ��
void delPerson(Addressbooks* abs) {
    cout << "������ɾ����ϵ�������� " << endl;
    string name;
    cin >> name;
    abs->temp.m_Name = name;
    if (check_Person(&abs->temp)) {
        delete_Person(&abs->temp);
    }
    else cout << "ɾ��ʧ��" << endl;
    system("pause");
    system("cls");//����
}