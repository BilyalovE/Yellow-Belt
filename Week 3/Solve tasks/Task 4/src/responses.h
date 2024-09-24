#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

struct BusesForStopResponse {
    string stop;
    vector <string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    string bus;
    vector <string> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
	map<string, vector <string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);

