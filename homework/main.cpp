#pragma once
#include<iostream>
#include<ctime>

using namespace std;

void print() {
	cout << "1. mk file" << endl;
	cout << "2. open file" << endl;
	cout << "3. read file" << endl;
	cout << "4. write file" << endl;
	cout << "5. close file" << endl;
	cout << "6. delete file" << endl;
	cout << "7. quit" << endl;
}


int main() {

	int order=0;

	while (order!=7) {
		int descriptor;
		int protect;
		int max;
		int desc;
		int length;
		int a;
		print();
		char name[10] = { 0 };
		cout << "Please input:";
		cin >> order;
		switch (order) {
		case 1:
			cout << "请输入文件名:";
			cin >> name;
			cout << "请输入文件大小:";
			cin >> max;
			cout << "请输入文件保护方式(仅读1 仅写2 读写为3):";
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

		}
	}




	return 0;
}



