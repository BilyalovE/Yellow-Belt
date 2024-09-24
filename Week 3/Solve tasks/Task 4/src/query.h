#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <exception>
using namespace std;

enum class QueryType {
    NEW_BUS,
    BUSES_FOR_STOP,
    STOPS_FOR_BUS,
    ALL_BUSES,
	ERROR
};

struct Query {
    QueryType type;
    string bus ;
    string stop;
    vector<string> stops;
};


QueryType stringToQuery(istream& is);

istream& operator >> (istream& is, Query& q);
