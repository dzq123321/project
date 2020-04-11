#include "sys.h"
void DirectionList(const string &path, vector<string> &subdir, vector<string> &subfile)
{
	string _path = path;
	_path += "\\*.*";
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