#include "common.h"
#include "sys.h"
/*
1��mysql��sqlite���ǻ����ļ����͵Ĺ�ϵ�����ݿ�

������Ҫsqlite���ݿ⣬ԭ������sqlite��һ�����С���޷�������ݿ⣬������Ƕ��ʽ��ƣ����޷������˼�ǲ���Ҫ��-u(��Ҫroot) -p(�����¼)��
��mysql
2��windows��������ģʽ��cd������Ч��ԭ�� cd E:\duzhiqiang\����51c����\github   ��Ч
���Լ���/d   cd /dE:\duzhiqiang\����51c����\github 
ԭ����Ҫ��ת����ͬ������ʱ����Ҫ���ǿ����ת���� /d ��
���ǣ����������ǵ�ǰĿ¼����Ŀ¼������Բ�ʹ�� /d ��������һ���Ǻ����ױ���Һ��Եġ�
*/
void Test_DirectionList()
{
	const string &path = "E:\\duzhiqiang\\����51c����\\����\\pack-master";
	vector<string> subdir;
	vector<string> subfile;
	DirectionList(path, subdir, subfile);
}
int main(int argc, char* argv[])
{
	Test_DirectionList();
	return 0;
}

//void Test_Sqlite()
//{
//
//}
//int main(int argc, char* argv[])
//{
//	Test_Sqlite();
//	return 0;
//}