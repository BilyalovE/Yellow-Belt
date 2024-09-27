//
//  main.cpp
//  Task 1
//
//  Created by Билялов Эльдар on 27.09.2024.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers){
    auto it = find_if(begin(numbers),
    end(numbers),
    [](const auto i){
    return i < 0;
    });
    if(it != end(numbers)){
        while (it != begin(numbers)){
            --it;
            if (it != begin(numbers)){
                cout << *it << ", ";
            }
            else{
                cout << *it << endl;
            }
        }
    }
    else if (it == end(numbers)){
        while ( --it != prev(begin(numbers))){
            if (it != begin(numbers)){
                cout << *it << ", ";
            }
            else{
                cout << *it << endl;
            }
        }
    }
}


int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  PrintVectorPart({6, 1, 8, 5, 4});
  return 0;
}
