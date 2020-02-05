#ifndef DATABASE_H
#define DATABASE_H
#pragma once
#include "date.h"
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Database {
public:
    Database() {}
    void Add(const Date& date, const string& event);

    int RemoveIf(function<bool(Date, string)> foo);

    vector<string> FindIf(function<bool(Date, string)> foo) const;

    string Last(const Date& date) const;

    void Print(ostream& ost) const;

private:
    map<Date, vector<string>> db;
};

#endif // DATABASE_H
