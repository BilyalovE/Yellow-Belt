#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

class Rational {
public:
	Rational() : p(0), q(1) {};
	Rational(int numerator, int denominator) : p(numerator), q(denominator) {
		if (q == 0) {
			string error_str = "invalid_argument";
			throw runtime_error(error_str);
		}
		if (p == 0){
			q = 1;
		}
	};

	int Numerator() const {
		if (p == 0) {
			return p;
		}
		else {
			int new_numerator = abs(p / Gcd(p, q));
			return new_numerator * CheckOperation(p, q);
		}
	}
	int Denominator() const {
		if (p == 0) {
			return 1;
		}
		else {
			int new_denominator = abs(q / Gcd(p, q));
			return new_denominator;
		}
	}

private:
	int Gcd(const int p, const int q) const {
		int a = max(abs(p), abs(q));
		int b = min(abs(p), abs(q));
		int temp;
		while (b != 0) {
			temp = b;
			b = a % b;
			a = temp;
		}
		return a;
	}

	int CheckOperation(const int new_numerator, const int new_denominator) const {
		if (new_numerator < 0 && new_denominator < 0 || new_numerator > 0 && new_denominator > 0) {
			return 1;
		}
		else {
			return -1;
		}
	}

	int p, q;
};

Rational operator+(const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() == rhs.Denominator()) {
		Rational temp(lhs.Numerator() + rhs.Numerator(), lhs.Denominator());
		Rational r(temp.Numerator(), temp.Denominator());
		return r;
	}
	else {
		Rational temp(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
		Rational r(temp.Numerator(), temp.Denominator());
		return r;
	}
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() == rhs.Denominator()) {
		Rational temp(lhs.Numerator() - rhs.Numerator(), lhs.Denominator());
		Rational r(temp.Numerator(), temp.Denominator());
		return r;
	}
	else {
		Rational temp(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
		Rational r(temp.Numerator(), temp.Denominator());
		return r;
	}
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
	Rational temp(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
	Rational r(temp.Numerator(), temp.Denominator());
	return r;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	int numerator = lhs.Numerator() * rhs.Denominator();
	int denominator = rhs.Numerator() * lhs.Denominator();
	if (denominator == 0) {
		string error_str = "Division by zero";
		throw runtime_error(error_str);
	}
	else {
		Rational r(numerator, denominator);
		return r;
	}
}

// Унарный +
Rational operator+(const Rational& rhs) {
	return rhs;
}

Rational operator-(Rational& r) {
	r = { -r.Numerator(), r.Denominator() } ;
	return r;
}



bool operator==(const Rational& lhs, const Rational& rhs) {
	if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()) {
		return true;
	}
	else {
		return false;
	}
}

bool operator<(const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() == rhs.Denominator()) {
		return lhs.Numerator() < rhs.Numerator();
	}
	else {
		return lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator();
	}
}

bool operator>(const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() == rhs.Denominator()) {
		return lhs.Numerator() > rhs.Numerator();
	}
	else {
		return lhs.Numerator() * rhs.Denominator() > rhs.Numerator() * lhs.Denominator();
	}
}


istream& operator>>(istream& stream, Rational& r) {
	char operation;
	int p, q;
	stream >> p >> operation >> q;
	r = Rational(p, q);
	return stream;
}

ostream& operator<<(ostream& stream, const Rational& r) {
	stream << r.Numerator() << '/' << r.Denominator();
	return stream;
}


void testDefaultConstructorRational(){
	Rational r;
	ostringstream os;
	string etalon_value = "0/1";
	os << r;
	AssertEqual(os.str(), etalon_value, "testDefaultConstructorRational" );
}

void testConstructorRational(){
	Rational r(3, 12);
	ostringstream os;
	string etalon_value = "1/4";
	os << r;
	AssertEqual(os.str(), etalon_value, "testConstructorRational" );
}

void testNegativeRationalNumber(){
	Rational r(-3, 12), r1(6, -24);
	ostringstream os, os1;
	string etalon_value = "-1/4";
	os << r;
	os1 << r1;
	AssertEqual(os.str(), etalon_value, "testNegativeRationalNumber1" );
	AssertEqual(os1.str(), etalon_value, "testNegativeRationalNumber2" );
}

void testPositiveRationalNumber(){
	Rational r(-5, -25), r1(-100, -500);
	ostringstream os, os1;
	string etalon_value = "1/5";
	os << r;
	os1 << r1;
	AssertEqual(os.str(), etalon_value, "testPositiveRationalNumber1" );
	AssertEqual(os1.str(), etalon_value, "testPositiveRationalNumber2" );
}

void testNoleDenominator(){
	Rational r(0, 0), r1(-100, 0);
	ostringstream os, os1;
	string etalon_value = "1/5";
	os << r;
	os1 << r1;
	AssertEqual(os.str(), etalon_value, "testNoleDenominator1" );
	AssertEqual(os1.str(), etalon_value, "testNoleDenominator2" );
}

void testNoleNominator(){
	Rational r(1, 1), r1(1, 100);
	ostringstream os, os1;
	string etalon_value = "0/1";
	os << r;
	os1 << r1;
	AssertEqual(os.str(), etalon_value, "testNoleNominator1" );
	AssertEqual(os1.str(), etalon_value, "testNoleNominator2" );
}

void testAll(){
	TestRunner runner;
	runner.RunTest(testDefaultConstructorRational, "Test1");
	runner.RunTest(testConstructorRational, "Test2");
	runner.RunTest(testNegativeRationalNumber, "Test3");
	runner.RunTest(testPositiveRationalNumber, "Test4");
	//runner.RunTest(testNoleDenominator, "Test5");
	runner.RunTest(testNoleNominator, "Test6");
}

int main() {
	testAll();
	return 0;
}
