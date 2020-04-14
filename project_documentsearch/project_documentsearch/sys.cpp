#include "sys.h"
/*
long _findfirst( char *filespec, struct _finddata_t *fileinfo );
返回值：如果查找成功的话，将返回一个long型的唯一的查找用的句柄（就是一个唯一编号）。这个句柄将在_findnext函数中被使用。若失败，则返回-1。
filespec：标明文件的字符串，可支持通配符。比如：*.c，则表示当前文件夹下的所有后缀为C的文件。 
fileinfo ：这里就是用来存放文件信息的结构体的指针。这个结构体必须在调用此函数前声明，不过不用初始化，只要分配了内存空间就可以了。
函数成功后，函数会把找到的文件的信息放入这个结构体中。
int _findnext( long handle, struct _finddata_t *fileinfo ); 
返回值： 若成功返回0，否则返回-1。 参数： handle：即由_findfirst函数返回回来的句柄。
fileinfo：文件信息结构体的指针。找到文件后，函数将该文件信息放入此结构体中。
*/
void DirectionList(const string &path, vector<string> &subdir, vector<string> &subfile)
{
	string _path = path;
	_path += "\\*.*";    //必须是_path,表示当前目录下的所有文件
	_finddata_t file;
	//_findfirst,搜索path路径下的第一个参数
	long handle = _findfirst(_path.c_str(), &file);
	if (handle == -1)
	{
		perror("_findfirst");
		return;
	}
	do
	{    //跳过隐藏文件
		if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
			continue;
		//递归打印目录
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