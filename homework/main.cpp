#include<iostream>
#include<ctime>
#include"userDashboard.h"
#include"Fileopera.h"
#include"MFD.h"
#include"command.h"
#include<vector>

using namespace std;

vector <MFD> UsrInfo;
vector < vector<UFD> > FileInfo;
vector< vector<UOF> > FileState;
vector< cluster> FileCluster;

MFD UsrInput;
UFD FileInput;
UOF StateInput;
cluster ClusterInput;
int num; //Ñ¡ÏîÑ¡Ôñ
int Headnum;
int curID;


void loginWelcome();

int main() {
    loginWelcome();
	initFiletoRom();
	while (1)
	{
		//Ä¬ÈÏrootµÇÂ½
		cout << "["<<UsrInfo[curID].usrname<<"]$ :";
		dealCmd();
	}
	return 0;
}
hand handlerlist[] =
{
	{ "chmod", do_Chmod },
	{ "chown", do_Chown },
	{ "mv", do_Mv },
	{ "copy", do_Copy },
	{ "type", do_Type },
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

void loginWelcome()
{
	cout << "Welcome to use filesystem build by hpc" << endl;
	cout << "Input help to start" << endl;
	cout << "Please enter: "<<endl;
}


