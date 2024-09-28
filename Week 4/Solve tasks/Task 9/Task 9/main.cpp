//
//  main.cpp
//  Task 9 Имена и фамилии — 4
//
//  Created by Билялов Эльдар on 27.09.2024.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
using namespace std;



string GetHalfName(const map<int, string>& map_half_name, int year){
    auto it_half_name = map_half_name.upper_bound(year);
    if(it_half_name == map_half_name.begin()) {
        // Если все записи позже указанного года
        return "";
    }
    else {
        // Если итератор указывает на элемент с годом, большим чем year
        return prev(it_half_name)->second;
    }
}


class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    // добавить факт изменения имени на first_name в год year
      map_FirstName[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    // добавить факт изменения фамилии на last_name в год year
      map_LastName[year] = last_name;
  }
  string GetFullName(int year) {
    // получить имя и фамилию по состоянию на конец года year
    // с помощью двоичного поиска
      string full_name;
      string first_name = GetHalfName(map_FirstName, year);
      string last_name = GetHalfName(map_LastName, year);
      if (first_name == ""){
          first_name = "with unknown first name";
      }
      if(last_name == ""){
          last_name = "with unknown last name";
      }
      full_name = first_name + " " + last_name;
      if(full_name == "with unknown first name with unknown last name"){
          full_name = "Incognito";
      }
      return full_name;
  }
private:
    map<int, string> map_FirstName, map_LastName;
};

int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
}
