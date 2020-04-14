#pragma once
#include "common.h"
#include "./sqlite3_lib/sqlite3.h"

//数据库管理模块 1、实现对sql语句的封装 class SqliteManager   2、 实现对数据库文件管理操作的封装
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




class  DataManager
{
public:
	DataManager();
	~DataManager();
public:
	void InitSqlite();
	void InsertDoc(const string &path, const string &doc);
	void GetDocs(const string &path, multiset<string> &docs);
	void DeleteDoc(const string &path, const string &doc);
private:
	SqliteManager m_dbmgr;
};