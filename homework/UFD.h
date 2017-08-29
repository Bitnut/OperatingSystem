#ifndef UFD_H_INCLUDED
#define UFD_H_INCLUDED
#include<iostream>
#include<string>

// elements for UOF
class UOF_el {
private:
	string filename;
	int protect;
	int currLength;
	int maxLength;
	int fileAddress;
	//int descriptor;
public:
	UOF_el(){
		protect = 1;
		currLength = 0;
		maxLength = 0;
		file_address = 0;
		//descriptor = -1;
	}
};


class UOF {
private:
    const maxOpenNum = 4;
	UOF_item item[maxOpenNum];
	int counter;
public:
	int find() {
		for (int i = 0;i < maxOpenNum;i++) {
			if (item[i].state == 0)
				return i;
		}
		return -1;
	}


	int UOF_check(int descriptor) {
		for (int i = 0;i < counter;i++)
			if (item[i].instance->descriptor == descriptor)
				return i;
		return -1;
	}

	UFD_item* UOF_find(int descriptor) {
		for (int i = 0;i < counter;i++)
			if (item[i].instance->descriptor == descriptor)
				return item[i].instance;
		return 0;
	}


	UOF(){
		counter = 0;

	}

};


class UFD {
private:
	const maxUserNum;

	UFD() {
		total_num = 0;
	}

	UFD_item* find() {
		for (int i = 0;i < MAX_FILE_NUMBER;i++) {
			if (item[i].descriptor == -1) {
				item[i].descriptor = i;
				return &item[i];
			}
		}
		return 0;
	}

	UFD_item* find(int descriptor) {
		for (int i = 0;i < MAX_FILE_NUMBER;i++) {
			if (item[i].descriptor == descriptor) {
				return &item[i];
			}
		}
		return 0;
	}



#endif // UFD_H_INCLUDED
