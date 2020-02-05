#include "database.h"
using namespace std;

void Database::Add(const Date& date, const string& event)
{
    auto found = it_db.equal_range(date);
    if (found.first != it_db.end()) {
        for (auto it = found.first; it != found.second; ++it)
            if (it->second == event)
                return;
    }
    it_db.emplace(date, event);
    //db[date].push_back(event);
}

int Database::RemoveIf(function<bool(Date, string)> foo)
{
    int size = 0;
    for (auto it = it_db.begin(); it != it_db.end();) {
        if (foo(it->first, it->second)) {
            it = it_db.erase(it);
            ++size;
        } else
            ++it;
    }
    return size;
}

vector<string> Database::FindIf(function<bool(Date, string)> foo) const
{
    vector<string> toPrint;
    for (auto it = it_db.begin(); it != it_db.end(); ++it) {
        if (foo(it->first, it->second))
            toPrint.push_back(it->first.str() + ' ' + it->second);
    }
    return toPrint;
}

string Database::Last(const Date& date) const
{
    auto begin = it_db.lower_bound(date);
    if (begin->first == date) {
        auto end = it_db.upper_bound(date);
        --end;
        return end->first.str() + ' ' + end->second;
    }
    if (begin->first != date) {
        if (begin == it_db.begin())
            throw invalid_argument(date.str());
        --begin;
    }
    if (begin == it_db.end())
        --begin;
    return begin->first.str() + ' ' + begin->second;
}

void Database::Print(ostream& ost) const
{
    for (auto it = it_db.begin(); it != it_db.end(); ++it)
        ost << it->first << ' ' << it->second << endl;
}
