//
//  main.cpp
//  Task 11 Построение арифметического выражения. Часть 1
//
//  Created by Билялов Эльдар on 28.09.2024.
//

#include <iostream>
#include <string>
#include <vector>
#include <deque>
using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const deque<T> & deq){
    for (const auto& d : deq){
        out << d;
    }
    return out;
}

deque <string> AssembleMathExpression(const int a, const vector <char>& list_operation,
                              const vector <int>& list_numbers){
    deque <string> result = {to_string(a)};
    for (int i = 0; i < list_operation.size(); ++i){
        result.push_front("(");
        result.push_back(")");
        string str(1, list_operation[i]);
        result.push_back(" " + str + " ");
        if (list_numbers[i] < 0){
            result.push_back("(");
            result.push_back(to_string(list_numbers[i]));
            result.push_back(")");
        }
        else{
            result.push_back(to_string(list_numbers[i]));
        }
    }
    return result;
}

int main(int argc, const char * argv[]) {
    int a, N;
    vector <char> list_operation;
    vector <int> list_numbers;
    cin >> a >> N;
    if (N == 0){
        cout << a;
    }
    else{
        while (N > 0){
            char math_operation = ' ';
            int number = 0;
            cin >> math_operation >> number;
            list_operation.push_back(math_operation);
            list_numbers.push_back(number);
            --N;
        }
        cout << AssembleMathExpression(a, list_operation, list_numbers) << endl;
    }
    return 0;
}

