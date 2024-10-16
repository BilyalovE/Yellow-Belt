#include "date.h"

string ParseEvent(istream& is) {
    // Поток is уже не имеет команды Add и дату.
    // Изначально поток был, к примеру, Add 2017-01-01 Holiday
    // А после функции main от стал таким: _Holiday
    string half_event, all_event;
    is >> all_event;
    getline(is, half_event);
    all_event += half_event;
    return all_event;
}


Date::Date() { }
Date::Date(const int year, const int month, const int day) {
    if (year >= 0 && year <= 9999){
        if(month > 0 && month <= 12){
            if (day > 0 && day <= 31){
                year_ = year;
                month_ = month;
                day_ = day;
            }
            else{
                throw logic_error("Day value is invalid: " + to_string(day)); }
        }
        else {
            throw logic_error("Month value is invalid: " + to_string(month)); }
    }
    else {
        throw logic_error("Year value is invalid: " + to_string(year)); }
}

int Date::GetYear() const noexcept { return year_; }
int Date::GetMonth() const noexcept { return month_; }
int Date::GetDay() const noexcept { return day_; }

int SubParseDate(stringstream& date, const string& type_date){
    const stringstream& err = date;
    string half_date_with_sign = "";
    int half_date = 0;
    if (type_date == "month" || type_date == "day"){
        // извлекаю первый -
        char chr = ' ';
        date >> chr;
        if(chr != '-'){
            throw std::logic_error("Wrong date format: " + err.str());
        }
    }
    
    // Проверяем, является ли первый символ '-'
    if (date.peek() == '-') {
        // Считываем дату, включая знак '-'
        date.ignore();
        if (isdigit(date.peek()) || date.peek() == '0'){
            date >> half_date;
            // Здесь дата будет равна "-дата"
            half_date_with_sign = '-' + to_string(half_date);
        }
    }
    else if (isdigit(date.peek())) {
        // Если дата положительная
        date >> half_date;
        half_date_with_sign = to_string(half_date);
    }
    // Проверяем, что дата был считан корректно
    if (half_date_with_sign.empty()) {
        throw std::logic_error("Wrong date format: " + err.str());
    }
    
    return stoi(half_date_with_sign);
}

Date ParseDate(istream& is){
    string str = "";
    is>>str;
    stringstream date(str);
    int year = 0, month = 0, day = 0;
        year = SubParseDate(date, "year");
        month = SubParseDate(date, "month");
        day = SubParseDate(date, "day");

    return {year, month, day};
}

ostream& operator << (std::ostream& os, const Date& date)
{
    os << setw(4) << setfill('0') << date.GetYear() << '-';
    os << setw(2) << setfill('0') << date.GetMonth() << '-';
    os << setw(2) << setfill('0') << date.GetDay();
    return os;
}

bool operator<(const Date& lhs, const Date& rhs) noexcept {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
           make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator<=(const Date& lhs, const Date& rhs) noexcept {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <=
           make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>(const Date& lhs, const Date& rhs) noexcept {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >
           make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>=(const Date& lhs, const Date& rhs) noexcept {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >=
           make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator != (const Date& lhs, const Date& rhs) noexcept {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) !=
           std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator == (const Date& lhs, const Date& rhs) noexcept {
    return !(lhs != rhs);
}
