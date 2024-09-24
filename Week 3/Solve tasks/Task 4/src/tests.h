#pragma once
#include "query.h"
#include <sstream>
#include "responses.h"
#include <utility>
#include <map>
#include "bus_manager.h"

#include "tests.h"

using namespace std;

struct InputData;

void TestQuery();
BusManager getBusManager(InputData inputData, Query q);
void TestGetBusesForStop();
void TestGetStopsForBus();
void TestGetAllBuses();
void testAll();
