#include "database.h"
using namespace std;

void Database::Add(const Date& date, const string& event)
{
    auto found = find(db[date].begin(), db[date].end(), event);
    if (found == db[date].end())
        db[date].push_back(event);
}

int Database::RemoveIf(function<bool(Date, string)> foo)
{
    int size = 0;
    auto del = [foo, &size](const Date& date, vector<string>& vector_) {
        for (auto first = vector_.begin(); first != vector_.end();) {
            if (foo(date, *first)) {
                first = vector_.erase(first);
                ++size;
            } else
                first++;
        }
        if (vector_.empty())
            return true;
        return false;
    };
    auto last = stable_partition(db.begin(), db.end(), del);
    db.erase(db.begin(), last);
    return size;
}

//int Database::RemoveIf(function<bool(Date, string)> foo)
//{
//    int size = 0;
//    auto del = [foo, &size](const Date& date, vector<string>& vector_) {
//        vector<string> new_vector;
//        for (auto first = vector_.begin(); first != vector_.end(); first++)
//            if (!foo(date, *first)) {
//                new_vector.push_back(*first);
//                ++size;
//            }
//        if (new_vector != vector_) {
//            vector_ = new_vector;
//        }
//        if (vector_.empty())
//            return true;
//        return false;
//    };
//    auto last = stable_partition(db.begin(), db.end(), del);
//    db.erase(db.begin(), last);
//    return size;
//}

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
    //bool check = db.find(date) != db.end();
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
