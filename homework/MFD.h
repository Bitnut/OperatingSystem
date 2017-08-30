#ifndef MFD_H_INCLUDED
#define MFD_H_INCLUDED
#include<string>

struct MFD
{
	char usrname[14];
	char usrpass[14];
	int link;  //user number
};
struct UFD
{
	char filename[14];
	int protect;
	int length;
	//curr length not exist
	int addr;
};
struct UOF
{
	char filename[14];
	int protect;
	int state; //0建立,1打开
	int read_poit; //读写指针
	int write_poit;
};

struct cluster
{
	int nextNum;
	int is_data;
	char data[256];
};

#endif // MFD_H_INCLUDED
