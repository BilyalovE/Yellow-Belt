#include "responses.h"



ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.buses.size() == 0) {
		os << "No bus" << endl;
	}
	else {
		os << "Stop " << r.stop << ": ";
		if (r.buses.size() == 1) {
			os << "no interchange";
		}
		else {
			bool flag_first_element = true;
			for (const string& bus : r.buses) {
				if (!flag_first_element) {
					os << " " << bus;
				}
				else {
					os << bus;
					flag_first_element = false;
				}
			}
		}
		os << endl;
	}
	return os;
}


ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.stops.size() == 0) {
		os << "No stop" << endl;
	}
	else {
		os << "Bus " << r.bus << ": ";
		for (const string& stop : r.stops) {
			os << stop << " ";
		}
		os << endl;
	}
	return os;
}



ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.buses_to_stops.empty()) {
		os << "No buses" << endl;
	}
	else {
		for (const auto& bus_item : r.buses_to_stops) {
			os << "Bus " << bus_item.first << ": ";
	    	for (const string& stop : bus_item.second) {
	    		os << stop << " ";
	    	}
	    	os << endl;
	    }
	}
    return os;
}
