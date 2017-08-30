#pragma once
#include<iostream>
#include<ctime>
#include"userDashboard.h"
#include<string>
#include<sstream>
#include<cstring>
using namespace std;

cmd cmd_in;
extern hand handlerlist[];

void dealCmd()
{
	string s;
	getline(cin, s);
		stringstream stream(s);// string object for input
		int i = 0;
		while (stream >> cmd_in.cmdNum[i])
			i++;
		int flag = 0;
		for (int i = 0; handlerlist[i].pname!=NULL; i++)
		{
			if (strcmp(handlerlist[i].pname, cmd_in.cmdNum[0].c_str()) == 0)
			{
				flag = 1;
				handlerlist[i].handler();
				break;
			}
		}
		if (!flag)
			cout << "Wrong command! Please enter 'help' to get help" << endl;

}
