#include "database.h"
using namespace std;

void Database::Add(const Date& date, const string& event)
{
    if (find(db[date].begin(), db[date].end(), event) == db[date].end())
        db[date].push_back(event);
}

int Database::RemoveIf(function<bool(Date, string)> foo)
{
    int size = 0;
    for (auto& [data, vector_] : db) {
        vector<string> strToDel;
        for (auto& str : vector_)
            if (foo(data, str)) {
                strToDel.push_back(str);
                ++size;
            }
        if (!strToDel.empty()) {
            auto del = [&strToDel](const string& s) {
                for (auto& str : strToDel)
                    if (str == s)
                        return true;
                return false;
            };
            auto itDel = remove_if(vector_.begin(), vector_.end(), del);
            vector_.erase(itDel, vector_.end());
        }
    }
    for (auto first = db.begin(); first != db.end();) {
        if (first->second.empty())
            first = db.erase(first);
        else
            ++first;
    }
    return size;
}

vector<string> Database::FindIf(function<bool(Date, string)> foo) const
{
    vector<string> toPrint;
    for (const auto& vector_ : db)
        for (const auto& item : vector_.second)
            if (foo(vector_.first, item))
                toPrint.push_back(vector_.first.str() + ' ' + item);
    return toPrint;
}

string Database::Last(const Date& date) const
{
    auto found = db.lower_bound(date);
    if (found->first != date) {
        if (found == db.begin())
            throw invalid_argument(date.str());
        --found;
    }
    if (found == db.end())
        --found;
    return found->first.str() + ' ' + found->second.back();
}

void Database::Print(ostream& ost) const
{
    for (const auto& vector_ : db)
        for (const auto& item : vector_.second)
            ost << vector_.first << " " << item << endl;
}
