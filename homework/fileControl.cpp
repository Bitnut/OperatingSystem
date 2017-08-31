#include<stdio.h>
#include<cstring>
#include<iostream>
#include<vector>
#include "common.h"
#include "MFD.h"
using namespace std;

//use claims in main
extern vector<MFD> UsrInfo;
extern vector< vector<UOF> > FileState;
extern vector< vector<UFD> > FileInfo;
extern vector< cluster> FileCluster;
extern int Headnum;
extern int countOpen;
extern MFD UsrInput;
extern UFD FileInput;
extern UOF StateInput;
extern cluster ClusterInput;

/*
*        FileControl is a module cooperate with
*        MFD as well as disk.txt, in order to
*        simulate the job of real disk
*/

// function for initiate file system
void initFiletoRom()
{   /*
    *     This file system is modeled depends on a txt file
    *     named 'disk.txt' in the same dir
    *     the txt file contains the most important message
    *     such as MFD, UFD, UOF and disk usage status
    */
	FILE *streamInit;
	if ((streamInit = fopen("disk.txt", "r")) == NULL)
	{
		cout << "Failed when reading the disk！" << endl;
		return;
	}
	/*
	*       loading MFD
	*       char usrname[14];
	*       char usrpass[14];
	*       int link;
	*/
	fscanf(streamInit, "%d", &Headnum);
	int alreadynum;
	int ret;
	alreadynum = 0;
	while (alreadynum<Headnum&&(ret = fscanf(streamInit, "%s %s %d", &UsrInput.usrname, &UsrInput.usrpass, &UsrInput.link)) != -1)
	{
		UsrInfo.push_back(UsrInput);
		alreadynum++;
	}
	// File info initializing
	vector<UFD> t;
	for (int i = 0; i < UsrInfo.size(); i++)
	{
		FileInfo.push_back(t);
	}
	vector<UOF> temp;
	for (int i = 0; i < UsrInfo.size(); i++)
	{
		FileState.push_back(temp);
	}

	/*
	*      loading UFD:
	*      char filename[14];
	*      int mode;
	*      int length;
	*      int addr;
	*/
	for (int i = 0; i < UsrInfo.size(); i++)
	{
		fscanf(streamInit, "%d", &Headnum);
	    alreadynum = 0;
		while (alreadynum<Headnum && (ret = fscanf(streamInit, "%s %d %d %d", &FileInput.filename, &FileInput.protect, &FileInput.length, &FileInput.addr)) != -1)
		{
			FileInfo[i].push_back(FileInput);
			alreadynum++;
		}
	}
	/*
	*      loading UOF
	*      char filename[14];
	*      int mode;
	*      int state; //0: exists and close,1: open
	*      int read_poit;
	*      int write_poit;
	*/
	for (int i = 0; i < UsrInfo.size(); i++)
	{
		fscanf(streamInit, "%d", &Headnum);
	    alreadynum = 0;
		while (alreadynum<Headnum && (ret = fscanf(streamInit, "%s %d %d %d %d", &StateInput.filename, &StateInput.protect, &StateInput.state, &StateInput.read_poit,&StateInput.write_poit)) != -1)
		{
			FileState[i].push_back(StateInput);
			if (StateInput.state == 1)
                countOpen++;
			alreadynum++;
		}
	}

	/*
	*       loading cluster
	*       int next_num;
	*       int is_data;
	*       char data[256];
	*/
    alreadynum = 0;
	char Tempbuf[256];
	int total = 0;
	char c;
	while (total < 68)
	{
		total++;
		memset(Tempbuf, 0, sizeof(Tempbuf));
		if ((ret = fscanf(streamInit, "%d %d", &ClusterInput.nextNum, &ClusterInput.is_data)) != -1)
		{
			if (ClusterInput.is_data == 1)
			{
				 fscanf(streamInit, "%c", &c);
				 fgets(Tempbuf, 256, streamInit);
			}
			strcpy(ClusterInput.data, Tempbuf);
			FileCluster.push_back(ClusterInput);
		}
		else
		{
			ClusterInput.nextNum = alreadynum;
			ClusterInput.is_data = 0;
			strcpy(ClusterInput.data, Tempbuf);

			FileCluster.push_back(ClusterInput);
		}
		alreadynum++;
	}

	fclose(streamInit);
}
// function for output to disk
void out_to_file()
{
	FILE* fd;
	fd = fopen("disk.txt", "w");
	fprintf(fd, "%d%c", UsrInfo.size(), ' ');
	for (int i = 0; i < UsrInfo.size(); i++)
		fprintf(fd, "%s %s %d%c", UsrInfo[i].usrname, UsrInfo[i].usrpass, UsrInfo[i].link, ' ');
	fprintf(fd, "\n");

	/*
	*      loading UFD:
	*      char filename[14];
	*      int mode;
	*      int length;
	*      int addr;
	*/
	for (int i = 0; i < FileInfo.size(); i++)
	{
		fprintf(fd, "%d%c", FileInfo[i].size(), ' ');
		for (int j = 0; j < FileInfo[i].size(); j++)
		{
			fprintf(fd, "%s %d %d %d%c", FileInfo[i][j].filename, FileInfo[i][j].protect, FileInfo[i][j].length,FileInfo[i][j].addr, ' ');
		}
		fprintf(fd, "\n");
	}

	/*
	*      loading UOF
	*      char filename[14];
	*      int mode;
	*      int state; //0: exists and close,1: open
	*      int read_poit;
	*      int write_poit;
	*/
	for (int i = 0; i < FileState.size(); i++)
	{
		fprintf(fd, "%d%c", FileState[i].size(), ' ');
		for (int j = 0; j < FileState[i].size(); j++)
		{
			fprintf(fd, "%s %d %d %d %d%c", FileState[i][j].filename, FileState[i][j].protect, FileState[i][j].state, FileState[i][j].read_poit,FileState[i][j].write_poit, ' ');
		}
		fprintf(fd, "\n");
	}

	/*
	*       loading cluster
	*       int next_num;
	*       int is_data;
	*       char data[256];
	*/
	for (int i = 0; i < FileCluster.size(); i++)
	{
		fprintf(fd, "%d %d%c", FileCluster[i].nextNum, FileCluster[i].is_data,' ');
		fputs(FileCluster[i].data, fd);
		fprintf(fd, "\n");
	}

	fclose(fd);
}
