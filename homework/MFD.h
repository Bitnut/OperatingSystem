#ifndef MFD_H_INCLUDED
#define MFD_H_INCLUDED
#include<string>

// header for fileControl
/*
*        File system's core part. Load the
*        info of users from txt, save as object
*        properties. Then complete disk work by
*        save these info before exit
*/
struct MFD
{
	char usrname[14];       // user name
	char usrpass[14];       // user password
	int link;               // users' link to their UFD
};
struct UFD
{
	char filename[14];      // file name
	int protect;            // protect way read only: 0, write only: 1, read and write: 2
	int length;             // length of file
	int addr;               // address of file on the disk
};
struct UOF
{
	char filename[14];      // file name
	int protect;            // protect way
	int state;              // open state. 0: create and close 1:create and open
	int read_poit;          // read pointer
	int write_poit;         // write pointer
};

struct cluster
{
	int nextNum;            // next number if next is itself file ends
	int is_data;            // mark if this disk block is occupied
	char data[256];         // every disk block is 256 char long
};

#endif // MFD_H_INCLUDED
