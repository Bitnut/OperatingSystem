#ifndef USERDASHBOARD_H_INCLUDED
#define USERDASHBOARD_H_INCLUDED
#include<string>
using namespace std;
// structs deal with users' commands and printing welcome page


typedef void(*func)(void);
struct HANDLE
{
	char *pname;
	func handler;
};
struct cmd
{
	string cmdNum[4];
};
void dealCmd();
void loginWelcome();

#endif // USERDASHBOARD_H_INCLUDED
