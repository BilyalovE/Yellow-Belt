#include "bus_manager.h"


map<string, vector <string>> BusManager::get_buses_to_stops(){
	return buses_to_stops;
}

map<string, vector <string>> BusManager::get_stops_to_buses(){
	return stops_to_buses;
}

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    // Создаю словарь автобусов
    buses_to_stops[bus] = stops;
    // Создаю словарь остановок
    for (const auto& stop : stops) {
    	stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse busesForStopResponse;
    if (stops_to_buses.count(stop) == 0) {
    	return busesForStopResponse;
    }
    else {
    	busesForStopResponse.stop = stop;
    	busesForStopResponse.buses = stops_to_buses.at(stop);
    	return busesForStopResponse;
    }
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
   	StopsForBusResponse stopsForBusResponse;
   	if (buses_to_stops.count(bus) == 0) {
   	    return stopsForBusResponse;
   	}
   	else {
   		stopsForBusResponse.bus = bus;
   		stopsForBusResponse.stops = buses_to_stops.at(bus);
   		return stopsForBusResponse;
   	}
}

AllBusesResponse BusManager::GetAllBuses() const {
    	AllBusesResponse allBusesResponse;
    	allBusesResponse.buses_to_stops = buses_to_stops;
    	return allBusesResponse;

    }



