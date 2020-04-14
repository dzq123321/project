#include "common.h"
#include "sys.h"
#include "DataManager.h"
#include "./sqlite3_lib/sqlite3.h"
#include "ScanManager.h"
#pragma comment (lib,"./sqlite3_lib/sqlite3.lib")
/*
1、mysql和sqlite都是基于文件类型的关系型数据库

我们是要sqlite数据库，原因在于sqlite是一个体积小，无服务的数据库，适用于嵌入式设计，而无服务的意思是不需要（-u(需要root) -p(密码登录)）
而mysql
2、windows下命令行模式中cd命令无效的原因 cd E:\duzhiqiang\比特51c语言\github   无效
可以加入/d   cd /dE:\duzhiqiang\比特51c语言\github 
原来，要跳转到不同分区的时候，需要添加强制跳转参数 /d。
但是，如果进入的是当前目录的子目录，则可以不使用 /d 参数。这一点是很容易被大家忽略的。
*/
//int sqlite3_exec(
//  sqlite3*,                                  /* An open database */
//const char *sql,                           /* SQL to be evaluated */
//int(*callback)(void*, int, char**, char**),  /* Callback function */
//void *,                                    /* 1st argument to callback */
//char **errmsg                              /* Error msg written here */
//);
void Test_Sqlite()
{
	//数据打开
	sqlite3 *db;
	int rc = sqlite3_open("test.db", &db);//打开数据库，返回值为0(SQLITE_OK)，打开成功，否则返回错误码
	if (rc != SQLITE_OK)
		printf("open database falied.\n");
	else
		printf("open database successed.\n");
	//操作数据库
	string sql = "select * from you_tb";
	char **result;
	int row;
	int col;
	char *zErrMsg = 0;
	sqlite3_get_table(db, sql.c_str(), &result, &row, &col, &zErrMsg);
	for (int i = 0; i <= row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			printf("%-5s", *(result + (i*col) + j));
		}
		cout << endl;
	}
}
//void Test_DataManager()
//{
//	SqliteManager sm;
//	sm.Open("sm.db");
//	string sql="create table you_tb(id int, name varchar(20), path varchar(100))";
//	sm.ExecutedSql(sql);
//	 sql = "select * from you_tb";
//	int row = 0;
//	int col = 0;
//	char **result = 0;
//	sm.GetResultTable(sql, row, col, result);
//	for (int i = 0; i <= row; ++i)
//	{
//		for (int j = 0; j < col; ++j)
//		{
//			printf("%-5s", *(result + (i*col) + j));
//		}
//		cout << endl;
//	}
//}
void Test_DataManager()
{
	DataManager dm;
	string path = "c:\\";
	string doc = "stl.paf";
	dm.InsertDoc(path, doc);
}
void Test_ScanManager()
{
	const string path = "E:\\duzhiqiang\\比特51c语言\\github";
	ScanManager sm;
	sm.ScanDirectory(path);
}
int main(int argc, char *argv[])
{
	//Test_Sqlite();
	//Test_DataManager();
	Test_ScanManager();
	return 0;
}
/*
static int callback(void *data, int argc, char **argv, char **azColName)
{
	//argc  列数
	//azColName 每列的属性名(id name path)
	//argv   每列的具体的元素值
	int i;
	fprintf(stderr, "%s: \n", (const char*)data);
	for (int i = 0; i < argc; i++)
	{
		printf("%s=%s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}
void Test_sqlite()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open("test.db", &db);//返回值为SQLITE_OK,表示打开成功,否则返回错误码

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	//sqlite3_exec(sqlite3*, const char *sql,sqlite_callback, void *data,char**errmsg)
	//string sql = "create table you_tb(id int,name varchar(20),path varchar(100))";
	const char* data = "Callback function called";
	//string sql = "insert into you_tb values(1,'abc','c:\\')";
	string sql = "select * from you_tb";
	//rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);//第五个参数不为NULL,则任何错误消息都会写入从sqlite3_malloc()获得的内存中，并通过第5个参数传递回去,所以需要sqlite3_free()
	  rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		fprintf(stdout, "Table created successfully\n");
		fprintf(stdout, "Insert Data successfully\n");
		fprintf(stdout, "Select Data successfully\n");
	}
	sqlite3_close(db);
}

int main(int argc,char *argv[])
{
	Test_sqlite();
	return 0;
}
*/
/*
void Test_DirectionList()
{
	const string &path = "E:\\duzhiqiang\\比特51c语言\\背包\\pack-master";
	vector<string> subdir;
	vector<string> subfile;
	DirectionList(path, subdir, subfile);
}
int main(int argc, char* argv[])
{
	//Test_sqlite();
	Test_DirectionList();
	return 0;
}
*/
//void Test_Sqlite()
//{
//
//}
//int main(int argc, char* argv[])
//{
//	Test_Sqlite();
//	return 0;
//}
