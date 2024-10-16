#pragma once
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include "token.h"
#include <sstream>
#include <tuple>
#include <memory>

using namespace std;

class Date{
public:
    Date(const int year, const int month, const int day);
    Date();
    int GetYear() const noexcept;
    int GetMonth() const noexcept ;
    int GetDay() const noexcept;
private:
    int year_;
    int month_;
    int day_;
};

int SubParseDate(stringstream& date, const string& type_date);
Date ParseDate(istream& is);

string ParseEvent(istream& is);

ostream& operator << (std::ostream& os, const Date& date);
bool operator < (const Date& lsh, const Date& rhs) noexcept;
bool operator <= (const Date& lsh, const Date& rhs) noexcept;
bool operator > (const Date& lsh, const Date& rhs) noexcept;
bool operator >= (const Date& lsh, const Date& rhs) noexcept;
bool operator != (const Date& lsh, const Date& rhs) noexcept;
bool operator == (const Date& lhs, const Date& rhs) noexcept;
