//
//  main.cpp
//  Task 10 Группировка строк по префиксу  Часть 1
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
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin,
                                        RandomIt range_end,
                                        char prefix)
{
    auto begin_it = lower_bound(range_begin, range_end, string(1, prefix));
    auto end_it = upper_bound(range_begin, range_end, string(1, static_cast<char>(prefix+1)));
    return make_pair(begin_it, end_it);
}




int main() {
  const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};
  
  const auto m_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
  for (auto it = m_result.first; it != m_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  
  const auto p_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
  cout << (p_result.first - begin(sorted_strings)) << " " <<
      (p_result.second - begin(sorted_strings)) << endl;
  
  const auto z_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
  cout << (z_result.first - begin(sorted_strings)) << " " <<
      (z_result.second - begin(sorted_strings)) << endl;
  
  return 0;
}
