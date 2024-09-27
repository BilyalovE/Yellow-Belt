//
//  main.cpp
//  Task 2
//
//  Created by Билялов Эльдар on 27.09.2024.
//

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border){
    //auto it = elements.upper_bound(border);
    vector<T> res;
    //copy_backward(begin(elements), it, end(res));
    copy_if(begin(elements),
            end(elements),
            inserter(res, end(res)),
            [border](const auto& e){
                return e > border;
            });
    sort(begin(res), end(res));
    return  res;
}


int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
  }
  cout << endl;
  
  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}
