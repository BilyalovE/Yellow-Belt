//
//  main.cpp
//  Task 2
//
//  Created by Билялов Эльдар on 02.10.2024. Набор фигур
//

#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class Figure{
public:
    Figure(const string n) : name(n) {};
    string Name() const {
        return name;
    };
    virtual double Perimeter() const = 0;;
    virtual double Area() const = 0;
public:
    string name = "";
};

class Triangle : public Figure{
public:
    Triangle(const int a_, const int b_, const int c_)
    : Figure("Triangle"), a(a_), b(b_), c(c_) {}
    double Perimeter() const override {
        return a + b + c;
    }
    
    double Area() const override {
        double half_per = 0.5 * Perimeter();
        return sqrt(half_per * (half_per - a) * (half_per- b) * (half_per - c)) ;
    }
private:
    const double a = 0;
    const double b = 0;
    const double c = 0;
};

class Rect : public Figure{
public:
    Rect(const int a_, const int b_) : Figure("Rect"), a(a_), b(b_) {}
    double Perimeter() const override {
        return 2 * (a + b);
    }
    double Area() const override {
        return a * b;
    }
private:
    const double a = 0;
    const double b = 0;
};

class Circle : public Figure{
public:
    Circle(const int r_) : Figure("Circle"), r(r_) {}
    double Perimeter() const override {
        return 2 * pi * r ;
    }
    double Area() const override {
        return pi * r * r;
    }
private:
    const double r = 0;
    const double pi = 3.14;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
    string name;
    double a, b, c, r;
    shared_ptr<Figure> figure;
    // Считываем название фигуры
    getline(is, name, ' ');
    if (name == "TRIANGLE") {
        is >> a >> b >> c;
        figure = make_shared<Triangle>(a, b, c);
    } else if (name == "RECT") {
        is >> a >> b;
        figure = make_shared<Rect>(a, b);
    } else if (name == "CIRCLE") {
        is >> r;
        figure = make_shared<Circle>(r);
    } else {
        // Если неизвестная команда ADD, обработать ошибку или вернуть nullptr
        cerr << "Неизвестная команда ADD: " << name << endl;
        return nullptr;
    }

    return figure;
}




int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);
    string command;
    getline(is, command, ' ');
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
