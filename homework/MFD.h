#ifndef MFD_H_INCLUDED
#define MFD_H_INCLUDED
#include<string>
#include"UFD.h"

class MFD {
public:
	string userName;
	UFD List[];


	MFD() {
		ufd = new UFD;
		for (int i = 0;i < 10;i++)
			user_name[i] = 0;
	}
};

#endif // MFD_H_INCLUDED
