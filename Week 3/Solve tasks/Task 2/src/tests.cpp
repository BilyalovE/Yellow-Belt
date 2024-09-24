#include "tests.h"

void testGetCountryCode(){
	PhoneNumber phoneNumber(PhoneNumber("+7-495-111-22-33"));
	AssertEqual(phoneNumber.GetCountryCode(), "7", "test county code 1");
	PhoneNumber phoneNumber1(PhoneNumber("+7909-495-111-22-33"));
	AssertEqual(phoneNumber1.GetCountryCode(), "7909", "test county code 2");
	PhoneNumber phoneNumber2(PhoneNumber("+asmsa-495-111-22-33"));
	AssertEqual(phoneNumber2.GetCountryCode(), "asmsa", "test county code 3");
	PhoneNumber phoneNumber3(PhoneNumber("+1-2-coursera-cpp"));
	AssertEqual(phoneNumber3.GetCountryCode(), "1", "test county code 3");
	//PhoneNumber phoneNumber3(PhoneNumber("90-495-111-22-33"));
	//AssertEqual(phoneNumber3.GetCountryCode(), " ", "invalid_argument test county code 4");
}
void testGetCityCode(){
	PhoneNumber phoneNumber(PhoneNumber("+7-495-111-22-33"));
	AssertEqual(phoneNumber.GetCityCode(), "495", "test city  code 1");
	PhoneNumber phoneNumber1(PhoneNumber("+7909-4-111-22-33"));
	AssertEqual(phoneNumber1.GetCityCode(), "4", "test city code 2");
	PhoneNumber phoneNumber2(PhoneNumber("+asmsa-495-111-22-33"));
	AssertEqual(phoneNumber2.GetCityCode(), "495", "test city  code 3");
	PhoneNumber phoneNumber3(PhoneNumber("+asmsa-dckdn c-111-22-33"));
	AssertEqual(phoneNumber3.GetCityCode(), "dckdn c", "test city code 4");
}
void testGetLocalNumber(){
	PhoneNumber phoneNumber(PhoneNumber("+7-495-111-22-33"));
	AssertEqual(phoneNumber.GetLocalNumber(), "111-22-33", "test LocalNumber  code 1");
	PhoneNumber phoneNumber1(PhoneNumber("+7-495-1112233"));
	AssertEqual(phoneNumber1.GetLocalNumber(), "1112233", "test cLocalNumber 2");
	PhoneNumber phoneNumber2(PhoneNumber("+323-22-460002"));
	AssertEqual(phoneNumber2.GetLocalNumber(), "460002", "test LocalNumber 3");
	PhoneNumber phoneNumber3(PhoneNumber("+1-2-coursera-cpp"));
	AssertEqual(phoneNumber3.GetLocalNumber(), "coursera-cpp", "test LocalNumber 4");
}
void testGetInternationalNumber(){
	PhoneNumber phoneNumber(PhoneNumber("+7-495-111-22-33"));
	AssertEqual(phoneNumber.GetInternationalNumber(), "+7-495-111-22-33", "test GetInternationalNumber 1");
	PhoneNumber phoneNumber2(PhoneNumber("+7-495-1112233"));
	AssertEqual(phoneNumber2.GetInternationalNumber(), "+7-495-1112233", "test GetInternationalNumber 2");
	PhoneNumber phoneNumber3(PhoneNumber("+323-22-4-600-0-0-2"));
	AssertEqual(phoneNumber3.GetInternationalNumber(), "+323-22-4-600-0-0-2", "test GetInternationalNumber 3");
	PhoneNumber phoneNumber4(PhoneNumber("+1-2-coursera-cpp"));
	AssertEqual(phoneNumber4.GetInternationalNumber(), "+1-2-coursera-cpp", "test GetInternationalNumber 4");
}

void testFailed(){
	PhoneNumber phoneNumber(PhoneNumber("1233-kcc d-kd ckd-mcmd c"));
	AssertEqual(phoneNumber.GetInternationalNumber(), "+7-495-111-22-33", "testFailed 1");
}

void allTests(){
	TestRunner tr;
	tr.RunTest(testGetCountryCode, "test1");
	tr.RunTest(testGetCityCode, "test2");
	tr.RunTest(testGetLocalNumber, "test3");
	tr.RunTest(testGetInternationalNumber, "test4");
	//tr.RunTest(testFailed, "test5");
}




