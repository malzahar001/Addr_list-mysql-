#include "struct.h"
#include "defData.h"
using namespace std;

bool connect_db(MYSQL& mysql);
bool fetch_Admini_info(AdminiInfo& Admini);
//bool fetch_level_info(_levelinfo& level, int level_id);

/****************************************************
 *���ܣ���¼���ݿ�
 * ���룺�̶����˺�����˿�
 ****************************************************/
bool connect_db(MYSQL& mysql) {
	//1.��ʼ�����ݿ���
	mysql_init(&mysql);

	//2.�����ַ�����
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	//3.�������ݿⲢ�ж��Ƿ����ӳɹ�
	//mysql_real_connect����ֵΪNULL��������ʧ��
	if (mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_USER_PASSWD, DB_NAME, DB_PORT, NULL, 0) == NULL)
	{
		cout << "����ʧ�ܣ�����ԭ��" << mysql_error(&mysql) << endl;
		return false;
	}

	return true;
}
/****************************************************
 *���ܣ�ͨ���û����������ȡ�û���Ϣ
 *���룺
 *     user - �û���Ϣ�ṹ��
 * ����ֵ��
 *       ��ȡ�ɹ�����true��ʧ��false
 ****************************************************/
 //ͨ���û����������ȡ�û���Ϣ����ȡ�ɹ�����true��ʧ��false
bool fetch_Admini_info(AdminiInfo& Admini) {
	MYSQL mysql;     //���ݿ����
	char sql[256];   //��Ų�ѯ���
	MYSQL_RES* res;  //�洢��ѯ���н��
	MYSQL_ROW row;   //��Ų�ѯ�����ÿһ��
	bool ret = false;//��ǲ�ѯ�Ƿ�ɹ�

	//1.���ӵ����ݿ⣬ʧ�ܴ����޷����ӷ�����
	if (connect_db(mysql) == false)
		return false;

	//2.�����û����������ȡ�û���Ϣ(id,level_id)
	//snprintf��sql��ֵ�ַ�����䣬�ں��˺�������
	//user.username��Ҫ��c_str()���ַ���stringת��Ϊchar*��
	snprintf(sql, 256, "select * from Admini_list where AdminiName='%s' and password='%s';", Admini.AdminiName.c_str(), Admini.password.c_str());

	//ִ��sql���Ĳ�ѯ���ɹ�����0
	ret = mysql_query(&mysql, sql);
	if (ret) {
		cout << "���ݿ��ѯ���" << sql << " ����ԭ��" << mysql_error(&mysql) << endl;
		mysql_close(&mysql);
		return false;
	}
	//3.��ȡ��ѯ���
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	//���û�в��ҵ���¼���͹ر����ݲ�����false
	if (row == NULL) {
		mysql_free_result(res);
		mysql_close(&mysql);
		return false;
	}
	Admini.id = atoi(row[0]);  //�ַ���ת��������
	//��ӡ�û�ID�͹ؿ����

	//4.���ؽ�����ͷŽ�����͹ر����ݿ�
	mysql_free_result(res);
	mysql_close(&mysql);
	return true;
}

/****************************************************
 *���ܣ������������Ϣִ��mysql���ԣ��Ӷ��ٿ�ͨѶ¼
 *���룺
 *     ��ǰ����Ա����
 * ����ֵ��
 *       ��ȡ�ɹ�����true��ʧ��false
 ****************************************************/
//1.�����ϵ��
void add_Person(Person *temp) {
	MYSQL mysql;     //���ݿ����
	char sql[256];   //��Ų�ѯ���
	MYSQL_RES* res;  //�洢��ѯ���н��
	MYSQL_ROW row;   //��Ų�ѯ�����ÿһ��
	bool ret = false;//��ǲ�ѯ�Ƿ�ɹ�

	//1.���ӵ����ݿ⣬ʧ�ܴ����޷����ӷ�����
	if (connect_db(mysql) == false) {
		cout << "���ݿ�����ʧ��" << endl;
		return;
	}
	//2.snprintf��sql��ֵ�ַ������,��Ҫ��c_str()��stringת��Ϊchar*��
	snprintf(sql, 256, "insert into person_list(name,sex,age,phone,address) values('%s','%d','%d','%s','%s');", 
		temp->m_Name.c_str(), temp->m_Sex,temp->m_Age,temp->m_Phone.c_str(),temp->m_Addr.c_str());
	//ִ��sql���Ĳ�ѯ���ɹ�����0
	if (mysql_query(&mysql, sql)) {  //����ʧ�ܣ��򷵻�1���ɹ�����0
		cout << "��������ʧ��" << mysql_error(&mysql) << endl;
		return;
	}
	else {
		cout << "�������ݳɹ�" << endl;
	}
	//3.�ͷŽ�����͹ر����ݿ�
	mysql_close(&mysql);
	return;
}
//2.��ʾ������ϵ��
void show_Person() {
	MYSQL mysql;     //���ݿ����
	char sql[256];   //��Ų�ѯ���
	MYSQL_RES* res;  //�洢��ѯ���н��
	MYSQL_ROW row;   //��Ų�ѯ�����ÿһ��
	bool ret = false;//��ǲ�ѯ�Ƿ�ɹ�

	//1.���ӵ����ݿ⣬ʧ�ܴ����޷����ӷ�����
	if (connect_db(mysql) == false) {
		cout << "���ݿ�����ʧ��" << endl;
		return;
	}
	//2.��ѯ����
	const char* sql01 = "select * from person_list";
	if (mysql_query(&mysql, sql01)) {
		cout << "δ�鵽��¼" << mysql_error << endl;
		return;
	}
	else {
		cout << "�鵽��¼" << endl;
	}
	res = mysql_store_result(&mysql);
	cout << "name\tsex\tage\tphone\taddress" << endl; //�����¼��ģʽ
	while (row = mysql_fetch_row(res)) { //rowѭ����ȡ������¼��ÿһ���У����ϵ��£�
		cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << endl; //������е�ÿһ��
	}
	//4.�ͷŽ�����͹ر����ݿ�
	mysql_free_result(res);
	mysql_close(&mysql);
}
//3.������ϵ��
void find_Person(Person* temp) {
	MYSQL mysql;     //���ݿ����
	char sql[256];   //��Ų�ѯ���
	MYSQL_RES* res;  //�洢��ѯ���н��
	MYSQL_ROW row;   //��Ų�ѯ�����ÿһ��
	bool ret = false;//��ǲ�ѯ�Ƿ�ɹ�

	//1.���ӵ����ݿ⣬ʧ�ܴ����޷����ӷ�����
	if (connect_db(mysql) == false) {
		cout << "���ݿ�����ʧ��" << endl;
		return;
	}

	//2.snprintf��sql��ֵ�ַ������,��Ҫ��c_str()��stringת��Ϊchar*��
	snprintf(sql, 256, "select * from person_list where name='%s';",
		temp->m_Name.c_str());
	//��ȡ��ѯ�����
	if (mysql_query(&mysql,sql)) {
		cout << "δ��ȡ�����ݣ�" << mysql_error << endl;
		return;
	}
	else {
		cout << "��ȡ������" << endl;
	}
	//��ȡ�������
	res = mysql_store_result(&mysql);
	cout << "name\tsex\tage\tphone\taddress" << endl; //�����¼��ģʽ
	while (row = mysql_fetch_row(res)) { //rowѭ����ȡ������¼��ÿһ���У����ϵ��£�
		cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << endl; //������е�ÿһ��
	}
	//3.�ͷŽ�����͹ر����ݿ�
	mysql_free_result(res);
	mysql_close(&mysql);
	return;
}
//4.�����ϵ�˵Ĵ���
bool check_Person(Person* temp) {
	MYSQL mysql;     //���ݿ����
	char sql[256];   //��Ų�ѯ���
	MYSQL_RES* res;  //�洢��ѯ���н��
	MYSQL_ROW row;   //��Ų�ѯ�����ÿһ��
	bool ret = false;//��ǲ�ѯ�Ƿ�ɹ�

	//1.���ӵ����ݿ⣬ʧ�ܴ����޷����ӷ�����
	if (connect_db(mysql) == false) {
		cout << "���ݿ�����ʧ��" << endl;
		return false;
	}

	//2.snprintf��sql��ֵ�ַ������,��Ҫ��c_str()��stringת��Ϊchar*��
	snprintf(sql, 256, "select * from person_list where name='%s';",
		temp->m_Name.c_str());
	//��ȡ��ѯ�����
	if (mysql_query(&mysql,sql)) {
		cout << "δ��ȡ�����ݣ�" << mysql_error << endl;
		return false;
	}
	else {
		cout << "��ȡ������" << endl;
	}
	//3.�ͷŽ�����͹ر����ݿ�
	mysql_close(&mysql);
	return true;
}
//5.ɾ����ϵ��
void delete_Person(Person* temp) {
	MYSQL mysql;     //���ݿ����
	char sql[256];   //��Ų�ѯ���
	MYSQL_RES* res;  //�洢��ѯ���н��
	MYSQL_ROW row;   //��Ų�ѯ�����ÿһ��
	bool ret = false;//��ǲ�ѯ�Ƿ�ɹ�

	//1.���ӵ����ݿ⣬ʧ�ܴ����޷����ӷ�����
	if (connect_db(mysql) == false) {
		cout << "���ݿ�����ʧ��" << endl;
		return;
	}
	//2.snprintf��sql��ֵ�ַ������,��Ҫ��c_str()��stringת��Ϊchar*��
	snprintf(sql, 256, "delete from person_list where name='%s';",temp->m_Name.c_str());

	//ִ��sql���Ĳ�ѯ���ɹ�����0
	if (mysql_query(&mysql, sql)) {  //����ʧ�ܣ��򷵻�1���ɹ�����0
		cout << "ɾ������ʧ��" << mysql_error(&mysql) << endl;
		return;
	}
	else {
		cout << "ɾ�����ݳɹ�" << endl;
	}
	//3.�ͷŽ�����͹ر����ݿ�
	mysql_close(&mysql);
	return;
}
//6.�����ϵ��
void clear_Person() {
	MYSQL mysql;     //���ݿ����
	char sql[256];   //��Ų�ѯ���
	MYSQL_RES* res;  //�洢��ѯ���н��
	MYSQL_ROW row;   //��Ų�ѯ�����ÿһ��
	bool ret = false;//��ǲ�ѯ�Ƿ�ɹ�

	//1.���ӵ����ݿ⣬ʧ�ܴ����޷����ӷ�����
	if (connect_db(mysql) == false) {
		cout << "�������ݿ�ʧ��" << endl;
		return;
	}

	//2.����sql��䲢ִ��
	const char* sql01 = "delete from person_list";
	if (mysql_query(&mysql, sql01)) {
		cout << "���ʧ��" << mysql_error << endl;
		return;
	}
	else {
		cout << "����ɹ�" << endl;
	}
	//3.�ͷŽ�����͹ر����ݿ�
	mysql_close(&mysql);
	return;
}