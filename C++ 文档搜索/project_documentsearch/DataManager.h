#pragma once
#include "common.h"
#include "./sqlite3_lib/sqlite3.h"

//���ݿ����ģ�� 1��ʵ�ֶ�sql���ķ�װ class SqliteManager   2�� ʵ�ֶ����ݿ��ļ���������ķ�װ
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
//����RAII����
class AutoGetResultTable {
public:
	AutoGetResultTable (SqliteManager *db, const string &sql, int &row, int &col, char **&ppRet);
	~AutoGetResultTable();
public:
	//c++11  ��ֹ���ÿ������캯���͸�ֵ���������
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