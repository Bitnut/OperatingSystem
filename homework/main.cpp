#include<iostream>
#include<ctime>
#include<vector>
#include"userDashboard.h"
#include"fileControl.h"
#include"MFD.h"
#include"command.h"t
using namespace std;
// objects that need manipulation initializing
// use vector to init objects multi
vector <MFD> UsrInfo;             // MFD contains user info
vector < vector<UFD> > FileInfo;  // UFD contains user properties
vector< vector<UOF> > FileState;  // UOF contains file descriptions
vector< cluster> FileCluster;     // FileClustrer for file management
MFD UsrInput;                     // For temp input user info
UFD FileInput;                    // For temp input file info
UOF StateInput;                   // For temp file state info
cluster ClusterInput;             // For cluster info
// variables for use
int num;                          //
int Headnum;                      //
int curID;                        // user ID number
int countOpen = 0;                // open file number controller

int main() {
    loginWelcome();
	initFiletoRom();
	while (1)
	{
		cout << "["<<UsrInfo[curID].usrname<<"]$ ";
		dealCmd();
	}
	return 0;
}






