#include <iostream>
#include <iomanip>

using namespace std;

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

//#include <mysql.h>
//#include "stdafx.h"



class sqlconn {
	const string server = "your_host:port";        //localhost:3306
	const string username = "your_username";
	const string password = "your_password";
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;

public:
	sqlconn() {

		try
		{
			driver = get_driver_instance();
			con = driver->connect(server, username, password);
		}
		catch (sql::SQLException e)
		{
			cout << "Could not connect to server. Error message: " << e.what() << endl;
			system("pause");
			exit(1);
		}

	 }

	int getPin(int id, char userType) {
		int pin;
		string s(1, userType);
		try {
			pstmt = con->prepareStatement("SELECT user_pin FROM school_database.user-table WHERE ((user_id=?) AND (user_type=?))");
			pstmt->setInt(1, id);
			pstmt->setString(2, s);
			res = pstmt->executeQuery();
			res->first();
			pin=res->getInt("user_pin");
			pstmt->close();
			return pin;

		}
		catch (sql::SQLException e)
		{
			cout << "Cannot proceede : Your User ID may not valid. Please enter correct ID" << endl;
			return 0;
		}
	}

	 void showRegStudent() {
		 cout 
			 << "-------------------------------------\n" 

			 
			 << " " << left << setw(12) << "Student id"
			 << left << setw(20) << "Student name"
			 << left << setw(20) << "email" << endl;

		 stmt = con->createStatement();
		 res = stmt->executeQuery("SELECT student-id,student-name,email FROM  school_database.student-table ORDER BY student-id ASC ");
		 while (res->next()) {
			 cout 
				 << " "<< left << setw(12) << res->getInt(1)
				 << left << setw(20)<< res->getString("student-name")
				 << left << setw(20)<< res->getString("email") << endl;
		 }
		 cout 
			 << "-------------------------------------" << endl;
		 

	 }

	 void showRegCouStudent() {

		 int code;
		 cout 
			 << "-------------------------------------\n"
			<< "Enter Corse Code : ";
		 cin >> code;
		 try {
			 stmt = con->createStatement();
			 pstmt = con->prepareStatement("SELECT student-id , student-name FROM school_database.student&course, school_database.student-table WHERE ((sid=student-id) AND (c_code=?))");
			 pstmt->setInt(1, code);
			 res = pstmt->executeQuery();
			 cout << "student id\t student Name" << endl;

			 while (res->next()) {
				 cout << "  " << res->getInt(1) << "\t\t"; 

				 cout << "  " << res->getString("student-name") << "" << endl;
			 }
			 cout << endl;
			 pstmt->close();
		 }
		 catch (sql::SQLException e)
		 {
			 cout << "Cannot proceede ...\n"
				 << "Check the course code is correct\n"
				 << "Check whether the inputs are digits" << endl;
		 }
	 }

	 void showStaffMembers() {
		 cout
			 << "-------------------------------------\n"


			 << " " << left << setw(12) << "Staff id"
			 << left << setw(20) << "User name"
			 << left << setw(30) << "email" 
			 << left << setw(20) << "post" << endl;

		 stmt = con->createStatement();
		 res = stmt->executeQuery("SELECT user_id,name,email,post FROM  school_database.staff-table ORDER BY user_id ASC ");						
		 while (res->next()) {
			 cout
				 << " " << left << setw(12) << res->getInt(1)
				 << left << setw(20) << res->getString("name")
				 << left << setw(30) << res->getString("email")
				 << left << setw(20) << res->getString("post") << endl;
		 }
		 cout
			 << "-------------------------------------" << endl;


	 }

	 void showCourses() {
		 cout
			 << "-------------------------------------\n"

			 << "Course Code\t Course Name" << endl;

		 stmt = con->createStatement();
		 res = stmt->executeQuery("SELECT course-code,course-name FROM  school_database.course-table ORDER BY course-code ASC ");
		 while (res->next()) {
			 cout << "  " << res->getInt(1) << "\t\t"; 

			 cout << "  " << res->getString("course-name") << endl;
		 }
		 cout
			 << "-------------------------------------" << endl;


	 }

	 void showProfile(int no) {
		 cout << "---------Profile-----------" << endl;
		 int id = no;

		 pstmt = con->prepareStatement("SELECT student-id,student-name,email FROM  school_database.student-table WHERE student-id=?");
		 pstmt->setInt(1, id);
		 res = pstmt->executeQuery();

		 while (res->next()) {

			 cout << "Student ID \t: " << res->getString("student-id") << endl;
			 cout << "Name \t\t: " << res->getString("student-name") << endl;
			 cout << "E-mail\t\t: " << res->getString("email") << endl;
		 }
		 cout << endl;
		 pstmt->close();

	 }

	 void insertStudent() {
		 std::string name,email;
		 int id,pin;
		 cout
			 << "-------------------------------------\n"
			 << "Enter Student ID : ";
		 cin >> id;
		 cin.ignore();				//ignore new line after call cin
		 cout << "Enter Student Name : ";
		 std::getline(cin, name);
		 cout << "Enter Student Pin : ";
		 cin >> pin;
		 cout << "Enter Student email : ";
		 cin >> email;
		 cout << name;

		 try{
		 
		 pstmt = con->prepareStatement("INSERT INTO school_database.user-table VALUES(?,?,?)");
		 pstmt->setInt(1, id);
		 pstmt->setInt(2, pin);
		 pstmt->setString(3, "s");
		 pstmt->execute(); 
		 pstmt->close();

		 pstmt = con->prepareStatement("INSERT INTO school_database.student-table VALUES(?,?,?)");
		 pstmt->setInt(1, id);
		 pstmt->setString(2, name);
		 pstmt->setString(3, email);
		 pstmt->execute();
		 pstmt->close();

		 cout
			 << "Student added successfully\n"
			 << "-------------------------------------" << endl;
		 }
		 catch (sql::SQLException e)
		 {
			 cout << "Cannot proceede ...\n" 
				 << "Check whether Student ID already exsist\n" 
				 <<"Check whether the data types are suitable" << endl;
		 }
	 }

	 void insertStaffMember() {
		 string name, email,position;
		 char post;
		 int id, pin;
		 cout
			 << "-------------------------------------\n"
			 << "Enter post of member : \n"
			 <<"  a-Administator\n"
			 <<"  m-manager\n"
			 <<"  c-Academic staff\n\n"
			 << "Enter post of member : ";
		 cin >> post;
		 switch (post)
		 {
		 case 'a': position = "Admin"; break;
		 case 'm': position = "Manager"; break;
		 case 'c': position = "Academic"; break;
		 default:cout << "Invalid input";
			 break;
		 }
		 if (post == 'a' || post == 'm' || post == 'c') {
			
			 cout << "Enter User ID : ";
			 cin >> id;
			 cin.ignore();
			 cout << "Enter name of staff mamber (dont use space) : ";
			 std::getline(cin, name);
			 cout << "Enter email : ";
			 cin >> email;
			 cout << "Enter user Pin : ";
			 cin >> pin;
			 string s(1, post);

			 try {

				 pstmt = con->prepareStatement("INSERT INTO school_database.user-table VALUES(?,?,?)");
				 pstmt->setInt(1, id);
				 pstmt->setInt(2, pin);
				 pstmt->setString(3,s);
				 pstmt->execute();
				 pstmt->close();

				 pstmt = con->prepareStatement("INSERT INTO school_database.staff-table VALUES(?,?,?,?)");
				 pstmt->setInt(1, id);
				 pstmt->setString(2, name);
				 pstmt->setString(3, email);
				 pstmt->setString(4, position);
				 pstmt->execute();
				 pstmt->close();

				 cout
					 << "\nStaff added successfully\n"
					 << "-------------------------------------" << endl;
			 }
			 catch (sql::SQLException e)
			 {
				 cout << "Cannot proceede ...\n"
					 << "Check whether Student ID already exsist\n"
					 << "Check whether the data types are suitable" << endl;
			 }
		 }
		 else { cout << "Enter correct letter for the post" << endl; }
	 }

	 void removeStudent() {
		 
		 int id;
		 cout 
			 << "-------------------------------------\n" 
			 << "Enter Student ID : ";
		 cin >> id;
		 
		 try{
			pstmt = con->prepareStatement("DELETE FROM school_database.user-table WHERE (user_id = ?)");

			pstmt->setInt(1, id);
			pstmt->execute();
			pstmt->close();

			pstmt = con->prepareStatement("DELETE FROM school_database.student-table WHERE (student-id = ?)");

			pstmt->setInt(1, id);
			pstmt->execute();
			pstmt->close();

			cout << "The Student removed."
				<< "-------------------------------------" << endl;


		 
		 }
		 catch (sql::SQLException e)
		 {
			 cout << "Cannot proceede : Some Errors occured "<< endl;
		 }
	 }

	 void createCourse() {
		 string courseN;
		 int cid;

		 
		 cout
			 << "-------------------------------------" << endl;
		 cin.ignore();
	     cout<< "Enter Course Name \t: ";
		 std::getline(cin, courseN);
		 cout << "Enter Course code (enter digits only)\t: ";
		 cin >> cid;
		 try {
			 pstmt = con->prepareStatement("INSERT INTO school_database.course-table VALUES(?,?)");
			 pstmt->setInt(1, cid);
			 pstmt->setString(2, courseN);
			 pstmt->execute();
			 pstmt->close();
			 cout << "Successfuly created.\n" 
			 << "-------------------------------------" << endl;

		 }
		 catch (sql::SQLException e)
		 {
			 cout << "Cannot proceede : \n"
				 <<"Check the course is already exsist\n"
				 <<"Check entered details are in correct format." << endl;
		 }
	 }

	 void deleteCourse() {
		 int cid;
		 cout 
			 << "-------------------------------------"

			 << "Enter Course code : ";
		 cin >> cid;
		 try{
		 pstmt = con->prepareStatement("DELETE FROM school_database.course-table WHERE (course-code = ?)");
		 pstmt->setInt(1, cid);
		 pstmt->execute();
		 pstmt->close();
		 cout<<"Course deleted"
			 << "-------------------------------------" << endl;


		 }
		 catch (sql::SQLException e)
		 {
			 cout << "Cannot proceede : " << e.what() << endl;
		 }
	 }

	 void selectCourse(int sid) {
		 
		 int id,cid;
		 showCourses();
		 id = sid;
		 cout << "Enter the Course Code : ";
		 cin >> cid;
		try{
		 pstmt = con->prepareStatement("INSERT INTO school_database.student&course VALUES(?,?)");
		 pstmt->setInt(1, id);
		 pstmt->setInt(2, cid);
		 pstmt->execute();
		 pstmt->close();

		 cout << "registration to course is succsessfull" << endl;
		}
		catch (sql::SQLException e)
		{
			cout << "Cannot proceede : Error occured\n"
				<<"You may already entered to the course or\n"
				<<"the course code is not valid" << endl;
		}
	 }

	 void changeSecrityPin() {
		 int id, pinNew, pinOld;
		 cout
			 << "-------------------------------------\n"
			 << "Enter user ID : ";
		 cin >> id;
		 cout << "Enter new Pin : ";
		 cin >> pinNew;

		 try {

			 pstmt = con->prepareStatement("UPDATE school_database.user-table SET user_pin = ? WHERE (user_id = ?);");
			 pstmt->setInt(1, pinNew);
			 pstmt->setInt(2, id);
			 pstmt->execute();
			 pstmt->close();

			 cout
				 << "Security pin was changed\n"
				 << "-------------------------------------" << endl;
		 }
		 catch (sql::SQLException e)
		 {
			 cout << "Cannot proceede ...\n"
				 << "Check whether user ID not valid\n"
				 << "Check whether the data types are suitable" << endl;
		 }
	 }
	
};
