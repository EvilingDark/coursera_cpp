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

//int Database::RemoveIf(function<bool(Date, string)> foo)
//{
//    int size = 0;
//    for (auto it = db.begin(); it != db.end(); ++it)
//        for (auto str = it->second.begin(); str != it->second.end();) {
//            if (foo(it->first, *str)) {
//                ++size;
//                auto found = it_db.equal_range(it->first);
//                for (auto it_2 = found.first; it_2 != found.second;) {
//                    if (it_2->second == *str)
//                        it_2 = it_db.erase(it_2);
//                    else
//                        ++it_2;
//                }
//                str = it->second.erase(str);
//            } else
//                ++str;
//        }
//    for (auto first = db.begin(); first != db.end();) {
//        if (first->second.empty())
//            first = db.erase(first);
//        else
//            ++first;
//    }
//    return size;
//}

//int Database::RemoveIf(function<bool(Date, string)> foo)
//{
//    int size = 0;
//    for (auto& [date, vector_] : db) {
//        vector<string> strToDel;
//        for (auto& str : vector_)
//            if (foo(date, str)) {
//                strToDel.push_back(str);
//                ++size;
//            }
//        if (!strToDel.empty()) {
//            auto del = [&strToDel](const string& s) {
//                for (auto& str : strToDel)
//                    if (str == s)
//                        return true;
//                return false;
//            };
//            auto dbDel = remove_if(vector_.begin(), vector_.end(), del);
//            vector_.erase(dbDel, vector_.end());
//            auto found = it_db.equal_range(date);
//            for (auto it = found.first; it != found.second;)
//                for (auto& to_del : strToDel) {
//                    if (it->second == to_del)
//                        it = it_db.erase(it);
//                    else
//                        ++it;
//                }
//        }
//    }
//    for (auto first = db.begin(); first != db.end();) {
//        if (first->second.empty())
//            first = db.erase(first);
//        else
//            ++first;
//    }
//    return size;
//}

//int Database::RemoveIf(function<bool(Date, string)> foo)
//{
//    int size = 0;
//    for (auto itDB = db.begin(); itDB != db.end(); itDB++) {
//        //auto data = itDB->first;
//        //auto vector_ = itDB->second;
//        for (auto itVEC = itDB->second.begin(); itVEC != itDB->second.end();) {
//            if (foo(itDB->first, *itVEC)) {
//                itVEC = itDB->second.erase(itVEC);
//                ++size;
//                if (itDB->second.empty())
//                    itDB = db.erase(itDB);
//            } else
//                ++itVEC;
//        }
//    }
//    //    auto del = [](pair<Date, vector<string>>& p) {
//    //        return p.second.empty();
//    //    };
//    //    remove_if(db.begin(), db.end(), del);
//    //    db.erase(db.begin(), last);
//    return size;
//}

//int Database::RemoveIf(function<bool(Date, string)> foo)
//{
//    int size = 0;
//    auto del = [foo, &size](const Date& date, vector<string>& vector_) {
//        for (auto first = vector_.begin(); first != vector_.end();) {
//            if (foo(date, *first)) {
//                first = vector_.erase(first);
//                ++size;
//            } else
//                first++;
//        }
//        return vector_.size() == 0;
//    };
//    auto last = stable_partition(db.begin(), db.end(), del);
//    db.erase(db.begin(), last);
//    return size;
//}

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

//string Database::Last(const Date& date) const
//{
//    auto found = db.lower_bound(date);
//    if (found->first != date) {
//        if (found == db.begin())
//            throw invalid_argument(date.str());
//        --found;
//    }
//    if (found == db.end())
//        --found;
//    return found->first.str() + ' ' + found->second.back();
//}

void Database::Print(ostream& ost) const
{
    for (auto it = it_db.begin(); it != it_db.end(); ++it)
        ost << it->first << ' ' << it->second << endl;
}
