#ifndef USERDASHBOARD_H_INCLUDED
#define USERDASHBOARD_H_INCLUDED

class userDashboard {
private:
    int descriptor;
    int protect;
    int max;
    int desc;
    int length;
    int a;
    int choice;
    void print();

public:
    userDashboard(){
        int descriptor = 0;
        int protect = 0;
        int max = 0;
        int desc = 0;
        int length = 0;
        int a = 0;
        int choice = 0;
    }
    void menu();

};


#endif // USERDASHBOARD_H_INCLUDED
