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
public:
    Animal(const string & t) : type(t){
    }
    void Eat(const Fruit& f){
        cout << type << " eats " << f.type << endl;
    }
    virtual void Sound() const {
        cout << type << " is silent"<< endl;
    }
private:
    const string type = "";
};

class Cat : public Animal {
public:
    Cat(): Animal("Cat"){
    }
    void Sound() const override {
        cout << "meow!" << endl;
    }
};

class Dog : public Animal{
public:
    Dog():Animal("Dog"){}
    void Sound() const override {
        cout << "whaf!" << endl;
    }
};

class Parrot : public Animal {
public:
    Parrot(const string& n) : Animal("Parrot"), name(n){
    }
    void Sound() const override {
        cout << name << " is good!" << endl;
    }
private:
    const string name;
};

class Horse : public Animal{
public:
    Horse() : Animal("Horse"){
    }
    void Sound() const override {
        cout <<"Horse is good!" << endl;
    }
};

void MakeSound(const Animal& animal){
    animal.Sound();
}

int main(int argc, const char * argv[]) {
    Cat cat;
    Dog dog;
    Parrot parrot("Eldar");
    Horse horse;
    MakeSound(cat);
    MakeSound(dog);
    MakeSound(parrot);
    MakeSound(horse);
    return 0;
}

