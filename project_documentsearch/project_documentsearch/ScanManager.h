#pragma once
#include "common.h"
#include "DataManager.h"




//���ݿ�ɨ��ģ�飬ͨ�����������ݿ����ģ��DataManager������ʵ�����ݿ��ļ���
//�����ļ����໥��Ӧ
class ScanManager
{
public:
	void ScanDirectory(const string &path);
private:
	DataManager m_db;
};