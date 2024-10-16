#include "database.h"

Database::Database(){}

Database::Database(const Date& date, const string& event){
    db[date].insert(event);
    db_copy[date].push_back(event);
}

void Database::Add(const Date& date, const string& event) {
    db[date].insert(event);
    db_copy[date].push_back(event);
    
       
}

void Database::Print(ostream& cout) const {
    cout << db;
}

pair<Date, string> Database::Last(const Date& date) const{
    auto upper_it = upper_bound(db_copy.begin(), db_copy.end(), date,
        [](const Date& d, const std::pair<const Date, vector<string>>& p) {
            return  d < p.first;
        });
    if(upper_it == db_copy.begin()){
        throw invalid_argument("");
    }
    else{
        vector <string> list = prev(upper_it)->second;
        return make_pair(prev(upper_it)->first, *prev(list.end()));
    }
}

/*int Database::RemoveIf(function<bool(const Date&, const string&)> predicate) {
    int  removed_count = 0;
    map<Date, string::iterator> delete_db;
    for (const auto& d : db){
        auto date = d.first;
        auto events = d.second;
        auto p = [&date, &predicate](const string event){
            return predicate(date, event);
        };
        auto it = stable_partition(events.begin(), events.end(), p);
        delete_db[date] = it;
    }
    for (const auto& d : delete_db){
        size_t initial_size_events = db.at(d.first).size();
        auto it_begin = db.at(d.first).begin();
        auto it_end = d.second;
        db.at(d.first).erase(it_begin, it_end);
        size_t current_size_events = db.at(d.first).size();
        removed_count += initial_size_events - current_size_events;
    }
    return removed_count;
}*/

int Database::RemoveIf(function<bool(const Date&, const string&)> predicate) {
    int removed_count = 0;
    map<Date, vector<string>::iterator> delete_db;

    // Проходим по каждой дате и связанным с ней событиям
    for (auto& [date, events] : db_copy) {
        const Date current_date = date; // Явно создаём локальную копию даты

        // Лямбда для проверки события на соответствие предикату
        auto it = stable_partition(events.begin(), events.end(),
                                   [&current_date, &predicate](const string& event) {
                                       return !predicate(current_date, event);
                                   });

        // Если есть события для удаления, сохраняем итератор на начало удаляемых
        if (it != events.end()) {
            delete_db[date] = it; // Сохраняем итератор на первый элемент, который нужно удалить
        }
    }

    // Удаляем события, которые удовлетворяют предикату
    for (const auto& [date, it_events] : delete_db) {
        size_t initial_size = db[date].size();
        // Удаляем события начиная с итератора it_events до конца списка событий
        db_copy[date].erase(it_events, db_copy[date].end());
        db[date].clear();
        copy(db_copy[date].begin(), db_copy[date].end(), inserter(db[date], db[date].end()));
        size_t current_size = db[date].size();
        // Увеличиваем счётчик удалённых событий
        removed_count += initial_size - current_size;

        // Если для данной даты больше нет событий, удаляем дату из базы
        if (db[date].empty()) {
            db.erase(date);
            db_copy.erase(date);
        }
    }

    return removed_count;
}




vector<pair<Date, string>> Database::FindIf(function<bool(const Date&, const string&)> predicate) const {
    vector<pair<Date, string>> found_history;
    map<Date, set<string>> history_find;
    for (const auto& [date, events] : db){
        for (const auto& event: events){
            if(predicate(date, event)){
                found_history.push_back(make_pair(date, event));
            }
        }
    }
    return found_history;
}

map<Date, set<string>> Database::GetBd() const{
    return db;
};
