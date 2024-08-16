#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <locale.h>
#include <utility>
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


QueryType stringToQuery(istream& is) {
    string  queryType;
    is >> queryType;
    if (queryType == "NEW_BUS") {
        return QueryType::NEW_BUS;
    }
    if (queryType == "BUSES_FOR_STOP") {
        return QueryType::BUSES_FOR_STOP;
    }
    if (queryType == "STOPS_FOR_BUS") {
        return QueryType::STOPS_FOR_BUS;
    }
    if (queryType == "ALL_BUSES") {
        return QueryType::ALL_BUSES;
    }
    else {
    	return QueryType::ERROR;
    }
}


istream& operator >> (istream& is, Query& q) {
    q.type = stringToQuery(is);
    switch (q.type) {
    case QueryType::NEW_BUS:
        is >> q.bus;
        //////
        int stop_count;
        is >> stop_count;
        q.stops.clear();
        while (stop_count > 0) {
            is >> q.stop;
            q.stops.push_back(q.stop);
            --stop_count;
        }
        break;
    case QueryType::BUSES_FOR_STOP:
        is >> q.stop;
        break;
    case QueryType::STOPS_FOR_BUS:
        is >> q.bus;
        break;
    case QueryType::ALL_BUSES:
        break;
    case QueryType::ERROR:
        ostringstream os;
        os << "Введене неправильная команда!";
        throw runtime_error(os.str());
        break;
    }
    return is;
}

template <typename T>
ostream& operator<<(ostream& os, vector<T> v){
	bool flag_first_element = true;
	for (const auto& item : v){
		if(!flag_first_element){
			os << ", " << item;
		}
		else{
			os << item;
			flag_first_element = false;
		}
	}
	return os;
}


template <typename Key, typename Value>
ostream& operator<<(ostream& os, map<Key, Value> m){
	bool flag_first_element = true;
	for (const auto& [key, value] : m){
		if(!flag_first_element){
			os << ", " << key << ":" << "[" << value << "]";
		}
		else{
			os << key << ":" << "[" << value << "]";
			flag_first_element = false;
		}
	}
	return os;
}

template <typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> p){
	if (p.second.size() == 0) {
			os << "No bus" << endl;
		}
		else {
			os << "Stop " << p.first << ": ";
			bool flag_first_element = true;
			for (const string& bus : p.second) {
		        if (p.second.size() == 1) {
		        	cout << "no interchange";
		        }
		        else {
		        	if (!flag_first_element){
		        		os << " " << bus ;
		        	}
		        	else{
		        		os << bus;
		        		flag_first_element = false;
		        	}
		        }
			}
			os << endl;
		}
	return os;
}
struct AllBusesResponse {
	map<string, vector <string>> buses_to_stops;
};


bool operator!=(const AllBusesResponse& lhs, const AllBusesResponse& rhs) {
	bool flagNotEqule = true;
	for (const auto& [key, value] : rhs.buses_to_stops) {
		if (lhs.buses_to_stops.count(key)){
			if(value == lhs.buses_to_stops.at(key)){
				flagNotEqule = false;
			}
			else{
				flagNotEqule = true;
				return flagNotEqule;
			}
		}
		else{
			return flagNotEqule;
		}
	}
	return flagNotEqule;
}

template <typename T, typename U>
void assertEqule(const T& t, const U& u, const string& hint) {
    if (t != u) {
        ostringstream os;
        os << "Assertion faile: " << t << " != " << u << " Hint: " << hint << endl;
        throw runtime_error(os.str());
    }
}

template <typename T>
void Assert(const T& t, const string& hint){
	assertEqule(t, true, hint);
}

void TestQuery() {
    {
        Query query;
        istringstream iss("NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo");
        iss >> query;
        assertEqule(query.bus, "32", "assert equel  to num");
        assertEqule(query.stops[0], "Tolstopaltsevo", "assert equel stop0");
        assertEqule(query.stops[1], "Marushkino", "assert equel stop1");
        assertEqule(query.stops[2], "Vnukovo", "assert equel stop2");
    }
    {
        Query query;
        istringstream iss("BUSES_FOR_STOP Vnukovo");
        iss >> query;
        assertEqule(query.stop, "Vnukovo", "assert equel BUSES_FOR_STOP Vnukovo");
    }
    {
        Query query;
        istringstream iss("STOPS_FOR_BUS 272");
        iss >> query;
        assertEqule(query.bus, "272", "assert equel STOPS_FOR_BUS 272");
    }
}


struct BusesForStopResponse {
    string stop;
    vector <string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.buses.size() == 0) {
		cout << "No bus" << endl;
	}
	else {
		cout << "Stop " << r.stop << ": ";
		if (r.buses.size() == 1) {
			cout << "no interchange";
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
		cout << endl;
	}
	return os;
}

struct StopsForBusResponse {
    string bus;
    vector <string> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.stops.size() == 0) {
		cout << "No stop" << endl;
	}
	else {
		cout << "Bus " << r.bus << ": ";
		for (const string& stop : r.stops) {
			cout << stop << " ";
		}
		cout << endl;
	}
	return os;
}


ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.buses_to_stops.empty()) {
		cout << "No buses" << endl;
	}
	else {
		for (const auto& bus_item : r.buses_to_stops) {
			cout << "Bus " << bus_item.first << ": ";
	    	for (const string& stop : bus_item.second) {
	    		cout << stop << " ";
	    	}
	    	cout << endl;
	    }
	}
    return os;
}

class BusManager {
public:

	map<string, vector <string>> get_buses_to_stops(){
		return buses_to_stops;
	}
	map<string, vector <string>> get_stops_to_buses(){
		return stops_to_buses;
	}

    void AddBus(const string& bus, const vector<string>& stops) {
        // Создаю словарь автобусов
    	buses_to_stops[bus] = stops;
        // Создаю словарь остановок
    	for (const auto& stop : stops) {
    		stops_to_buses[stop].push_back(bus);
    	}
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
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

    StopsForBusResponse GetStopsForBus(const string& bus) const {
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

    AllBusesResponse GetAllBuses() const {
    	AllBusesResponse allBusesResponse;
    	allBusesResponse.buses_to_stops = buses_to_stops;
    	return allBusesResponse;

    }
private:
    map<string, vector <string>> buses_to_stops, stops_to_buses;
};

struct InputData{
	vector <string> is_list = { "NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo",
				                    "NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo"
		                          };
	map<string, vector <string>> buses_to_stops = { {"32", {"Tolstopaltsevo", "Marushkino", "Vnukovo"}},
				                                    {"32K", {"Tolstopaltsevo", "Marushkino", "Vnukovo",  "Peredelkino",  "Solntsevo", "Skolkovo"}}
		                                           };
	map<string, vector <string>> stops_to_buses = { {"Tolstopaltsevo", {"32", "32K"}},
				                                    {"Marushkino", {"32", "32K"}},
												    {"Vnukovo", {"32", "32K"}},
												    {"Peredelkino", {"32K"}},
												    {"Solntsevo", {"32K"}},
												    {"Skolkovo", {"32K"}}
		                                            };
};

BusManager getBusManager(InputData inputData, Query q){
	BusManager bm;
	for (int i = 0; i < inputData.is_list.size(); ++i ){
		istringstream is(inputData.is_list[i]);
		is >> q;
		bm.AddBus(q.bus, q.stops);
	}
	return bm;
}



void TestGetBusesForStop(){
	InputData inputData;
	Query q;
	BusManager bm = getBusManager(inputData, q);
	BusesForStopResponse busesForStopResponse1 = {"Tolstopaltsevo", {"32", "32K"}};
	auto p1 = make_pair(busesForStopResponse1.stop, busesForStopResponse1.buses);
	BusesForStopResponse test = bm.GetBusesForStop("Tolstopaltsevo");
	auto p2 = make_pair(test.stop, test.buses);
	assertEqule(p1, p2, "testBusesForStopResponse");
}

void TestGetStopsForBus(){
	InputData inputData;
	Query q;
	BusManager bm = getBusManager(inputData, q);
	StopsForBusResponse stopsForBusResponse = {"32", {"Tolstopaltsevo", "Marushkino", "Vnukovo"}};
	auto p3 = make_pair(stopsForBusResponse.bus, stopsForBusResponse.stops);
	StopsForBusResponse test2 = bm.GetStopsForBus("32");
	auto p4 = make_pair(test2.bus, test2.stops);
	assertEqule(p3, p4, "stopsForBusResponse");
}

void TestGetAllBuses(){
	InputData inputData;
	Query q;
	BusManager bm = getBusManager(inputData, q);
	for (int i = 0; i < inputData.is_list.size(); ++i ){
		istringstream is(inputData.is_list[i]);
		is >> q;
		bm.AddBus(q.bus, q.stops);
	}
	AllBusesResponse allBusesResponse = {inputData.buses_to_stops};
	allBusesResponse.buses_to_stops["33"] = {"Tolstopaltsevo"};
	assertEqule(bm.GetAllBuses(), allBusesResponse, "teatGetAllBusses");
}

class TestRunner{
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string test_name) {
		try{
			func();
			cerr << test_name << " Ok" << endl;
		}
		catch (runtime_error& exError) {
			++test_fail_count;
			cerr << test_name << exError.what();
		}
	}
	~TestRunner(){
		if (test_fail_count > 0){
			cerr <<  "fail count " << test_fail_count << ". Terminate" << endl;
			exit(1);
		}
	}

private:
	int test_fail_count = 0;
};

void testAll(){
	TestRunner tr;
	tr.RunTest(TestQuery, "TestQuery");
	tr.RunTest(TestGetBusesForStop, "TestGetBusesForStop");
	tr.RunTest(TestGetAllBuses, "TestGetStopsForBus");
	tr.RunTest(TestGetAllBuses, "TestGetAllBuses");
}

int main() {
	setlocale(LC_ALL, "Russian");

	testAll();

    int query_count;
    Query q;
    cin >> query_count;
    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        try{
        	switch (q.type) {
        		case QueryType::NEW_BUS:
        			bm.AddBus(q.bus, q.stops);
        	        break;
        	    case QueryType::BUSES_FOR_STOP:
        	        cout << bm.GetBusesForStop(q.stop);
        	        break;
        	    case QueryType::STOPS_FOR_BUS:
        	        cout << bm.GetStopsForBus(q.bus);
        	        break;
        	    case QueryType::ALL_BUSES:
        	        cout << bm.GetAllBuses();
        	        break;
        	    case QueryType::ERROR:
        	    	--i;
        	    	break;
        	}
        }
        catch (runtime_error& ex) {
        	cout << ex.what() << endl;
        }
    }
    return 0;
}

