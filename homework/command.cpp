#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<cstring>
#include<vector>
#include<ctime>
#include "MFD.h"
#include"fileControl.h"
#include"userDashboard.h"
using namespace std;

extern cmd cmd_in;
extern vector < vector<UFD> > FileInfo;
extern UFD FileInput;
extern vector<cluster> FileCluster;
extern vector<MFD> UsrInfo;
extern vector< vector<UOF> > FileState;
extern UOF StateInput;
extern cluster ClusterInput;
extern MFD UsrInput;
extern int num;
extern int Headnum;
extern int curID;
extern int countOpen;


void do_Chmod()
{
	int temp;
	//Chmod	filename mode
	for (int i = 0; i < FileInfo[curID].size(); i++)
	{
		if (strcmp(FileInfo[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			stringstream ss;
			ss << cmd_in.cmdNum[2];
			ss >> temp;
			FileInfo[curID][i].protect = temp;
			break;
		}
	}
	for (int i = 0; i < FileState[curID].size(); i++)
	{
		if (strcmp(FileState[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			FileState[curID][i].protect = temp;
			break;
		}
	}
	cout << "success!"<<endl;
}

void do_Chown()
{
	// Chown filename new_owner
     vector<UFD>::iterator it;
	 for (it = FileInfo[curID].begin(); it != FileInfo[curID].end(); it++)
	{
		if (strcmp((*it).filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			strcpy(FileInput.filename,(*it).filename);
			FileInput.length = (*it).length;
			FileInput.protect = (*it).protect;
			FileInput.addr = (*it).addr;

			FileInfo[curID].erase(it);
			break;
		}
	}
	 vector<UOF>::iterator it_num1;
	 for (it_num1 = FileState[curID].begin(); it_num1 != FileState[curID].end(); it_num1++)
	 {
		 if (strcmp((*it_num1).filename, cmd_in.cmdNum[1].c_str()) == 0)
		 {
			 strcpy(StateInput.filename, (*it_num1).filename);
			 StateInput.protect = (*it_num1).protect;
			 StateInput.state = (*it_num1).state;
			 StateInput.read_poit = (*it_num1).read_poit;
			 StateInput.write_poit = (*it_num1).write_poit;

			 FileState[curID].erase(it_num1);
			 break;
		 }
	 }

	int tempID;
	for (int i = 0; i < UsrInfo.size(); i++)
	{
		if (strcmp(UsrInfo[i].usrname, cmd_in.cmdNum[2].c_str()) == 0)
		{
			tempID = i;
			break;
		}
	}
	int flag = 0;
	// check for re-name file
	for (int i = 0; i < FileInfo[tempID].size(); i++)
	{
		if (strcmp(FileInfo[tempID][i].filename, cmd_in.cmdNum[2].c_str()) == 0)
		{
			flag = 1;
			break;
		}
	}
	if (!flag)
	{
		FileInfo[tempID].push_back(FileInput);
		FileState[tempID].push_back(StateInput);
		cout << "success！" << endl;
	}
	else
	{
		cout << "file named "<<""<<" already exists" << endl;
	}
}

void do_Mv()
{
	//Mv srcFile desFile
	for (int i = 0; i < FileInfo[curID].size(); i++)
	{
		if (strcmp(FileInfo[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			strcpy(FileInfo[curID][i].filename, cmd_in.cmdNum[2].c_str());
			break;
		}
	}

	for (int i = 0; i < FileState[curID].size(); i++)
	{
		if (strcmp(FileState[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			strcpy(FileState[curID][i].filename, cmd_in.cmdNum[2].c_str());
			break;
		}
	}
	cout << "success" << endl;
}

void do_dir()
{
	for (int i = 0; i < FileInfo[curID].size(); i++)
	{
		cout << FileInfo[curID][i].filename << "  ";
	}
	cout << endl;

}

void do_Type()
{
    //Type filename
	int address;
	for (int i = 0; i < FileInfo[curID].size(); i++)
	{
		if (strcmp(FileInfo[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			address = FileInfo[curID][i].addr;
			break;
		}
	}
	int index;
	for (int i = 0; i < FileState[curID].size(); i++)
	{
		if (strcmp(FileState[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			index = i;
			break;
		}
	}
        cout<<"filename: \t\t"<< FileState[curID][index].filename<<endl;
        cout<<"protect: \t\t"<< FileState[curID][index].protect<<endl;
        cout<<"state: \t\t\t"<< FileState[curID][index].state<<endl;
        cout<<"readpoint: \t\t"<< FileState[curID][index].read_poit<<endl;
        cout<<"writepoint: \t\t"<< FileState[curID][index].write_poit<<endl;
        cout<<"first block address:\t"<<address<<endl;
}

void do_Passwd()
{
	//Passwd oldPwd  newPwd
	if (strcmp(UsrInfo[curID].usrpass, cmd_in.cmdNum[1].c_str()) == 0)
	{
		strcpy(UsrInfo[curID].usrpass, cmd_in.cmdNum[2].c_str());
		cout << "success!" << endl;
	}
	else
		cout << "Wrong password!" << endl;
}

void do_sysc()
{
	out_to_file();
	cout << "Successfully syn!" << endl;
}

void do_Login()
{
	//Login	userName pwd
	int flag = 0;
	for (int i = 0; i < UsrInfo.size(); i++)
	{
		if (strcmp(cmd_in.cmdNum[1].c_str(), UsrInfo[i].usrname) == 0 && strcmp(cmd_in.cmdNum[2].c_str(), UsrInfo[i].usrpass) == 0)
		{
			curID = i;
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		cout << "success！" << endl;
		return;
	}
	else
	{
		cout << "Not exits!" << endl;
	}
}

void do_exit()
{
	do_sysc();
	cout << "Successfully out, see you!" << endl;
	exit(0);
}

void do_Logout()
{
	/*cout << "您是否已经使用sysc命令保存信息至磁盘？Y/N" << endl;
	char c;
	c = getchar();
	if (c == 'Y')*/
	cout << "Success! Please choose a user to login" << endl;
}

void do_register()
{
	//Register usrName pwd
	if (UsrInfo.size() < 16)
	{
		int flag = 1;
		for (int i = 0; i < UsrInfo.size(); i++)
		{
			if (strcmp(cmd_in.cmdNum[1].c_str(), UsrInfo[i].usrname) == 0)
			{
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			strcpy(UsrInput.usrname, cmd_in.cmdNum[1].c_str());
			strcpy(UsrInput.usrpass, cmd_in.cmdNum[2].c_str());
			UsrInput.link = UsrInfo.size();
			UsrInfo.push_back(UsrInput);

			vector<UFD> t;
			FileInfo.push_back(t);

			vector<UOF> temp;
		    FileState.push_back(temp);

			cout << "success!" << endl;

		}
		else
		{
			cout << "Already exists" << endl;
		}
	}
	else
		cout << "Bigger than 16 users now! Cannot create a user" << endl;
}

void do_Create()
{
	//create name mode
	if (FileInfo[curID].size() < 16)
	{
		int flag = 1;
		//check if there's the same name file
		for (int i = 0; i < FileInfo[curID].size(); i++)
		{
			if (strcmp(FileInfo[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
			{
				flag = 0;
				break;
			}
		}
		if (!flag)
		{
			cout << FileInput.filename << "EXITS！" << endl;
			return;
		}

		strcpy(FileInput.filename, cmd_in.cmdNum[1].c_str());
		stringstream ss;
		ss << cmd_in.cmdNum[2];
		int temp;
		ss >> temp;
		FileInput.length = temp;
		ss.clear();
		ss << cmd_in.cmdNum[3];
		ss >> temp;
		cout<< temp <<endl;
		FileInput.protect = temp;
		for (int i = 0; i < FileCluster.size(); i++)
		{
		    int ran = rand() % 68;
			if (FileCluster[ran].is_data == 0)
			{
				FileInput.addr = ran;
				FileCluster[ran].is_data = 1;
				break;
			}
		}
		FileInfo[curID].push_back(FileInput);
		cout << "build success!" << endl;

		strcpy(StateInput.filename, cmd_in.cmdNum[1].c_str());
		StateInput.state = 0;
		StateInput.protect = FileInput.protect;
		StateInput.read_poit = 0;
		StateInput.write_poit = 0;

		FileState[curID].push_back(StateInput);

	}
	else
		cout << "16 files already! No more files！" << endl;
}

void do_Delete()
{
	//delete filename
	int flag = 0;
	vector<UFD>::iterator it;
	for (it = FileInfo[curID].begin(); it != FileInfo[curID].end(); it++)
	{
		if (strcmp((*it).filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			//FileInfo[curID].erase(it);
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		//Type filename
		int address;
		for (int i = 0; i < FileInfo[curID].size(); i++)
		{
			if (strcmp(FileInfo[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
			{
				address = FileInfo[curID][i].addr;
				break;
			}
		}
		int index;
		for (int i = 0; i < FileState[curID].size(); i++)
		{
			if (strcmp(FileState[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
			{
				index = i;
				break;
			}
		}

		vector<int> reset_addr;
		reset_addr.clear();

		while (1)
		{
			if (FileCluster[address].nextNum == address)
			{
				for (int i = 0; i < FileState[curID][index].write_poit; i++)
					FileCluster[address].data[i]=0;
				reset_addr.push_back(address);
				break;
			}
			else
			{
				reset_addr.push_back(address);
				for (int i = 0; i < 256; i++)
				{
					 FileCluster[address].data[i]=0;
				}
				if (FileCluster[address].nextNum != address)
				{
					address = FileCluster[address].nextNum;
				}
				else
					break;
			}
		}

		for (int w = 0; w < reset_addr.size(); w++)
		{
			FileCluster[reset_addr[w]].is_data = 0;
			FileCluster[reset_addr[w]].nextNum = reset_addr[w];
		}

		vector<UFD>::iterator it;
		for (it = FileInfo[curID].begin(); it != FileInfo[curID].end(); it++)
		{
			if (strcmp((*it).filename, cmd_in.cmdNum[1].c_str()) == 0)
			{
				FileInfo[curID].erase(it);
				flag = 1;
				break;
			}
		}

		vector<UOF>::iterator it1;
		for (it1 = FileState[curID].begin(); it1 != FileState[curID].end(); it1++)
		{
			if (strcmp((*it1).filename, cmd_in.cmdNum[1].c_str()) == 0)
			{
				FileState[curID].erase(it1);
				break;
			}
		}

		cout << "success!" << endl;
	}
	else
		cout << "File not exists!" << endl;


}

void do_Open()
{
	//Open  filename mode
	stringstream ss;
	ss << cmd_in.cmdNum[2];
	int temp;
	ss >> temp;
	int flag = 0;
	cout<<"You have opened: "<<countOpen<<" files!"<<endl;
	if(countOpen == 4)
    {
        cout<<"You have opened 4 files! No more!";
    }
    else
    {
        for (int i = 0; i < FileState[curID].size(); i++)
        {
            if (strcmp(FileState[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
            {
			FileState[curID][i].state = 1;
			countOpen++;
			flag = 1;
			break;
            }
        }
        if (flag)
            cout << "Open success!" << endl;
        else
        {
            strcpy(StateInput.filename, cmd_in.cmdNum[1].c_str());
            StateInput.protect = temp;
            StateInput.state = 1;
            StateInput.read_poit = StateInput.write_poit = 0;
            FileState[curID].push_back(StateInput);
            cout << "You have opened this file！" << endl;
        }
    }


}

void do_Close()
{
	//close filename
	vector<UOF>::iterator it;
	for (it = FileState[curID].begin(); it != FileState[curID].end(); it++)
	{
		if (strcmp((*it).filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			FileState[curID].erase(it);
			countOpen--;
			cout << "success!" << endl;
			break;
		}
	}
}

/*int num;
int next_num;
int is_data;
char data[256];*/

void do_Write()
{
	//Write	filename buffer nbytes 写文件   物理空间68

	char buf[1024];
	stringstream ss;
	ss << cmd_in.cmdNum[3];
	int temp;
	ss >> temp;


	for (int i = 0; i < FileInfo[curID].size(); i++)
	{
		if (strcmp(FileInfo[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			if (FileInfo[curID][i].protect == 1 || FileInfo[curID][i].protect == 2)//判断权限
			{
				break;
			}
			else
			{
				cout << "Permission denied!" << endl;
				return;
			}
		}
	}

	int index;
	for (int i = 0; i < FileState[curID].size(); i++)
	{
		if (strcmp(FileState[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			index = i;
			break;
		}
	}
	//起始物理块
	int address;
	for (int i = 0; i < FileInfo[curID].size(); i++)
	{
		if (strcmp(FileInfo[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			address = FileInfo[curID][i].addr;
			break;
		}
	}
            cout<<address<<endl;
            // find the last block
			while (FileCluster[address].nextNum != address)
				address = FileCluster[address].nextNum;
            cout<<address<<endl;


			cout << "Please write：" << endl;
			gets(buf);
			fflush(stdin);
            cout<<buf;


			int wbegin;
			wbegin = FileState[curID][index].write_poit;
			cout<<curID<<" "<<index<<endl;
			cout<<wbegin<<endl;

			vector <int> newspace_num;// for calculate block size
			newspace_num.clear();

			//int num = (256-wbegin+temp) / 256-1;
			if (temp <= 256 - wbegin)
				num = 0;
			else
			{
				num = ceil((temp - (256 - wbegin))*1.0 / 256);
			}

			newspace_num.push_back(address);
			for (int i = 0; i < FileCluster.size(); i++)
			{
				if (newspace_num.size() == num+1)
					break;

                int ran = rand() % 68;
				if (FileCluster[ran].is_data == 0)
				{
					newspace_num.push_back(ran);
					FileCluster[ran].is_data = 1;
				}
			}
			for (int k = 0; k < newspace_num.size() - 1; k++)
			{
				FileCluster[newspace_num[k]].nextNum = newspace_num[k + 1];
			}
			// write data!
			for (int i = 0; i < temp; i++)
			{
				if (wbegin == 256)
				{
					wbegin = 0;
					address = FileCluster[address].nextNum;
				}
				FileCluster[address].data[wbegin] = buf[i];
				wbegin++;
			}

			// refresh write pointer
			FileState[curID][index].write_poit = wbegin;
			cout << "Done~ Please sysc!" << endl;
			return;

}

void do_Read()
{
	//Read 	filename buffer nbytes
	char buf[1024];
	stringstream ss;
	ss << cmd_in.cmdNum[3];
	int temp;
	ss >> temp;

	for (int i = 0; i < FileInfo[curID].size(); i++)
	{
		if (strcmp(FileInfo[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			if (FileInfo[curID][i].protect == 0 || FileInfo[curID][i].protect == 2)// permission check
			{
				break;
			}
			else
			{
				cout << "Permission denied!" << endl;
				return;
			}
		}
	}

	int index;
	for (int i = 0; i < FileState[curID].size(); i++)
	{
		if (strcmp(FileState[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			index = i;
			break;
		}
	}

	int address;
	for (int i = 0; i < FileInfo[curID].size(); i++)
	{
		if (strcmp(FileInfo[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			address = FileInfo[curID][i].addr;
			break;
		}
	}

	int rbegin;
	rbegin = FileState[curID][index].read_poit;
	int addcur = rbegin / 256;

	for (int i = 0; i < addcur; i++)
	{
		address = FileCluster[address].nextNum;
	}

	for (int i = 0; i < temp; i++)
	{
		if (rbegin % 256 == 255)
		{
			address = FileCluster[address].nextNum;
		}
		buf[i] = FileCluster[address].data[rbegin % 256];
		rbegin++;
	}

	FileState[curID][index].read_poit = rbegin;

	cout << "read out：" << endl;
	for (int i = 0; i < temp; i++)
		cout << buf[i];
	cout << endl;

}


void doTempWrite()
{
	//Write	filename buffer nbytes

	char buf[1024];
	stringstream ss;
	ss << cmd_in.cmdNum[3];
	int temp;
	ss >> temp;


	for (int i = 0; i < FileInfo[curID].size(); i++)
	{
		if (strcmp(FileInfo[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			if (FileInfo[curID][i].protect == 1 || FileInfo[curID][i].protect == 2)
			{
				break;
			}
			else
			{
				cout << "Permission denied!" << endl;
				return;
			}
		}
	}

	int index;
	for (int i = 0; i < FileState[curID].size(); i++)
	{
		if (strcmp(FileState[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			index = i;
			break;
		}
	}
	int address;
	for (int i = 0; i < FileInfo[curID].size(); i++)
	{
		if (strcmp(FileInfo[curID][i].filename, cmd_in.cmdNum[1].c_str()) == 0)
		{
			address = FileInfo[curID][i].addr;
			break;
		}
	}

	strcpy(buf, cmd_in.cmdNum[2].c_str());

	int wbegin;
	wbegin = FileState[curID][index].write_poit;

	while (FileCluster[address].nextNum != address)
		address = FileCluster[address].nextNum;

	vector <int> newspace_num;
	newspace_num.clear();
	newspace_num.push_back(address);

	//int num = (256-wbegin+temp) / 256-1;
	if (temp <= 256 - wbegin)
		num = 0;
	else
	{
		num = ceil((temp - (256 - wbegin))*1.0 / 256);
	}



	cout << newspace_num.size() << endl;



	for (int i = 0; i < FileCluster.size(); i++)
	{
		if (newspace_num.size() == num + 1)
			break;
		if (FileCluster[i].is_data == 0)
		{
			newspace_num.push_back(i);
			FileCluster[i].is_data = 1;
		}
	}

	for (int k = 0; k < newspace_num.size() - 1; k++)
	{
		FileCluster[newspace_num[k]].nextNum = newspace_num[k + 1];
	}
	for (int i = 0; i < temp; i++)
	{
		if (wbegin == 256)
		{
			wbegin = 0;
			address = FileCluster[address].nextNum;
		}
		FileCluster[address].data[wbegin] = buf[i];
		wbegin++;
	}
	FileState[curID][index].write_poit = wbegin;
	cout << "success!" << endl;
	return;

}

void do_Help()
{
	cout << "登陆:\t\tlogin userName pwd" << endl;
	cout << "登出:\t\tlogout	" << endl;
	cout << "注册:\t\tregister usrName pwd" << endl;
	cout << "修改用户口令:\tpasswd	oldPwd  newPwd" << endl;
	cout << "打开文件:\topen   filename mode" << endl;
	cout << "关闭文件:\tclose  filename" << endl;
	cout << "建立文件:\tmkfile	 filename mode" << endl;
	cout << "删除文件:\trm	 filename" << endl;
	cout << "写文件:\twrite	filename buffer nbytes" << endl;
	cout << "读文件:\tread 	filename buffer nbytes" << endl;
	cout << "列出所有文件:\tls" << endl;
	cout << "改变文件权限:\tchmod	filename mode" << endl;
	cout << "改变文件拥有者:\tchown	filename new_owner" << endl;
	cout << "改变文件名:\tmv	srcFile desFile" << endl;
	cout << "显示文件内容:\ttype	filename" << endl;
	cout << "退出程序:\texit" << endl;
	cout << "同步到磁盘:\tsysc" << endl;
}

void do_Clear()
{
	system("cls");
}
