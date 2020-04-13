#include "DataManager.h"



SqliteManager::SqliteManager():m_db(nullptr)
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
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_db));
		exit(1);
	}
	else
	{
		fprintf(stderr, "Open database successfully: \n");
	}
}
void SqliteManager::Close()
{
	if (m_db)
	{
		int rc = sqlite3_close(m_db);
		if (rc != SQLITE_OK)
			fprintf(stderr,"Close database failed: %s\n", sqlite3_errmsg(m_db));
		else
			fprintf(stdout, "Close database successfully\n");
	}
}
void SqliteManager::ExecutedSql(const string &sql)
{
	char *zErrMsg = 0;
	int rc = sqlite3_exec(m_db, sql.c_str(), 0, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		fprintf(stdout, "Table created successfully\n");
	}
}
void SqliteManager::GetResultTable(const string &sql, int &row, int &col, char **&ppRet)
{
	//char **result;
	//int row;
	//int col;
	char *zErrMsg = 0;
	int rc=sqlite3_get_table(m_db, sql.c_str(), &ppRet, &row, &col, &zErrMsg);//sqlite3_free_table
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		fprintf(stdout, "Table created successfully\n");
	}
}
