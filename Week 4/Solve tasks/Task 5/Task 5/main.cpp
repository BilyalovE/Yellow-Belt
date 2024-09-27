//
//  main.cpp
//  Task 5
//
//  Created by Билялов Эльдар on 27.09.2024.
//

#include <iostream>
#include <algorithm>

using namespace std;


void PrintAllPermutation(int N){
    vector <int> nums(N);
    for(int i = 0; i < N; ++i){
        nums[i] = i + 1;
    }
    do{
        for(const auto n : nums){
            if(n != *prev(nums.end())){
                cout << n << ", ";
            }
            else{
                cout << n << endl;
            }
        }
    }
    while(next_permutation(begin(nums), end(nums)));
    
}
int main(int argc, const char * argv[]) {
    unsigned int  N;
    bool flag = 1;
    while(flag){
        cout << "Введите целое положительное число N: ";
        cin >> N;
        cout << '\n';
        if (N > 0 && N <= 9){
            flag = 0;
        }
    }
    PrintAllPermutation(N);
    
    return 0;
}
