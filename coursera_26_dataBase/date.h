#ifndef DATE_H
#define DATE_H

#pragma once
#include <iostream>
using namespace std;

class Date {
public:
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    Date() {}
    Date(int yy, int mm, int dd);
    string str() const;

private:
    int year = 0;
    int month = 0;
    int day = 0;
};

Date ParseDate(istream& is);

istream& operator>>(istream& ist, Date& date);

ostream& operator<<(ostream& ost, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

#endif // DATE_H
