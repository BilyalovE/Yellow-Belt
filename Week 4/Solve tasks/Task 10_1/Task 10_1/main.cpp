//
//  main.cpp
//  Task 10_1 Группировка строк по префиксу. Часть 2
//
//  Created by Билялов Эльдар on 28.09.2024.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end, const string& prefix)
{
    /*auto begin_it = lower_bound(range_begin, range_end, prefix);
    string new_prefix = prefix;
    new_prefix.back()++;
    auto end_it = upper_bound(range_begin, range_end, new_prefix);
    return make_pair(begin_it, end_it);*/
    auto itr = std::equal_range(range_begin, range_end, prefix,
            [&prefix](const std::string& x, const std::string& y)
            {
                return x.compare(0, prefix.length(), y.substr(0, prefix.length())) < 0;
            });
        return std::make_pair(itr.first, itr.second);
}

    

int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
  
  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;
  
  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;
  
  return 0;
}
