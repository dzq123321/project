#include "DataManager.h"
#include "sys.h"


SqliteManager::SqliteManager() :m_db(nullptr)
{}
SqliteManager::~SqliteManager()
{
	Close();
}
void SqliteManager::Open(const string &path)
{
	char *zErrMsg = 0;
	int rc = sqlite3_open(path.c_str(), &m_db);
	if (rc)
	{
		//fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_db));
		ERROR_LOG("Can't open database: %s", sqlite3_errmsg(m_db));
		exit(1);
	}
	else
	{
		//fprintf(stderr, "Open database successfully: \n");
		TRACE_LOG("Open database successfully")
	}
}
void SqliteManager::Close()
{
	if (m_db)
	{
		int rc = sqlite3_close(m_db);
		if (rc != SQLITE_OK)
		{
			//fprintf(stderr,"Close database failed: %s\n", sqlite3_errmsg(m_db));
			ERROR_LOG("Close database failed: %s", sqlite3_errmsg(m_db));
		}
		else
			//fprintf(stdout, "Close database successfully\n");
			TRACE_LOG("Close database successfully");
	}
}
void SqliteManager::ExecutedSql(const string &sql)
{
	char *zErrMsg = 0;
	int rc = sqlite3_exec(m_db, sql.c_str(), 0, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		ERROR_LOG("SQL error: %s", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		//fprintf(stdout, "Table created successfully\n");
		TRACE_LOG("SQL executed successfully");
	}
}
void SqliteManager::GetResultTable(const string &sql, int &row, int &col, char **&ppRet)
{
	//char **result;
	//int row;
	//int col;
	char *zErrMsg = 0;
	int rc = sqlite3_get_table(m_db, sql.c_str(), &ppRet, &row, &col, &zErrMsg);//sqlite3_free_table
	if (rc != SQLITE_OK)
	{
		//fprintf(stderr, "Table created error: %s", zErrMsg);
		ERROR_LOG("Table created error: %s", zErrMsg)
			sqlite3_free(zErrMsg);
	}
	else
	{
		//fprintf(stdout, "Table created successfully\n");
		TRACE_LOG("Table created successfully");
	}
}


DataManager::DataManager()
{
	m_dbmgr.Open(DOC_DB);//创建数据库
	InitSqlite();//创建表
}
DataManager::~DataManager()
{}
void DataManager::InitSqlite()
{
	//string sql=" create table if not exists DOC_TABLE(id integer primary key autoincrement, doc_name text, doc_path text)"
	//这样也行，但是就不能动态的改变我们想创建表的名字，可以通过sprintf
	char sql[SQL_BUFFER_SIZE] = { 0 };
	sprintf(sql, "create table if not exists %s(id integer primary key autoincrement, doc_name text, doc_path text)", DOC_TABLE);
	//sprintf 将sql之后的字符串自规定的格式打印到sql中
	m_dbmgr.ExecutedSql(sql);
}
void DataManager::InsertDoc(const string &path, const string &doc)
{
	char sql[SQL_BUFFER_SIZE] = { 0 };
	sprintf(sql, "insert into %s values (null,'%s','%s')", DOC_TABLE,doc.c_str(),path.c_str());
	//sprintf 将sql之后的字符串自规定的格式打印到sql中
	m_dbmgr.ExecutedSql(sql);
}
void DataManager::GetDocs(const string &path, multiset<string> &docs)
{
	char sql[SQL_BUFFER_SIZE] = { 0 };
	sprintf(sql, "select doc_name from %s where doc_path='%s'", DOC_TABLE,path.c_str());
	//sprintf 将sql之后的字符串自规定的格式打印到sql中
	int row = 0, col = 0;
	char **ppRet = 0;
	m_dbmgr.GetResultTable(sql,row,col,ppRet);
	for (int i = 1; i <= row; ++i)
		docs.insert(ppRet[i]);
	//释放结果表
	sqlite3_free_table(ppRet);
}
void DataManager::DeleteDoc(const string &path, const string &doc)
{
	char sql[SQL_BUFFER_SIZE] = { 0 };
	sprintf(sql, "delete from %s where doc_name='%s' and doc_path='%s'", DOC_TABLE, doc.c_str(), path.c_str());
	m_dbmgr.ExecutedSql(sql);
}