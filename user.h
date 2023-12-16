#include "sql-connection.h"
#include <iostream>
using namespace std;

class users {
	string uName;
	int sPin  = 123;

protected:
	int ID;
	sqlconn consql;


public:
	bool loginCheck(char userType){
		int pin;
		cout
			<< endl
			<< "-------------------------------------" << endl
			<< "Enter user ID (use digits only)\t: ";
		cin >> ID;
		cout
			<< "Enter Passcode(use digits only)\t: ";
		cin >> pin;
		cout
			<< "-------------------------------------" << endl << endl;
		


		if (pin == consql.getPin(ID,userType)) return true;
		else { 
			
			cout << "Incorrect passcode or user ID"<<endl; return false;
		}
	}

	 virtual void loginPage()=0;
	
};


class adminclss : public users {

public:
	void loginPage() {
		system("cls");
		char op;
		cout
			<< "_____________________________________\n"

			<< "____________Administrator____________|" << endl
			<< endl
			<< "   Select a following task..." << endl
			<< endl
			<< "   1 - Insert Student" << endl
			<< "   2 - Insert Staff member" << endl
			<< "   3 - Insert Course" << endl
			<< "   4 - Show Registered student" << endl
			<< "   5 - Show Staff members" << endl
			<< "   6 - Show Course list" << endl
			<< "   7 - Remove Student" << endl
			<< "   8 - Change Security pin of users" << endl
			<< endl
			<< "Enter your choice : ";
		cin >> op;

		switch (op)
		{
		case '1':consql.insertStudent(); break;
		case '2':consql.insertStaffMember(); break;
		case '3':consql.createCourse(); break;
		case '4':consql.showRegStudent(); break;
		case '5':consql.showStaffMembers(); break;
		case '6':consql.showCourses(); break;
		case '7':consql.removeStudent(); break;
		case '8':consql.changeSecrityPin(); break;


		default:cout << "invalid input";
			break;
		}

	}

};

class managerclss : public users {


public:

	void loginPage() {
		system("cls");
		char op;
		cout
			<< "_____________________________________\n"

			<< "______________Manager________________|" << endl
			<< endl
			<< "   Select a following task..." << endl
			<< endl
			<< "   1 - View registered student" << endl
			<< "   2 - View student registered to courses" << endl
			<< "   3 - View course list" << endl
			<< endl
			<< "Enter your choice : ";
		cin >> op;

		switch (op)
		{
		case '1':consql.showRegStudent(); break;
		case '2':consql.showRegCouStudent(); break;
		case '3':consql.showCourses(); break;


		default:cout << "invalid input";
			break;
		}

	}

};

class academicclss : public users {
public:

	void loginPage() {
		system("cls");
		char op;
		cout
			<< "_____________________________________\n"

			<< "___________Academic Staff____________|" << endl
			<< endl
			<< "   Select a following task..." << endl
			<< endl
			<< "   1 - View registered student" << endl
			<< "   2 - View student registered to courses" << endl
			<< "   3 - View course list" << endl
			<< endl
			<< "Enter your choice : ";
		cin >> op;

		switch (op)
		{
		case '1':consql.showRegStudent(); break;
		case '2':consql.showRegCouStudent(); break;
		case '3':consql.showCourses(); break;

		default:cout << "invalid input";
			break;
		}

	}


};

class studenclss : public users {

	string stName;
	int stCode, stCourse;
	

public:

	void loginPage() {
		system("cls");
		char op;
		cout
			<< "_____________________________________\n"

			<< "_______________Student_______________|" << endl
			<< endl
			<< "   Select a following task..." << endl
			<< endl
			<< "   1 - View profile" << endl
			<< "   2 - Register for a course" << endl
			<< "   3 - View course list" << endl
			<< endl
			<< "Enter your choice : ";
		cin >> op;

		switch (op)
		{
		case '1':consql.showProfile(ID); break;
		case '2':consql.selectCourse(ID); break;
		case '3':consql.showCourses(); break;

		default:cout << "invalid input";
			break;
		}

	}
	
};
