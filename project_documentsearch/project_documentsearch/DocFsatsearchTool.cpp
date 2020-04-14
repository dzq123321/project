#include "common.h"
#include "sys.h"
#include "DataManager.h"
#include "./sqlite3_lib/sqlite3.h"
#include "ScanManager.h"
#pragma comment (lib,"./sqlite3_lib/sqlite3.lib")
/*
1��mysql��sqlite���ǻ����ļ����͵Ĺ�ϵ�����ݿ�

������Ҫsqlite���ݿ⣬ԭ������sqlite��һ�����С���޷�������ݿ⣬������Ƕ��ʽ��ƣ����޷������˼�ǲ���Ҫ��-u(��Ҫroot) -p(�����¼)��
��mysql
2��windows��������ģʽ��cd������Ч��ԭ�� cd E:\duzhiqiang\����51c����\github   ��Ч
���Լ���/d   cd /dE:\duzhiqiang\����51c����\github 
ԭ����Ҫ��ת����ͬ������ʱ����Ҫ���ǿ����ת���� /d��
���ǣ����������ǵ�ǰĿ¼����Ŀ¼������Բ�ʹ�� /d ��������һ���Ǻ����ױ���Һ��Եġ�
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
	//���ݴ�
	sqlite3 *db;
	int rc = sqlite3_open("test.db", &db);//�����ݿ⣬����ֵΪ0(SQLITE_OK)���򿪳ɹ������򷵻ش�����
	if (rc != SQLITE_OK)
		printf("open database falied.\n");
	else
		printf("open database successed.\n");
	//�������ݿ�
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
	const string path = "E:\\duzhiqiang\\����51c����\\github";
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
	//argc  ����
	//azColName ÿ�е�������(id name path)
	//argv   ÿ�еľ����Ԫ��ֵ
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

	rc = sqlite3_open("test.db", &db);//����ֵΪSQLITE_OK,��ʾ�򿪳ɹ�,���򷵻ش�����

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
	//rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);//�����������ΪNULL,���κδ�����Ϣ����д���sqlite3_malloc()��õ��ڴ��У���ͨ����5���������ݻ�ȥ,������Ҫsqlite3_free()
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
	const string &path = "E:\\duzhiqiang\\����51c����\\����\\pack-master";
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
