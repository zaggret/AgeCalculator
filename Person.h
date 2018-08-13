#pragma once
#include "stdafx.h"
//localtime_s starts from 1900
#include <string>
using std::string;

class userClass {
private:
	int uID;		//Holds user input Days
	int uIM;		//Holds user input Months
	int uIY;		//Holds user input Years
	size_t DD;		//Holds how many days user has been alive 
public:
	userClass() {
		uID = NULL;
		uIM = NULL;
		uIY = NULL;
		DD = NULL;
	}
	~userClass() {}
	int charToInt(char ch);
	bool validate(string uI, int currentYear);
	void calculateDifference(struct tm nowDate);
	bool setUserParameters(string uI, int currentYear, struct tm nowDate);
	void displayStats();
	long int julianDay(unsigned int year, unsigned int month, unsigned int day);
};
