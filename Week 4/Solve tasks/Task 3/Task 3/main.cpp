//
//  main.cpp
//  Task 3
//
//  Created by Билялов Эльдар on 27.09.2024.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s){
    vector<string> res;
    auto begin_range = begin(s);
    for(auto it = find(begin(s), end(s), ' ');
        it != end(s);
        it = find(next(it), end(s), ' '))
    {
        string word(begin_range, it);
        res.push_back(word);
        begin_range = ++it;
        
    }
    string word(rbegin(s), find(rbegin(s), rend(s), ' '));
    reverse(begin(word), end(word));
    res.push_back(word);
    return res;
}


int main() {
  string s = "C Cpp Java Python";
  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}
