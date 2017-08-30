#ifndef USERDASHBOARD_H_INCLUDED
#define USERDASHBOARD_H_INCLUDED

#include<string>
using namespace std;
typedef void(*func)(void);
struct hand
{
	char *pname;
	func handler;
};

struct cmd
{
	string cmdNum[4];
};
void dealCmd();


#endif // USERDASHBOARD_H_INCLUDED
