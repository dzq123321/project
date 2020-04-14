#include "sys.h"
/*
long _findfirst( char *filespec, struct _finddata_t *fileinfo );
����ֵ��������ҳɹ��Ļ���������һ��long�͵�Ψһ�Ĳ����õľ��������һ��Ψһ��ţ�������������_findnext�����б�ʹ�á���ʧ�ܣ��򷵻�-1��
filespec�������ļ����ַ�������֧��ͨ��������磺*.c�����ʾ��ǰ�ļ����µ����к�׺ΪC���ļ��� 
fileinfo �����������������ļ���Ϣ�Ľṹ���ָ�롣����ṹ������ڵ��ô˺���ǰ�������������ó�ʼ����ֻҪ�������ڴ�ռ�Ϳ����ˡ�
�����ɹ��󣬺�������ҵ����ļ�����Ϣ��������ṹ���С�
int _findnext( long handle, struct _finddata_t *fileinfo ); 
����ֵ�� ���ɹ�����0�����򷵻�-1�� ������ handle������_findfirst�������ػ����ľ����
fileinfo���ļ���Ϣ�ṹ���ָ�롣�ҵ��ļ��󣬺��������ļ���Ϣ����˽ṹ���С�
*/
void DirectionList(const string &path, vector<string> &subdir, vector<string> &subfile)
{
	string _path = path;
	_path += "\\*.*";    //������_path,��ʾ��ǰĿ¼�µ������ļ�
	_finddata_t file;
	//_findfirst,����path·���µĵ�һ������
	long handle = _findfirst(_path.c_str(), &file);
	if (handle == -1)
	{
		perror("_findfirst");
		return;
	}
	do
	{    //���������ļ�
		if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
			continue;
		//�ݹ��ӡĿ¼
		if (file.attrib&_A_SUBDIR)
		{
			//cout << "dir: "<<file.name << endl;
			//string tmp_path = path;
			//tmp_path += "\\";
			//tmp_path += file.name;
			//DirectionList(tmp_path);
			subdir.push_back(file.name);
		}
		else
			//cout << file.name << endl;
		subfile.push_back(file.name);
	} while (_findnext(handle, &file) == 0);
	_findclose(handle);
}