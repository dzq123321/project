#pragma once
#include "common.h"
#include "DataManager.h"




//数据库扫描模块，通过（操作数据库管理模块DataManager），来实现数据库文件和
//本地文件的相互对应
class ScanManager
{
public:
	void ScanDirectory(const string &path);
private:
	DataManager m_db;
};