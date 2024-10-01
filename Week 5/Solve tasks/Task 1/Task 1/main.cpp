//
//  main.cpp
//  Task 1 Видео 1
//
//  Created by Билялов Эльдар on 30.09.2024.
//

#include <iostream>
#include <string>


using namespace std;

struct Log {
    Log(const string& name): n(name){
        cout << "+" << n << endl;
    }
    ~Log(){
        cout << "-" << n << endl;
    }
    string n;
};

struct Fruit{
    Fruit(const string& t, const int h) : type(t), hp(h){
    }
    const string type;
    const int hp;
};

struct Apple : public  Fruit{
    Apple() : Fruit("apple", 10){
    }
};

class Animal{
    
};

class Cat{
    
};

class Dog{
    
}


int main(int argc, const char * argv[]) {
    Apple a1;
    cout << a1.type << endl;
    cout << a1.hp << endl;
    return 0;
}
