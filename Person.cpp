#include <time.h>
#include "stdafx.h"
#include <iostream>
#include "Person.h"
using std::cin;
using std::cout;
using std::endl;
#define SECONDS_IN_DAY 86400
#define DAY (charToInt(uI[0]) * 10 + charToInt(uI[1]))
#define MONTH (charToInt(uI[3]) * 10 + charToInt(uI[4]))
#define YEAR (charToInt(uI[6])*1000 + charToInt(uI[7])*100 + charToInt(uI[8])*10 + charToInt(uI[9]))
#define MAX_DAYS_IN_MONTH 31
static int daysinMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };//How many days in a month: Jan to Dec
//!MONTHS RANGE FROM 1 TO 12
void errorMessage(int);
//Convert char to int 
int userClass::charToInt(char ch) {
	return ch - '0';
}

//Validates if user input is valid and then assigns it to the userClass object
bool userClass::validate(string uI, int currentYear) {
	if (uI.length() < 8) {
		errorMessage(0);
		return 0;
	}//Check if string is too small.Prevents out of bounds read
	if (uI[0] == '\0') {
		errorMessage(0);
		return 0;
	}//Check if string is blank
	if (!((DAY>0) && (DAY <= MAX_DAYS_IN_MONTH))) {
		errorMessage(0);
		return 0;
	}//Check if DAY is possible
	if (!(uI[2] == '\/')) {
		errorMessage(0);
		return 0;
	}
	if (!((MONTH>0) && (MONTH <= 12))) {
		errorMessage(0);
		return 0;
	}//Check if MONTH is possible
	if (DAY>daysinMonth[MONTH - 1]) {
		errorMessage(1);
		return 0;
	}//Check if the days input are more than days in that month
	if (!(uI[5]) == '\/') {
		errorMessage(0);
		return 0;
	}
	if (!(YEAR <= currentYear)) {
		errorMessage(0);
		return 0;
	}//Check if YEAR is possible
	else {
		this->uID = DAY;
		this->uIM = MONTH;
		this->uIY = YEAR;
		return 1;
	}
}

//Calculates the day difference between users input and the current date
void userClass::calculateDifference(struct tm nowDate) {
	//Conveting the current date to Julian Day Number 
	size_t now = julianDay(nowDate.tm_year, nowDate.tm_mon, nowDate.tm_mday);
	//Converting the user date to Julian Day Number
	size_t end = julianDay(this->uIY, this->uIM, this->uID);
	this->DD = now - end;

}

//Initializer
bool userClass::setUserParameters(string uI, int currentYear, struct tm nowDate) {
	if (!validate(uI, currentYear)) {//First we validate the user input
		return 0;
	}
	calculateDifference(nowDate);	//Then we calculate the difference between input date and now
	return 1;
}

//Display stats in a similar way that timeanddate.com does
void userClass::displayStats() {
	long float years, months, days;
	years = floor(this->DD / 365);
	days = this->DD % 365;
	months = days / 30;
	days = (months - floor(months)) * 30;
	months = floor(months);
	cout << "> " << "You have been alive for " << years << " Years, " << months << " Months, " << (int)days << " days" << endl;
	cout << "Or " << endl;
	cout.imbue(std::locale(""));			//Prints numbers using seperator , or . depending on your system settings
	cout << "> " << this->DD << " days" << endl;
	cout << "Which can be converted to one of the units below:" << endl;
	cout << "> " << this->DD*SECONDS_IN_DAY << " seconds" << endl;
	cout << "> " << (this->DD*SECONDS_IN_DAY) / 60 << " minutes" << endl;
	cout << "> " << ((this->DD*SECONDS_IN_DAY) / 60) / 60 << " hours" << endl;
	cout << "> " << this->DD / 7 << " weeks";
	if (this->DD % 7 != 0) {
		cout << " and " << floor(this->DD % 7) << " days\n";
	}
	else {
		cout << "\n";
	}
}

//Converts a Gregorian calendar date to Julian Day Number
long int userClass::julianDay(unsigned int year, unsigned int month, unsigned int day) {
	int Y = year;
	int M = month;
	int D = day;
	//Formula to convert gregorian date to julian day number
	int JDN = ((1461 * (Y + 4800 + (M - 14) / 12)) / 4 + (367 * (M - 2 - 12 * ((M - 14) / 12))) / 12 - (3 * ((Y + 4900 + (M - 14) / 12) / 100)) / 4 + D - 32075);
	return JDN;
}

//Error message funtion - might be replaced with try catch blocks
void errorMessage(int msg) {
	switch (msg) {
	case 0:
		cout << "Invalid or wrongly formated input" << endl;
		break;
	case 1:
		cout << "Invalid DD input\n";
		break;
	}
}





