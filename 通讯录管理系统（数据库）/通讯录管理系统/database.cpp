#include "struct.h"
#include "defData.h"
using namespace std;

bool connect_db(MYSQL& mysql);
bool fetch_Admini_info(AdminiInfo& Admini);
//bool fetch_level_info(_levelinfo& level, int level_id);

/****************************************************
 *功能：登录数据库
 * 输入：固定的账号密码端口
 ****************************************************/
bool connect_db(MYSQL& mysql) {
	//1.初始化数据库句柄
	mysql_init(&mysql);

	//2.设置字符编码
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	//3.连接数据库并判断是否连接成功
	//mysql_real_connect返回值为NULL代表连接失败
	if (mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_USER_PASSWD, DB_NAME, DB_PORT, NULL, 0) == NULL)
	{
		cout << "连接失败！错误原因：" << mysql_error(&mysql) << endl;
		return false;
	}

	return true;
}
/****************************************************
 *功能：通过用户名和密码获取用户信息
 *输入：
 *     user - 用户信息结构体
 * 返回值：
 *       获取成功返回true，失败false
 ****************************************************/
 //通过用户名和密码获取用户信息，获取成功返回true，失败false
bool fetch_Admini_info(AdminiInfo& Admini) {
	MYSQL mysql;     //数据库对象
	char sql[256];   //存放查询语句
	MYSQL_RES* res;  //存储查询所有结果
	MYSQL_ROW row;   //存放查询结果的每一项
	bool ret = false;//标记查询是否成功

	//1.连接到数据库，失败代表无法连接服务器
	if (connect_db(mysql) == false)
		return false;

	//2.根据用户名和密码获取用户信息(id,level_id)
	//snprintf给sql赋值字符串语句，内含账号与密码
	//user.username需要用c_str()由字符串string转换为char*型
	snprintf(sql, 256, "select * from Admini_list where AdminiName='%s' and password='%s';", Admini.AdminiName.c_str(), Admini.password.c_str());

	//执行sql语句的查询，成功返回0
	ret = mysql_query(&mysql, sql);
	if (ret) {
		cout << "数据库查询输错" << sql << " 错误原因：" << mysql_error(&mysql) << endl;
		mysql_close(&mysql);
		return false;
	}
	//3.获取查询结果
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	//如果没有查找到记录，就关闭数据并返回false
	if (row == NULL) {
		mysql_free_result(res);
		mysql_close(&mysql);
		return false;
	}
	Admini.id = atoi(row[0]);  //字符串转换成整型
	//打印用户ID和关卡序号

	//4.返回结果，释放结果集和关闭数据库
	mysql_free_result(res);
	mysql_close(&mysql);
	return true;
}

/****************************************************
 *功能：根据输入的信息执行mysql语言，从而操控通讯录
 *输入：
 *     当前的人员数据
 * 返回值：
 *       获取成功返回true，失败false
 ****************************************************/
//1.添加联系人
void add_Person(Person *temp) {
	MYSQL mysql;     //数据库对象
	char sql[256];   //存放查询语句
	MYSQL_RES* res;  //存储查询所有结果
	MYSQL_ROW row;   //存放查询结果的每一项
	bool ret = false;//标记查询是否成功

	//1.连接到数据库，失败代表无法连接服务器
	if (connect_db(mysql) == false) {
		cout << "数据库连接失败" << endl;
		return;
	}
	//2.snprintf给sql赋值字符串语句,需要用c_str()将string转换为char*型
	snprintf(sql, 256, "insert into person_list(name,sex,age,phone,address) values('%s','%d','%d','%s','%s');", 
		temp->m_Name.c_str(), temp->m_Sex,temp->m_Age,temp->m_Phone.c_str(),temp->m_Addr.c_str());
	//执行sql语句的查询，成功返回0
	if (mysql_query(&mysql, sql)) {  //插入失败，则返回1，成功返回0
		cout << "插入数据失败" << mysql_error(&mysql) << endl;
		return;
	}
	else {
		cout << "插入数据成功" << endl;
	}
	//3.释放结果集和关闭数据库
	mysql_close(&mysql);
	return;
}
//2.显示所有联系人
void show_Person() {
	MYSQL mysql;     //数据库对象
	char sql[256];   //存放查询语句
	MYSQL_RES* res;  //存储查询所有结果
	MYSQL_ROW row;   //存放查询结果的每一项
	bool ret = false;//标记查询是否成功

	//1.连接到数据库，失败代表无法连接服务器
	if (connect_db(mysql) == false) {
		cout << "数据库连接失败" << endl;
		return;
	}
	//2.查询数据
	const char* sql01 = "select * from person_list";
	if (mysql_query(&mysql, sql01)) {
		cout << "未查到记录" << mysql_error << endl;
		return;
	}
	else {
		cout << "查到记录" << endl;
	}
	res = mysql_store_result(&mysql);
	cout << "name\tsex\tage\tphone\taddress" << endl; //输出记录的模式
	while (row = mysql_fetch_row(res)) { //row循环获取整个记录的每一个行（从上到下）
		cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << endl; //输出改行的每一项
	}
	//4.释放结果集和关闭数据库
	mysql_free_result(res);
	mysql_close(&mysql);
}
//3.查找联系人
void find_Person(Person* temp) {
	MYSQL mysql;     //数据库对象
	char sql[256];   //存放查询语句
	MYSQL_RES* res;  //存储查询所有结果
	MYSQL_ROW row;   //存放查询结果的每一项
	bool ret = false;//标记查询是否成功

	//1.连接到数据库，失败代表无法连接服务器
	if (connect_db(mysql) == false) {
		cout << "数据库连接失败" << endl;
		return;
	}

	//2.snprintf给sql赋值字符串语句,需要用c_str()将string转换为char*型
	snprintf(sql, 256, "select * from person_list where name='%s';",
		temp->m_Name.c_str());
	//获取查询结果集
	if (mysql_query(&mysql,sql)) {
		cout << "未获取到数据：" << mysql_error << endl;
		return;
	}
	else {
		cout << "获取到数据" << endl;
	}
	//获取结果集合
	res = mysql_store_result(&mysql);
	cout << "name\tsex\tage\tphone\taddress" << endl; //输出记录的模式
	while (row = mysql_fetch_row(res)) { //row循环获取整个记录的每一个行（从上到下）
		cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << endl; //输出改行的每一项
	}
	//3.释放结果集和关闭数据库
	mysql_free_result(res);
	mysql_close(&mysql);
	return;
}
//4.检测联系人的存在
bool check_Person(Person* temp) {
	MYSQL mysql;     //数据库对象
	char sql[256];   //存放查询语句
	MYSQL_RES* res;  //存储查询所有结果
	MYSQL_ROW row;   //存放查询结果的每一项
	bool ret = false;//标记查询是否成功

	//1.连接到数据库，失败代表无法连接服务器
	if (connect_db(mysql) == false) {
		cout << "数据库连接失败" << endl;
		return false;
	}

	//2.snprintf给sql赋值字符串语句,需要用c_str()将string转换为char*型
	snprintf(sql, 256, "select * from person_list where name='%s';",
		temp->m_Name.c_str());
	//获取查询结果集
	if (mysql_query(&mysql,sql)) {
		cout << "未获取到数据：" << mysql_error << endl;
		return false;
	}
	else {
		cout << "获取到数据" << endl;
	}
	//3.释放结果集和关闭数据库
	mysql_close(&mysql);
	return true;
}
//5.删除联系人
void delete_Person(Person* temp) {
	MYSQL mysql;     //数据库对象
	char sql[256];   //存放查询语句
	MYSQL_RES* res;  //存储查询所有结果
	MYSQL_ROW row;   //存放查询结果的每一项
	bool ret = false;//标记查询是否成功

	//1.连接到数据库，失败代表无法连接服务器
	if (connect_db(mysql) == false) {
		cout << "数据库连接失败" << endl;
		return;
	}
	//2.snprintf给sql赋值字符串语句,需要用c_str()将string转换为char*型
	snprintf(sql, 256, "delete from person_list where name='%s';",temp->m_Name.c_str());

	//执行sql语句的查询，成功返回0
	if (mysql_query(&mysql, sql)) {  //插入失败，则返回1，成功返回0
		cout << "删除数据失败" << mysql_error(&mysql) << endl;
		return;
	}
	else {
		cout << "删除数据成功" << endl;
	}
	//3.释放结果集和关闭数据库
	mysql_close(&mysql);
	return;
}
//6.清空联系人
void clear_Person() {
	MYSQL mysql;     //数据库对象
	char sql[256];   //存放查询语句
	MYSQL_RES* res;  //存储查询所有结果
	MYSQL_ROW row;   //存放查询结果的每一项
	bool ret = false;//标记查询是否成功

	//1.连接到数据库，失败代表无法连接服务器
	if (connect_db(mysql) == false) {
		cout << "连接数据库失败" << endl;
		return;
	}

	//2.定义sql语句并执行
	const char* sql01 = "delete from person_list";
	if (mysql_query(&mysql, sql01)) {
		cout << "清除失败" << mysql_error << endl;
		return;
	}
	else {
		cout << "清除成功" << endl;
	}
	//3.释放结果集和关闭数据库
	mysql_close(&mysql);
	return;
}