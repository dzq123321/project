#include "common.h"
#include "sys.h"
/*
1、mysql和sqlite都是基于文件类型的关系型数据库

我们是要sqlite数据库，原因在于sqlite是一个体积小，无服务的数据库，适用于嵌入式设计，而无服务的意思是不需要（-u(需要root) -p(密码登录)）
而mysql
2、windows下命令行模式中cd命令无效的原因 cd E:\duzhiqiang\比特51c语言\github   无效
可以加入/d   cd /dE:\duzhiqiang\比特51c语言\github 
原来，要跳转到不同分区的时候，需要添加强制跳转参数 /d 。
但是，如果进入的是当前目录的子目录，则可以不使用 /d 参数。这一点是很容易被大家忽略的。
*/
void Test_DirectionList()
{
	const string &path = "E:\\duzhiqiang\\比特51c语言\\背包\\pack-master";
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