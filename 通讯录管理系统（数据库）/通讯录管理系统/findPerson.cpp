#include"struct.h"
using namespace std;
void find_Person(Person* temp);
//4������ָ����ϵ����Ϣ
void findPerson(Addressbooks* abs) {
    cout << "��������Ҫ���ҵ���ϵ��" << endl;
    string name;
    cin >> name;
    abs->temp.m_Name = name;
    cout << abs->temp.m_Name << endl;
    //�ж�ָ������ϵ���Ƿ����ͨѶ¼��
    find_Person(&abs->temp);
    system("pause");
    system("cls");//����
}
