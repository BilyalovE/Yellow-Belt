//
//  main.cpp
//  Task 8 Поиск ближайшего элемента
//
//  Created by Билялов Эльдар on 27.09.2024.
//

#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел
set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border){
    auto right_it = lower_bound(numbers.begin(), numbers.end(), border);
    if(*right_it == border){
        return right_it;
    }
    else if(size(numbers) > 2){
        if(right_it != begin(numbers)){
            auto left_it = prev(right_it);
            if(border - *left_it <= *right_it-border){
                return left_it;
            }
            else{
                return right_it;
            }
        }
        else {
            return right_it;
        }
    }
    else{
        return begin(numbers);
    }
}

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 4) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 10000) << endl;
      
    set<int> empty_set;
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
