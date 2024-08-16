#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		// добавить факт изменения имени на first_name в год year
		map_first_name[year] = first_name;
		list_years.push_back(year);
	}
	void ChangeLastName(int year, const string&last_name) {
		// добавить факт изменения фамилии на last_name в год year
		map_last_name[year] = last_name;
		list_years.push_back(year);
	}
	string GetFullName(int year) {
		// получить имя и фамилию по состоянию на конец года year
		list_years.push_back(year);
		sort(begin(list_years), end(list_years));
		int temp_year;
		for (int i = 0; i < list_years.size(); ++i) {
			if (list_years[i] == year) {
				temp_year = i;
				break;
			}
		}
		for (int i = 0; i <= temp_year; ++i) {
			if(map_first_name.count(list_years[i])){
				index_first_name = i;
			}
			if (map_last_name.count(list_years[i])) {
				index_last_name = i;
			}
		}
		if (index_first_name == -1 && index_last_name == -1) {
			return "Incognito";
		}
		else if (index_last_name == -1) {
			return map_first_name[list_years[index_first_name]] + " with unknown last name";
		}
		else if (index_first_name == -1) {
			return map_last_name[list_years[index_last_name]] + " with unknown first name";
		}
		else {
			return map_first_name[list_years[index_first_name]] + " " + map_last_name[list_years[index_last_name]];
		}
	}

private:
	map <int, string> map_first_name;
	map <int, string> map_last_name;
	vector <int> list_years;
	int index_first_name = -1, index_last_name = -1;
};


void test1(){
	Person person;
	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	string os1, os2;
	for (int year : {1900, 1965, 1990}) {
			os1 += person.GetFullName(year) + " ";
		}
	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
			os1 += person.GetFullName(year) + " ";
		}
	person.ChangeLastName(1968, "Volkova");
	os2 = "Incognito Polina with unknown last name Polina Sergeeva Polina Sergeeva Appolinaria Sergeeva Polina Volkova Appolinaria Volkova ";
	for (int year : {1969, 1970}) {
		os1 += person.GetFullName(year) + " ";
	}
	AssertEqual(os1, os2, "hint");

}

int main() {
  TestRunner runner;
  runner.RunTest(test1, "test");
  return 0;
}
