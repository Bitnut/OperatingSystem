#pragma once
#include<iostream>
#include<ctime>
#include"userDashboard.h"
#include<string>
#include<sstream>
#include<cstring>
#include"command.h"
using namespace std;
// command instance for input
cmd cmd_in;
// functionList for input route
HANDLE functionList[] =
{
	{ "chmod", do_Chmod },
	{ "chown", do_Chown },
	{ "mv", do_Mv },
	{ "print", do_Type },
	{ "passwd", do_Passwd },
	{ "login", do_Login },
	{ "logout", do_Logout },
	{ "mkfile", do_Create },
	{ "rm", do_Delete },
	{ "open", do_Open },
	{ "close", do_Close },
	{ "write", do_Write },
	{ "read", do_Read },
	{ "help", do_Help },
	{ "ls", do_dir},
	{ "sysc",do_sysc},
	{ "register", do_register},
	{ "exit", do_exit},
	{ "clear", do_Clear},
	{ NULL, NULL }
};
/*
    登陆:login userName
	登出:logout
	注册:register
	修改用户口令:passwd
	打开文件:open
	关闭文件:close
	建立文件:mkfile
	删除文件:rm
	写文件:write
	读文件:read
	列出所有文件:ls
	改变文件权限:chmod
	改变文件拥有者:chown
	改变文件名:mv
	显示文件内容:type
	退出程序:exit
	同步到磁盘:sysc
*/

void loginWelcome()
{
	cout << "Welcome to use filesystem build by hpc" << endl;
	cout << "Input help to start" << endl;
	cout << "Please enter: "<<endl;
}

void dealCmd()
{
	string s;
	getline(cin, s);
		stringstream stream(s);// string object for input
		int i = 0;
		while (stream >> cmd_in.cmdNum[i])
			i++;
		int flag = 0;
		for (int i = 0; functionList[i].pname!=NULL; i++)
		{
			if (strcmp(functionList[i].pname, cmd_in.cmdNum[0].c_str()) == 0)
			{
				flag = 1;
				functionList[i].handler();
				break;
			}
		}
		if (!flag)
			cout << "Wrong command! Please enter 'help' to get help" << endl;

}
