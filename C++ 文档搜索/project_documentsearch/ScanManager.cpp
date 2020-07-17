#include "ScanManager.h"
#include "sys.h"

ScanManager::ScanManager()
{}
void ScanManager::StartScan(const string& path)
{
	while (1)
	{
		this_thread::sleep_for(chrono::seconds(3));
		ScanDirectory(path);
	}
}

ScanManager& ScanManager::CreateInstance(const string &path)
{
	static ScanManager inst;
	thread scan_thread(&StartScan, &inst, path);
	scan_thread.detach();
	return inst;
}

void ScanManager::ScanDirectory(const string &path)
{
		//ɨ�豾���ļ�
	vector<string> local_files;  //�����ļ�
	vector<string> local_dirs; //����Ŀ¼
	DirectionList(path,  local_dirs, local_files);
	set<string> local_set;
	local_set.insert(local_files.begin(), local_files.end());
	local_set.insert(local_dirs.begin(), local_dirs.end());
	//ɨ�����ݿ��ļ�ϵͳ
	multiset<string> db_set;
	DataManager &m_db = DataManager::GetInstance();
	m_db.GetDocs(path, db_set);
	//�Աȱ����ļ������ݿ��ļ�
	auto local_it = local_set.begin();
	auto db_it = db_set.begin();
	while (local_it != local_set.end() && db_it != db_set.end())
	{
		if (*local_it < *db_it)
		{
			//�����ļ����ڣ����ݿ��ļ������ڣ������ݿ�����ļ�
			m_db.InsertDoc(path, *local_it);
			local_it++;
		}
		else if (*local_it > *db_it)
		{
			//�����ļ������ڣ����ݿ��ļ����ڣ������ݿ�ɾ���ļ�
			m_db.DeleteDoc(path, *db_it);
			db_it++;
		}
		else
		{
			//�����ļ����ڣ����ݿ��ļ����ڣ�
			local_it++;
			db_it++;
		}
	}
	while (local_it != local_set.end())
	{
		// �����ļ����ڣ����ݿ��ļ������ڣ������ݿ�����ļ�
		m_db.InsertDoc(path, *local_it);
		local_it++;
	}
	while (db_it != db_set.end())
	{
		//�����ļ������ڣ����ݿ��ļ����ڣ������ݿ�ɾ���ļ�
		m_db.DeleteDoc(path, *db_it);
		db_it++;
	}
	//�ݹ������Ŀ¼
	//
	for (const auto &dir : local_dirs)
	{
		string dir_path = path;
		dir_path += "\\";
		dir_path += dir;
		ScanDirectory(dir_path);
	}

}