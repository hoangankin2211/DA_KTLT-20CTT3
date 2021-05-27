#include"ConsoleProcess.h"
#include "login.h"
#include "Menu.h"
#include"Header.h"
#include<stdio.h> 
#include<conio.h> 

void insertUserName(string& username) {
    showPointer();
    char index=getch();
    while (index != 13) {
        //Backspace
        if (index == 8) {
            if (username.size() > 0) {
                username.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        //Other index
        else if (index >= 33 && index <= 126 && username.size()<=15) {
            cout << index;
            username.push_back(index);
        }
        index = getch();
    }
}

void insertPassword(string& password) {
    showPointer();
    char index = getch();
    while (index != 13) {
        //Backspace
        if (index == 8) {
            if (password.size() > 0) {
                password.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        //Other index
        else if (index >= 33 && index <= 126 && password.size() <= 15) {
            cout << "*";
            password.push_back(index);
        }
        index = getch();
    }
}

void LoginInterface(User &user){
    
    showPointer();
    textBgColor(2, 0);
    system("cls");

    user.ID=user.Password="";

    
    gotoxy(2, 15);
    cout << "  _   _   ____  __  __  _   _  ____";
    gotoxy(2, 16);
    cout << " | | | | / ___||  \\/  || | | |/ ___|";
    gotoxy(2, 17);
    cout << " | |_| || |    | |\\/| || | | |\\___ \\";
    gotoxy(2, 18);
    cout << " |  _  || |___ | |  | || |_| | ___) |";
    gotoxy(2, 19);
    cout << " |_| |_| \\____||_|  |_| \\___/ |____/" ;


    gotoxy(86, 15);
    cout << "  _____  ___  _____" ;
    gotoxy(86, 16);
    cout << " |  ___||_ _||_   _|" ;
    gotoxy(86, 17);
    cout << " | |_    | |   | |" ;
    gotoxy(86, 18);
    cout << " |  _|   | |   | |" ;
    gotoxy(86, 19);
    cout << " |_|    |___|  |_|" ;

    gotoxy(38, 0);
    cout << " __  __    _    _   _    _    ____ _____ ____";
    gotoxy(38, 1);
    cout << "|  \\/  |  / \\  | \\ | |  / \\  / ___| ____|  _ \\ ";
    gotoxy(38, 2);
    cout << "| |\\/| | / _ \\ |  \\| | / _ \\| |  _|  _| | |_) |";
    gotoxy(38, 3);
    cout << "| |  | |/ ___ \\| |\\  |/ ___ \\ |_| | |___|  _ <";
    gotoxy(38, 4);
    cout << "|_|  |_/_/   \\_\\_| \\_/_/   \\_\\____|_____|_| \\_\\ ";

    gotoxy(40, 6);
    cout << " ____ _____ _   _ ____  _____ _   _ _____";
    gotoxy(40, 7);
    cout << "/ ___|_   _| | | |  _ \\| ____| \\ | |_   _|";
    gotoxy(40, 8);
    cout << "\\___ \\ | | | | | | | | |  _| |  \\| | | |";
    gotoxy(40, 9);
    cout << " ___) || | | |_| | |_| | |___| |\\  | | |";
    gotoxy(40, 10);
    cout << "|____/ |_|  \\___/|____/|_____|_| \\_| |_|";
    
    textColor(0);
    drawRectangle(47, 15, 27, 10, 11);
    gotoxy(48, 16);
    cout<<"USERNAME : ";
    gotoxy(48,19);
    cout<<"PASSWORD : ";
    
    drawRectangle(48, 17, 25, 1, 15);
	drawRectangle(48, 20, 25, 1, 15);
	gotoxy(48, 22);
	cout<<"ENTER TO LOGIN";

    gotoxy(48,17);
    insertUserName(user.ID);

    gotoxy(48,20);
    insertPassword(user.Password);
}

int CheckLogin(User& user) {
    fstream file1,file2;
    file1.open("file_save/login_info.csv",ios::in);
    file2.open("file_save/login_info.csv",ios::in);

    if (!file1.is_open() || !file2.is_open())    
   	    cout << "Error File Open";
    
    string row,column;
    int caseUser;
    bool check=false;
    while (!file1.eof())
    {   
        getline(file1,row);
        while (!file2.eof())
        {
            getline(file2,column,',');
            if (column.compare(user.ID)==0) {
                getline(file2,column,',');
                if (column.compare(user.Password)==0) {
                    check=true;
                    getline(file2, column, ',');
                    caseUser = stoi(column, 0, 10);
                    break;
                }
            }
            getline(file2,column);
            break;
        }
        if (check==true) break;    
    }
    
    if (check==false) return -1;
    
    user.role = caseUser;
    if (caseUser == 1) {
        getline(file2, column, '\n');
        user.info.Class = column;
    }

    file1.close();
    file2.close();
    
    return caseUser;
}

void repeatLogin(User &user){
    textColor(0);
    
    do
	{   
        system("cls");
		LoginInterface(user);
        
		if (CheckLogin(user) ==-1)
		{   
			gotoxy(48, 24);
			cout<<"LOGIN FAIL";
            hidePointer();
			Sleep(900);
		}
	} 
    while (CheckLogin(user) == -1);
    
    gotoxy(48, 24);
    cout<<"LOGIN SUCCESSFUL";
    hidePointer();
    Sleep(900);
    system("cls");
    if (CheckLogin(user) == 1) menuStudent(user);
    else menuStaff(user);
}



