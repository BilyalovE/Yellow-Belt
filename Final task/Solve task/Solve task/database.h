#pragma once
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <utility>
#include <set>
#include <iostream>
#include "date.h"
#include <algorithm>

using namespace std;

template <typename K, typename V>
ostream& operator<<(ostream& os, const map<K, set<V>> & m);
class Database{
public:
    Database();
    Database(const Date& date, const string& event);
    void Add(const Date& date, const string& event);
    void Print(ostream& cout) const;
    pair<Date, string> Last(const Date& date)  const;
    int RemoveIf(function<bool(const Date&, const string&)> predicate);
    vector<pair<Date, string>> FindIf(function<bool(const Date&, const string&)> predicate) const;
    map<Date, set<string>> GetBd() const;
private:
    map<Date, set<string>> db;
    map<Date, vector<string>> db_copy;
};


template <typename K, typename V>
ostream& operator<<(ostream& os, const map<K, set<V>> & m) {
    bool flag = 1;
    for(const auto& i : m){
        for (const auto& event : i.second){
            if (!flag){
                os << '\n';
            }
            flag = 0;
            os << i.first << " " << event;
        }
    }
    return os;
}

template <typename K, typename V>
ostream& operator<<(ostream& os, const pair<K, V> & m) {
    os << m.first << " " << m.second;
    return os;
}

