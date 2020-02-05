#include "date.h"
#include <exception>
#include <iomanip>
#include <sstream>
#include <string>
#include <tuple>
using namespace std;

Date::Date(int yy, int mm, int dd)
{
    if (mm < 1 || mm > 12)
        throw runtime_error("Month value is invalid: " + to_string(mm));
    if (dd < 1 || dd > 31)
        throw runtime_error("Day value is invalid: " + to_string(dd));
    year = yy;
    month = mm;
    day = dd;
}

string Date::str() const
{
    ostringstream ost;
    ost << setw(4) << setfill('0') << year << '-'
        << setw(2) << month << '-' << setw(2) << day;
    return ost.str();
}

Date ParseDate(istream& is)
{
    Date d;
    is >> d;
    return d;
}

int GetInt(istream& ist)
{
    if (ist) {
        char ch;
        ist.get(ch);
        if (!isdigit(ch))
            throw runtime_error("Not a digit: " + to_string(ch));
        ist.unget();
        int digit;
        ist >> digit;
        return digit;
    } else
        throw runtime_error("Unexpected end of stream");
}

istream& operator>>(istream& ist, Date& date)
{
    if (ist) {
        char ch = '.', ch0 = '.', ch1 = '.';
        while (ist.peek() == ' ')
            ist.get(ch);
        int yy = GetInt(ist);
        ist.get(ch0);
        int mm = GetInt(ist);
        ist.get(ch1);
        int dd = GetInt(ist);
        if (ch0 != '-' || ch1 != '-')
            throw runtime_error("Wrong date format: " + to_string(yy) + ch0 + to_string(mm) + ' ' + to_string(dd));
        date = { yy, mm, dd };
    }
    return ist;
}

ostream& operator<<(ostream& ost, const Date& date)
{
    ost << setw(4) << setfill('0') << date.getYear() << '-'
        << setw(2) << date.getMonth() << '-'
        << setw(2) << date.getDay();
    return ost;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    return make_tuple(lhs.getYear(), lhs.getMonth(), lhs.getDay()) < make_tuple(rhs.getYear(), rhs.getMonth(), rhs.getDay());
}
bool operator<=(const Date& lhs, const Date& rhs)
{
    return make_tuple(lhs.getYear(), lhs.getMonth(), lhs.getDay()) <= make_tuple(rhs.getYear(), rhs.getMonth(), rhs.getDay());
}
bool operator==(const Date& lhs, const Date& rhs)
{
    return make_tuple(lhs.getYear(), lhs.getMonth(), lhs.getDay()) == make_tuple(rhs.getYear(), rhs.getMonth(), rhs.getDay());
}
bool operator!=(const Date& lhs, const Date& rhs)
{
    return !(lhs == rhs);
}
bool operator>(const Date& lhs, const Date& rhs)
{
    return make_tuple(lhs.getYear(), lhs.getMonth(), lhs.getDay()) > make_tuple(rhs.getYear(), rhs.getMonth(), rhs.getDay());
}
bool operator>=(const Date& lhs, const Date& rhs)
{
    return make_tuple(lhs.getYear(), lhs.getMonth(), lhs.getDay()) >= make_tuple(rhs.getYear(), rhs.getMonth(), rhs.getDay());
}
