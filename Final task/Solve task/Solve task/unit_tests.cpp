#include "date.h"
#include "database.h"
#include "node.h"
#include "test_runner.h"
#include "condition_parser_test.h"




using namespace std;

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event",
                    "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"},
                    "Parse multiple events");
    }
}

void TestParseDate(){
    {
        istringstream is("2017-06-01 1st of June");
        AssertEqual(ParseDate(is), Date(2017, 06, 01), "Parse date correct values 1");
    }
    {
        stringstream is("0-2-31 2017-06-01 1st of June");
        AssertEqual(ParseDate(is), Date(0, 2, 31), "Parse date correct values 2");
    }
    {
        stringstream is("10000-2-31  1st of June");
        try{
            ParseDate(is);
        }
        catch(logic_error & l_err){
            stringstream os1(l_err.what());
            stringstream os2("Year value is invalid: 10000");
            AssertEqual(os1.str(), os2.str(), "Parse date uncorrect values 1 invalid year");
        }
    }
    {
        stringstream is("0-0-31  1st of June");
        try{
            ParseDate(is);
        }
        catch(logic_error & l_err){
            stringstream os1(l_err.what());
            stringstream os2("Month value is invalid: 0");
            AssertEqual(os1.str(), os2.str(),
                        "Parse date uncorrect values 2 invalid month");
        }
    }
    {
        stringstream is("0--1-31  1st of June");
        try{
            ParseDate(is);
        }
        catch(logic_error & l_err){
            stringstream os1(l_err.what());
            stringstream os2("Month value is invalid: -1");
            AssertEqual(os1.str(), os2.str(),
                        "Parse date uncorrect values 2 invalid month2");
        }
    }
    {
        stringstream is("0-1-32  1st of June");
        try{
            ParseDate(is);
        }
        catch (logic_error& l_err){
            stringstream os1(l_err.what());
            stringstream os2("Day value is invalid: 32");
            AssertEqual(os1.str(), os2.str(),
                        "Parse date uncorrect values 2 invalid day");
        }
    }
    {
        stringstream is("--0-1-32  1st of June");
        try{
            ParseDate(is);
        }
        catch (logic_error& l_err){
            stringstream os1(l_err.what());
            stringstream os2("Wrong date format: --0-1-32");
            AssertEqual(os1.str(), os2.str(),
                        "Parse date uncorrect date format 1");
        }
    }
    {
        stringstream is("-0---1-32  1st of June");
        try{
            ParseDate(is);
        }
        catch (logic_error& l_err){
            stringstream os1(l_err.what());
            stringstream os2("Wrong date format: -0---1-32");
            AssertEqual(os1.str(), os2.str(),
                        "Parse date uncorrect date format 2");
        }
    }
    {
        stringstream is("-24/1-32  1st of June");
        try{
            ParseDate(is);
        }
        catch (logic_error& l_err){
            stringstream os1(l_err.what());
            stringstream os2("Wrong date format: -24/1-32");
            AssertEqual(os1.str(), os2.str(),
                        "Parse date uncorrect date format 3");
        }
    }
    {
        stringstream is("24-1--32  1st of June");
        try{
            ParseDate(is);
        }
        catch (logic_error& l_err){
            stringstream os1(l_err.what());
            stringstream os2("Day value is invalid: -32");
            AssertEqual(os1.str(), os2.str(),
                        "Parse date uncorrect values 3 invalid day");
        }
    }
}

void TestDatabaseAdd(){
    {
        istringstream is("2017-06-01 1st of June");
        const auto date = ParseDate(is);
        const auto event = ParseEvent(is);
        Database db;
        db.Add(date, event);
        map<Date, set<string>> expected = {{{2017, 6, 1}, {"1st of June"}}};
        AssertEqual(db.GetBd(), expected, "TestDatabaseAdd one node");
    }
    {
        istringstream is("7-12-1 Birthday`s Eldar");
        auto date = ParseDate(is);
        auto event = ParseEvent(is);
        Database database;
        database.Add(date, event);
        istringstream is2("7-12-1 Birthday`s Eldar");
        date = ParseDate(is2);
        event = ParseEvent(is2);
        database.Add(date, event);
        const map<Date, set<string>> expected = {{{7, 12, 1}, {"Birthday`s Eldar"}}};
        AssertEqual(database.GetBd(), map<Date, set<string>> {{{7, 12, 1}, {"Birthday`s Eldar"}}}, "TestDatabaseAdd double note");
    }
    {
        istringstream is("7-12-1 Birthday`s Eldar");
        auto date = ParseDate(is);
        auto event = ParseEvent(is);
        Database database;
        database.Add(date, event);
        istringstream is2("2002-04-29 Birthday`s Eldar");
        date = ParseDate(is2);
        event = ParseEvent(is2);
        database.Add(date, event);
        const map<Date, set<string>> expected = {{{7, 12, 1}, {"Birthday`s Eldar"}},
            {{2002, 04, 29}, {"Birthday`s Eldar"}}};
        AssertEqual(database.GetBd(), expected,"TestDatabaseAdd several note");
    }
    {
        istringstream is("1975-05-23 Birthday`s Venera");
        auto date = ParseDate(is);
        auto event = ParseEvent(is);
        Database database;
        database.Add(date, event);
        istringstream is2("2002-04-29 Birthday`s Eldar");
        auto date2 = ParseDate(is2);
        event = ParseEvent(is2);
        database.Add(date2, event);
        istringstream is3("2002-04-29 Happy dinner");
        date = ParseDate(is3);
        event = ParseEvent(is3);
        database.Add(date, event);
        const map<Date, set<string>> expected = {{{1975, 05, 23}, {"Birthday`s Venera"}},
            {{2002, 04, 29}, {"Birthday`s Eldar", "Happy dinner"}}};
        AssertEqual(database.GetBd(), expected,"TestDatabaseAdd several note2");
    }
}

void TestDatabasePrint(){
    {
        istringstream is("1975-05-23 Birthday`s Venera");
        auto date = ParseDate(is);
        auto event = ParseEvent(is);
        Database database;
        database.Add(date, event);
        stringstream os1, os2;
        database.Print(os1);
        os2 << "1975-05-23 Birthday`s Venera";
        AssertEqual(os1.str(), os2.str(), "TestDatabasePrint 1");
    }
    {
        istringstream is("1975-05-23 Birthday`s Venera");
        auto date = ParseDate(is);
        auto event = ParseEvent(is);
        Database database;
        database.Add(date, event);
        istringstream is2("2002-4-29 Birthday`s Eldar");
        auto date2 = ParseDate(is2);
        event = ParseEvent(is2);
        database.Add(date2, event);
        istringstream is3("2002-04-29 Happy dinner");
        date = ParseDate(is3);
        event = ParseEvent(is3);
        database.Add(date, event);
        stringstream os1, os2;
        database.Print(os1);
        os2 << "1975-05-23 Birthday`s Venera" << '\n'
            << "2002-04-29 Birthday`s Eldar" << '\n'
            << "2002-04-29 Happy dinner";
        AssertEqual(os1.str(), os2.str(), "TestDatabasePrint 2");
    }
}

void TestDatabaseFindIf(){
    {
        istringstream is("2017-01-01 Holiday");
        auto date = ParseDate(is);
        auto event = ParseEvent(is);
        Database database;
        database.Add(date, event);
        istringstream is2("2017-03-08 Holiday");
        auto date2 = ParseDate(is2);
        event = ParseEvent(is2);
        database.Add(date2, event);
        istringstream is3("2017-01-01 New Year");
        auto date3 = ParseDate(is3);
        event = ParseEvent(is3);
        database.Add(date3, event);
        istringstream is_cond("event != \"working day\"");
        auto condition = ParseCondition(is_cond);
        auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
        };
        const auto entries = database.FindIf(predicate);
        ostringstream os1, os2;
        for (const auto& entry : entries){
            os1 << entry << endl;
        }
        os2 << "2017-01-01 Holiday" << '\n'
            << "2017-01-01 New Year" << '\n'
            << "2017-03-08 Holiday" << '\n';
        AssertEqual(os1.str(), os2.str(), "TestDatabaseFindIf 1");
    }
    {
        istringstream is("2017-01-01 Holiday");
        auto date = ParseDate(is);
        auto event = ParseEvent(is);
        Database database;
        database.Add(date, event);
        istringstream is2("2017-03-08 Holiday");
        auto date2 = ParseDate(is2);
        event = ParseEvent(is2);
        database.Add(date2, event);
        istringstream is3("2017-01-01 New Year");
        auto date3 = ParseDate(is3);
        event = ParseEvent(is3);
        database.Add(date3, event);
        istringstream is_cond("");
        auto condition = ParseCondition(is_cond);
        auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
        };
        const auto entries = database.FindIf(predicate);
        ostringstream os1, os2;
        for (const auto& entry : entries){
            os1 << entry << endl;
        }
        os2 << "2017-01-01 Holiday" << '\n'
            << "2017-01-01 New Year" << '\n'
            << "2017-03-08 Holiday" << '\n';
        AssertEqual(os1.str(), os2.str(), "TestDatabaseFindIf 2");
    }
    {
        istringstream is("2017-01-01 holiday");
        auto date = ParseDate(is);
        auto event = ParseEvent(is);
        Database database;
        database.Add(date, event);
        istringstream is2("2017-03-08 Holiday");
        auto date2 = ParseDate(is2);
        event = ParseEvent(is2);
        database.Add(date2, event);
        istringstream is3("2017-01-01 New Year");
        auto date3 = ParseDate(is3);
        event = ParseEvent(is3);
        database.Add(date3, event);
        istringstream is_cond("event == \"holiday\" AND date == 2017-1-01");
        auto condition = ParseCondition(is_cond);
        auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
        };
        const auto entries = database.FindIf(predicate);
        ostringstream os1, os2;
        for (const auto& entry : entries){
            os1 << entry << endl;
        }
        os2 << "2017-01-01 holiday" << '\n';
        AssertEqual(os1.str(), os2.str(), "TestDatabaseFindIf 3");
    }
}


void TestDatabaseLast(){
    {
        istringstream is("2017-01-01 New Year");
        auto date = ParseDate(is);
        auto event = ParseEvent(is);
        Database database;
        database.Add(date, event);
        istringstream is2("2017-03-08 Holiday");
        date = ParseDate(is2);
        event = ParseEvent(is2);
        database.Add(date, event);
        istringstream is3("2017-01-01 Holiday");
        date = ParseDate(is3);
        event = ParseEvent(is3);
        database.Add(date, event);
        istringstream is4("2016-12-31");
        stringstream os1, os2;
        try{
            database.Last(ParseDate(is4));
        }
        catch (invalid_argument&) {
            os1 << "No entries" << endl;
        }
        os2 << "No entries" << endl;
        AssertEqual(os1.str(), os2.str(), "TestDatabaseLast 1");
    }
    {
        Database database;
        istringstream is("2016-12-31");
        stringstream os1, os2;
        try{
            os1 << database.Last(ParseDate(is));
        }
        catch (invalid_argument&) {
            os1 << "No entries" << endl;
        }
        os2 << "No entries" << endl;
        AssertEqual(os1.str(), os2.str(), "TestDatabaseLast 2");
    }
    {
        istringstream is("2017-01-01 New Year");
        auto date = ParseDate(is);
        auto event = ParseEvent(is);
        Database database;
        database.Add(date, event);
        istringstream is2("2017-03-08 Holiday");
        date = ParseDate(is2);
        event = ParseEvent(is2);
        database.Add(date, event);
        istringstream is3("2017-01-01 Holiday");
        date = ParseDate(is3);
        event = ParseEvent(is3);
        database.Add(date, event);
        istringstream is4("2017-1-01");
        stringstream os1, os2;
        try{
            os1 << database.Last(ParseDate(is4));
        }
        catch (invalid_argument&) {
            os1 << "No entries" << endl;
        }
        os2 << "2017-01-01 Holiday";
        AssertEqual(os1.str(), os2.str(), "TestDatabaseLast 3");
    }
    {
        istringstream is("2017-01-01 New Year");
        auto date = ParseDate(is);
        auto event = ParseEvent(is);
        Database database;
        database.Add(date, event);
        istringstream is2("2017-03-08 Holiday");
        date = ParseDate(is2);
        event = ParseEvent(is2);
        database.Add(date, event);
        istringstream is3("2017-01-01 Holiday");
        date = ParseDate(is3);
        event = ParseEvent(is3);
        database.Add(date, event);
        istringstream is4("2017-06-01");
        stringstream os1, os2;
        try{
            os1 << database.Last(ParseDate(is4));
        }
        catch (invalid_argument&) {
            os1 << "No entries" << endl;
        }
        os2 << "2017-03-08 Holiday";
        AssertEqual(os1.str(), os2.str(), "TestDatabaseLast 4");
    }
}

void TestDatabaseRemoveIf(){
    {}
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseDate, "TestParseDate");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestDatabaseAdd, "TestDatabaseAdd");
    tr.RunTest(TestDatabasePrint, "TestDatabasePrint");
    tr.RunTest(TestDatabaseFindIf, "TestDatabaseFindIf");
    tr.RunTest(TestDatabaseLast, "TestDatabaseLast");
    tr.RunTest(TestDatabaseRemoveIf, "TestDatabaseRemoveIf");
}
