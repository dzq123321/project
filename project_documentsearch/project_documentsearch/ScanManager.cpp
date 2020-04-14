#include "ScanManager.h"
#include "sys.h"


void ScanManager::ScanDirectory(const string &path)
{
		//扫描本地文件
	vector<string> local_files;  //本地文件
	vector<string> local_dirs; //本地目录
	DirectionList(path, local_files, local_dirs);
	set<string> local_set;
	local_set.insert(local_files.begin(), local_files.end());
	local_set.insert(local_dirs.begin(), local_dirs.end());
	//扫描数据库文件系统
	multiset<string> db_set;
	m_db.GetDocs(path, db_set);
	//对比本地文件和数据库文件
	auto local_it = local_set.begin();
	auto db_it = db_set.begin();
	while (local_it != local_set.end() && db_it != db_set.end())
	{
		if (*local_it < *db_it)
		{
			//本地文件存在，数据库文件不存在，则数据库插入文件
			m_db.InsertDoc(path, *local_it);
			local_it++;
		}
		else if (*local_it > *db_it)
		{
			//本地文件不存在，数据库文件存在，则数据库删除文件
			m_db.DeleteDoc(path, *local_it);
			db_it++;
		}
		else
		{
			//本地文件存在，数据库文件存在，
			local_it++;
			db_it++;
		}
	}
	while (local_it != local_set.end())
	{
		// 本地文件存在，数据库文件不存在，则数据库插入文件
		m_db.InsertDoc(path, *local_it);
		local_it++;
	}
	while (db_it != db_set.end())
	{
		//本地文件不存在，数据库文件存在，则数据库删除文件
		m_db.DeleteDoc(path, *db_it);
		db_it++;
	}
	//递归遍历子目录
	//
}