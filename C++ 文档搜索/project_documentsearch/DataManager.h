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

/*
//利用RAII机制
class AutoGetResultTable {
public:
	AutoGetResultTable (SqliteManager *db, const string &sql, int &row, int &col, char **&ppRet);
	~AutoGetResultTable();
public:
	//c++11  禁止调用拷贝构造函数和赋值运算符重载
	AutoGetResultTable(const AutoGetResultTable &) = delete;
	AutoGetResultTable& operator=(const AutoGetResultTable&) = delete;
protected:
	AutoGetResultTable(const AutoGetResultTable &);
	AutoGetResultTable& operator=(const AutoGetResultTable&);
private:
	SqliteManager *m_db;
	SqliteManager **m_ppRet;
};
*/



class  DataManager
{
public:
	~DataManager();
public:
	static DataManager& GetInstance();
public:
	void InitSqlite();
	void InsertDoc(const string &path, const string &doc);
	void GetDocs(const string &path, multiset<string> &docs);
	void DeleteDoc(const string &path, const string &doc);
	void Search(const string &key, vector<pair<string, string>> &doc_path);
private:
	DataManager();
private:
	SqliteManager m_dbmgr;
};