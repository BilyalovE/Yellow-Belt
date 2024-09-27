//
//  main.cpp
//  Task 6
//
//  Created by Билялов Эльдар on 27.09.2024.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

void PrintStats(vector<Person> persons){
    // Median age
    cout << "Median age = "
    << ComputeMedianAge(persons.begin(), persons.end()) << endl;
    // Median age for females
    auto range_end_female = partition(persons.begin(),
                         persons.end(),
                         [](const auto& person){
                            return person.gender == Gender::FEMALE;
                        }
    );
    cout << "Median age for females = "
         << ComputeMedianAge(persons.begin(), range_end_female) << endl;
    // Median age for males
    cout << "Median age for males = "
         << ComputeMedianAge(range_end_female, persons.end()) << endl;
    // Median age for employed females
    auto range_end_female_emp = partition(persons.begin(),
                         range_end_female,
                         [](const auto& person){
                            return person.is_employed == 1;
                        }
    );
    cout << "Median age for employed females = "
         << ComputeMedianAge(persons.begin(), range_end_female_emp) << endl;
    // Median age for unemployed females
    cout << "Median age for unemployed females = "
         << ComputeMedianAge(range_end_female_emp, range_end_female) << endl;
    
    // Median age for employed males
    auto range_end_male_emp = partition(range_end_female,
                                        persons.end(),
                         [](const auto& person){
                            return person.is_employed == 1;
                        }
    );
    cout << "Median age for employed males = "
         << ComputeMedianAge(range_end_female, range_end_male_emp) << endl;
    // Median age for unemployed males
    cout << "Median age for unemployed males = "
         << ComputeMedianAge(range_end_male_emp, persons.end()) << endl;
}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}
