#include <stdlib.h>
#include <iostream>
#include "users.h"
#include <string>

using namespace std;


int main() {
	

	char op,con;
	int pin;


		system("cls");
		cout
			<< "_____________________________________\n"
			<< "                                     |\n"
			<< "--Student management System  [demo]--|\n"
			<< "_____________________________________|\n"

			<< "_____________Login page______________|\n\n"

			<< "Sign in as....\n\n"
			<< "  a - Administrator\n"
			<< "  s - Student\n"
			<< "  m - Manager\n"
			<< "  c - Acdemic staff" << endl
			<< endl
			<< "Please enter your choice: ";
		cin >> op;

	

		switch (op) {

		case 'a': {									
			adminclss lcadmin;
			if (lcadmin.loginCheck(op))lcadmin.loginPage();
			else op = 'x';
		}
				break;

		case 'c': {
			academicclss lcacademic;
			if (lcacademic.loginCheck(op))lcacademic.loginPage();
			else op = 'x';

		}
				break;

		case 'm': {
			managerclss lcmanager;
			if (lcmanager.loginCheck(op))lcmanager.loginPage();
			else op = 'x';

		}
				break;


		case 's': {
			studenclss lcstudent;
			if (lcstudent.loginCheck(op))lcstudent.loginPage();
			else op = 'x';

		}
				break;


		default:cout << "invalid input";
		}

		if (cin.fail()){          //if this wasn't here the whlie loop get crashed
			system("cls");
			cout << "\nInvalid type of input.\n(Charactors instead of digits)\n\n";
			system("pause");
		} else {
			cout << endl 
				<< "press 'e' to log out ..."<< endl
				<<"press other key to continue... " << endl;
			cin >> con;
			cout << "Please wait..." << endl;

		}

	do									//after login correctly this loop will keep the user in there own menu page
	{
		switch (op) {

		case 'a': {
			adminclss lcadmin;
			lcadmin.loginPage();
		}
				break;

		case 'c': {
			academicclss lcacademic;
			lcacademic.loginPage();
		}
				break;

		case 'm': {
			managerclss lcmanager;
			lcmanager.loginPage();
		}
				break;


		case 's': {
			studenclss lcstudent;
			lcstudent.loginPage();
		}
				break;


		default: {
			cout << "Error in login" << endl;
			exit(1); }
		}
				
		if (cin.fail()) {          //if this wasn't here the whlie loop get crashed
			system("cls");
			cout << "\nInvalid type of input.\n(Charactors instead of digits)\n\n";
			system("pause");
		}
		else {
			cout << endl
				<< "press 'e' to log out and exit ..." << endl
				<< "press other key to continue... " << endl;
			cin >> con;
			cout <<"Please wait..." << endl;
		}

	} while (con != 'e' && (!cin.fail()) );
	if (con == 'e')exit(1);
	
	

 	return 0;
}



