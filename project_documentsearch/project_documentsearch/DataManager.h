#pragma once
#include "common.h"
#include "./sqlite3_lib/sqlite3.h"

//���ݿ����ģ�� 1��ʵ�ֶ�sql���ķ�װ class SqliteManager
class SqliteManager
{
public:
	SqliteManager();
	~SqliteManager();
public:
	void Open(const string &path);
	void Close();
	void ExecutedSql(const string &sql);
	void GetResultTable(const string &sql, int &row, int &col, char **&ppRet);
private:
	sqlite3 *m_db;
};
