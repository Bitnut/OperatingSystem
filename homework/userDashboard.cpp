#pragma once
#include<iostream>
#include<ctime>
#include"userDashboard.h"
#include<string>
using namespace std;

void userDashboard::print() {
	cout << "1. mk file" << endl;
	cout << "2. open file" << endl;
	cout << "3. read file" << endl;
	cout << "4. write file" << endl;
	cout << "5. close file" << endl;
	cout << "6. delete file" << endl;
	cout << "7. quit" << endl;
}


void userDashboard::menu() {


	while (choice!=7) {

		print();
		string name = {};
		cout << "$ ";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Please enter filename: ";
			cin >> name;
			cout << "Size: ";
			cin >> max;
			cout << "Protect way(ro:1 wr:2 rw:3): ";
			cin >> protect;
			break;

		case 2:
			cout << "请输入文件描述符以及保护方式:";
			cin >> descriptor;
			cin >> protect;
			break;

		case 3:
			cout << "请输入文件描述符以及字节长度:";
			cin >> desc >> length;
			break;

		case 4:
			cout << "请输入文件描述符以及字节长度:";
			cin >> desc >> length;
			cout << endl;
			break;

		case 5:
			cout << "请输入文件描述符:";
			cin >> a;
			break;

		case 6:
			cout << "请输入文件描述符:";
			cin >> a;
			continue;

        default:
            cout << "Wrong input! Please ENTER again";

		}

     }
}
