#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>

using namespace std;

class Date {
public:
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    Date() {}
    Date(int yy, int mm, int dd)
    {
        if (mm < 1 || mm > 12)
            throw runtime_error("Month value is invalid: " + to_string(mm));
        if (dd < 1 || dd > 31)
            throw runtime_error("Day value is invalid: " + to_string(dd));
        year = yy;
        month = mm;
        day = dd;
    }

private:
    int year;
    int month;
    int day;
};

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

//bool operator<(const Date& lhs, const Date& rhs)
//{
//    return tie(lhs.getYear(), lhs.getMonth(), lhs.getDay()) < tie(rhs.getYear(), rhs.getMonth(), rhs.getDay());
//}

bool operator==(const Date& lhs, const Date& rhs)
{
    return make_tuple(lhs.getYear(), lhs.getMonth(), lhs.getDay()) == make_tuple(rhs.getYear(), rhs.getMonth(), rhs.getDay());
}

bool operator>(const Date& lhs, const Date& rhs)
{
    return make_tuple(lhs.getYear(), lhs.getMonth(), lhs.getDay()) > make_tuple(rhs.getYear(), rhs.getMonth(), rhs.getDay());
}

void PrintSet(const Date& date, const set<string> events)
{
    for (const auto& item : events)
        cout << date << " " << item << endl;
}

class Database {
public:
    Database() {}
    void AddEvent(const Date& date, const string& event)
    {
        db[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event)
    {
        bool check = db[date].find(event) != db[date].end();
        if (check == true) {
            db[date].erase(db[date].find(event));
            return true;
        }
        return false;
    }
    int DeleteDate(const Date& date)
    {
        int events = db[date].size();
        db[date].clear();
        return events;
    }
    void Find(const Date& date)
    {
        for (auto& item : db[date])
            cout << item << endl;
    }
    void Print()
    {
        for (const auto& item : db)
            PrintSet(item.first, item.second);
    }

private:
    map<Date, set<string>> db;
};

int main()
{
    Database db;
    string command;
    while (getline(cin, command)) {
        try {
            stringstream ss(command);
            string order, event;
            Date date;
            ss >> order >> date >> event;
            if (order == "Add")
                db.AddEvent(date, event);
            else if (order == "Find")
                db.Find(date);
            else if (order == "Del" && event.size() > 0) {
                bool check = db.DeleteEvent(date, event);
                if (check == true)
                    cout << "Deleted successfully" << endl;
                else
                    cout << "Event not found" << endl;
            } else if (order == "Del") {
                int N = db.DeleteDate(date);
                cout << "Deleted " << N << " events" << endl;
            } else if (order == "Print")
                db.Print();
            else if (command.size() > 0)
                throw runtime_error("Unknown command: " + order);

        } catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}
