#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include <conio.h>
#include <cstring>
using namespace std;
#define MAX 1000 //ͨѶ¼�������
//��ϵ�˽ṹ��
struct Person {
    string m_Name;//����
    int m_Sex;//�Ա�1�� 2Ů
    int m_Age;//����
    string m_Phone;//�绰
    string m_Addr;//סַ
};
//ͨѶ¼�ṹ��
struct Addressbooks {
    Person temp;//�ݴ�ĳ��Ա��Ϣ
    int m_Size;//ͨѶ¼����Ա����
};
//�û���Ϣ�ṹ
struct AdminiInfo {
	int id;       //����Աid
	string AdminiName; //�û���
	string password; //����
};
//����������
void showMenu();
void addPerson(Addressbooks* abs);
void showPerson(Addressbooks* abs);
void delPerson(Addressbooks* abs);
void findPerson(Addressbooks* abs);
void alterPerson(Addressbooks* abs);
void clearabs(Addressbooks* abs);

//��¼��������
bool login(AdminiInfo& Admini);