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

string Date::str() const { return to_string(year) + '-' + to_string(month) + '-' + to_string(day); }

Date ParseDate(istream& is)
{
    Date d;
    is >> d;
    return d;
}

istream& operator>>(istream& ist, Date& date)
{
    if (ist) {
        string DATE;
        ist >> DATE;
        stringstream ss(DATE);
        int yy, mm, dd;
        char ch0 = '.', ch1 = '.';
        ss >> yy >> ch0 >> mm >> ch1 >> dd;
        if (ch0 != '-' || ch1 != '-' || !ss.eof())
            throw runtime_error("Wrong date format: " + DATE);
        stringstream ssc(DATE);
        int y, m, d;
        ssc >> y >> ch0 >> m >> ch1 >> d;
        if (y != yy || m != mm || d != dd)
            throw runtime_error("Wrong date format: " + DATE);
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
