/*A simple app where the user enters a birthday(or any date) and we calculate
the time interval between the users birthday and current day*/
/*Created by alex charalampidis for fun and practice*/

#include "stdafx.h"
#include "Person.h"
#include <time.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
#include <ctime>
#ifdef __unix__ 
#error "Unix systems not supported"
#endif

int main()
{ 
	struct tm nowDate;								//Holds the current date struct
	time_t long_time = time(NULL);					//time_t object holds the seconds passed since epoch
	errno_t err = localtime_s(&nowDate, &long_time);//Converts the time_t object to structure tm
	nowDate.tm_mon += 1;							//Months are numbered from [1-12] for JAN to DEC
	nowDate.tm_year += 1900;						
	userClass user;
	cout << "---------------------------------------------------------------------\n"
		<< "Age Calculator by Alex Charalampidis.\t\t\t\t    |\n"
		<< "Calculates and displays the time span between your birthday and now.|\n"
		<<"For convenience 1 month = 30 days.\t\t\t\t    |\n"
		<<"---------------------------------------------------------------------"
		<< endl;
	string userInput = "\0";
	do{
		cout << "Please enter your birthday in the format DD/MM/YYYY: ";
		cin >> userInput;
	} while (!user.setUserParameters(userInput, nowDate.tm_year,nowDate));
	user.displayStats();
	system("PAUSE");
	return 0;
}