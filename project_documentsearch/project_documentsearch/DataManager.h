#pragma once
#include "common.h"
#include "./sqlite3_lib/sqlite3.h"

//数据库管理模块 1、实现对sql语句的封装 class SqliteManager
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
