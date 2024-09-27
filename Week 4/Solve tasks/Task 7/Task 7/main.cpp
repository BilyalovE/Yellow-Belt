//
//  main.cpp
//  Task 7
//
//  Created by Билялов Эльдар on 27.09.2024.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
    if(range_end - range_begin < 2){
        return;
    }
    else{
        vector<typename RandomIt::value_type> nums(range_begin, range_end);
        size_t dop_index = (end(nums) - begin(nums)) / 2;
        vector<typename RandomIt::value_type> left_nums(begin(nums), begin(nums) + dop_index);
        vector<typename RandomIt::value_type> right_nums(begin(nums) + dop_index, end(nums));
        MergeSort(begin(left_nums), end(left_nums));
        MergeSort(begin(right_nums), end(right_nums));
        vector<typename RandomIt::value_type> merge_nums;
        merge(begin(left_nums), end(left_nums), begin(right_nums),
              end(right_nums), back_inserter(merge_nums),
              [](const auto num1, const auto num2){
                return num1 < num2;
              }
        );
        // Копируем отсортированный результат обратно в исходный диапазон
        move(merge_nums.begin(), merge_nums.end(), range_begin);
        
    }
}

template <typename RandomIt>
void MergeSort3(RandomIt range_begin, RandomIt range_end){
    if(range_end - range_begin < 2){
        return;
    }
    else{
        vector<typename RandomIt::value_type> nums(range_begin, range_end);
        size_t dop_index = (end(nums) - begin(nums)) / 3;
        vector<typename RandomIt::value_type> left_nums(begin(nums), begin(nums) + dop_index);
        vector<typename RandomIt::value_type> top_nums(begin(nums) + dop_index,
                                                       end(nums) - dop_index);
        vector<typename RandomIt::value_type> right_nums(end(nums) - dop_index, end(nums));
        MergeSort3(begin(left_nums), end(left_nums));
        MergeSort3(begin(top_nums), end(top_nums));
        MergeSort3(begin(right_nums), end(right_nums));
        vector<typename RandomIt::value_type> temp_merge_nums;
        merge(begin(left_nums), end(left_nums), begin(top_nums),
              end(top_nums), back_inserter(temp_merge_nums),
              [](const auto num1, const auto num2){
                return num1 < num2;
              }
        );
        vector<typename RandomIt::value_type> merge_nums;
        merge(begin(temp_merge_nums), end(temp_merge_nums), begin(right_nums),
              end(right_nums), back_inserter(merge_nums),
              [](const auto num1, const auto num2){
                return num1 < num2;
              }
        );
        // Копируем отсортированный результат обратно в исходный диапазон
        move(merge_nums.begin(), merge_nums.end(), range_begin);
        
    }
}


int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
