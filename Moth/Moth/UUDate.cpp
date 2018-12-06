/*
* UUDate.cpp
*
* Version information
* Author: John McGlinchey
* Date: 19/10/2018
* Description: This file is the implementation file for the UUDate class and defines (implements) the functions of the class
*
* Copyright notice -
*/


#include "UUDate.h"
bool ValidDay(int day, int month, int year);
bool ValidMonth(int month);
bool ValidYear(int year);
bool LeapYear(int year);


UUDate::UUDate(){
	//Initialise the date to 01/01/2000
	//TODO - Add your implementation here
	SetDay(01);
	SetMonth(01);
	SetYear(2000);
}

UUDate::UUDate(int day, int month, int year) {
	//Initialise the date to user input or set input to a valid input if it fails 
	//TODO - Add your implementation here
	if (ValidYear(year) == true)
		year_ = year;
	else
		year_ = 2000;
	if (ValidMonth(month) == true)
		month_ = month;
	else
		month_ = 1;

	if (ValidDay(day, month_, year_) == true)
		day_ = day;
	else
		day_ = 1;
}

UUDate::UUDate(std::string date) {
	//Initialise the string date to user input or set input to a valid input if it fails
	//Allows for practically any date as long as it is in the d/m/y format
	//TODO - Add your implementation here
	std::string dayStr, monthStr, yearStr;
	int day = 0, month = 0, year = 0;
	int pos = 0, pos2 = 0;
	//Find the position of both / in the string
	pos = static_cast<int>(date.find('/'));
	pos2 = static_cast<int>(date.find_last_of('/'));
	//Day will be from point 0 until first /
	dayStr = date.substr(0, pos);
	//Month will be from position after first / until second /
	monthStr = date.substr(pos + 1, (pos2 - pos) - 1);
	//Year will be from second / to the end
	yearStr = date.substr(pos2 + 1, date.length() - pos2);

	//Parse ints from the day, month and year strings
	day = std::stoi(dayStr);
	month = std::stoi(monthStr);
	year = std::stoi(yearStr);

	//Validate the inputs
	if (ValidYear(year) == true)
		year_ = year;
	else
		year_ = 2000;
	if (ValidMonth(month) == true)
		month_ = month;
	else
		month_ = 1;

	if (ValidDay(day, month_, year_) == true)
		day_ = day;
	else
		day_ = 1;

}

void UUDate::IncrementDate() {
	//TODO - Add your implementation here
	//Inrement the date by 1 day each time the function is called
	int day = GetDay(), month = GetMonth(), year = GetYear();
	day++;
	if (month == 2) { //Deal with February
		if (LeapYear(year) == true) {
			if (day > 29) {
				day = 1;
				month++;
			}
			else { 
				SetDay(day);
			}
		}
		else {
			if (day > 28) {
				day = 1;
				month++;
			}
			else {
				SetDay(day);
			}
		}
	}
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		if (month == 12) { //Deal with 31 day months
			if (day > 31) {
				day = 1;
				month = 1;
				year++;
			}
			else {
				SetDay(day);
			}
		}
		else {
			if (day > 31) {
				day = 1;
				month++;
			}
			else {
				SetDay(day);
			}
		}
	}
	else { //Deal with the 30 day months
		if (day > 30) {
			day = 1;
			month++;
		}
		else {
			SetDay(day);
		}
	}

	SetDay(day);
	SetMonth(month);
	SetYear(year);
}

int UUDate::Between(UUDate date) {
	//Find the amount of days between two dates
	//TODO - Add your implementation here
	int daysbetween = 0;
	int tempDay, tempMonth, tempYear;
	//Finds which date is further in the future
	if (GetDate() > date.GetDate()) {
		//Set temp files as the incrememnt function will change the date of the variable
		tempDay = date.GetDay(); 
		tempMonth = date.GetMonth();
		tempYear = date.GetYear();
		do {
			date.IncrementDate();
			daysbetween++;
		} while (date.GetDate() != GetDate());
		//Set original date back to what it was
		date.SetDay(tempDay);
		date.SetMonth(tempMonth);
		date.SetYear(tempYear);
	}
	else {
		//Set temp files as the incrememnt function will change the date of the variable
		tempDay = GetDay();
		tempMonth = GetMonth();
		tempYear = GetYear();
		do {
			IncrementDate();
			daysbetween++;
		} while (GetDate() != date.GetDate());
		//Set original date back to what it was
		SetDay(tempDay);
		SetMonth(tempMonth);
		SetYear(tempYear);
	}

	//return daysbetween;
	
	return 1;
}

int UUDate::GetDay() const {
	//Returns the day
	//TODO - Add your implementation here
	return day_;
}

void UUDate::SetDay(int day) {
	//Sets the day if the input is valid
//TODO - Add your implementation here
	if (ValidDay(day, month_, year_) == true) {
		day_ = day;
	}
}

int UUDate::GetMonth() const {
	//Returns the month
	//TODO - Add your implementation here
	return month_;
}

void UUDate::SetMonth(int month) {
	//Sets the month if the input is valid
	//TODO - Add your implementation here
	if (ValidMonth(month) == true) {
		month_ = month;
	}
}

int UUDate::GetYear() const {
	//Returns the year
	//TODO - Add your implementation here
	return year_;
}

void UUDate::SetYear(int year) {
	//Sets the year if the input is valid
	//TODO - Add your implementation here
	if (ValidYear(year) == true) {
		year_ = year;
	}
}

std::string UUDate::GetDate() {
	//Returns the date in the format (d)d/(m)m/(yyy)y
	//TODO - Add your implementation here
	std::string date = "";
	std::stringstream out;

	out << "" << GetDay() << "/" << GetMonth() << "/" << GetYear();
	date = out.str();

	return date;
}

bool ValidDay(int day, int month, int year) {
	//Validates if the day input is allowed
	if (day > 0 && day <= 31) {
		if (month == 2) { //Deals with February
			if (LeapYear(year) == true)
				if (day <= 29)
					return true;
				else
					return false;
			else {
				if (day <= 28)
					return true;
				else
					return false;
			}
		}
		else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8
			|| month == 10 || month == 12) { //Deals with 31 day months
			if (day <= 31)
				return true;
			else
				return false;
		}
		else
			if (day <= 30)//Deals with 30 day months
				return true;
			else
				return false;
	}
	else
		return false;
}

bool ValidMonth(int month) {
	//Validates if the month input is allowed
	if (month > 0 && month <= 12)
		return true;
	else
		return false;
}

bool ValidYear(int year) {
	//Validates if the year input is allowed
	if (year > 0)
		return true;
	else
		return false;
}

bool LeapYear(int year) {
	//Calculates if the year is a leap year
	if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))
		return true;
	else
		return false;
}

