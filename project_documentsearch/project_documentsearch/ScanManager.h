#pragma once
#include "common.h"
#include "DataManager.h"




//���ݿ�ɨ��ģ�飬ͨ�����������ݿ����ģ��DataManager������ʵ�����ݿ��ļ���
//�����ļ����໥��Ӧ
class ScanManager
{
public:
	static ScanManager& CreateInstance(const string &path);
public:
	void StartScan(const string& path);
	void ScanDirectory(const string &path);
private:
	ScanManager();
	//DataManager m_db;
};