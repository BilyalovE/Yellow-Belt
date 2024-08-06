#include <iostream>
#include <sstream>
#include <cassert>
#include <string>
#include <map>
#include <vector>
#include <exception>
using namespace std;




using namespace std;

enum class QueryType {
    NEW_BUS,
    BUSES_FOR_STOP,
    STOPS_FOR_BUS,
    ALL_BUSES,
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
    }
    return is;
}



template <typename T, typename U>
void Assert( T& t,  U& u) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed " << t << "!=" << u;
        throw runtime_error(os.str());
    }
    
}

void TestQuery() {
    {
        Query query;
        istringstream iss("NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnkovo");
        iss >> query;
        
        Assert(query.bus, "31");
        
       
        
        assert(query.stops[0] == "Tolstopaltsevo");
        assert(query.stops[1] == "Marushkino");
        assert(query.stops[2] == "Vnukvoo");
    }
    {
        Query query;
        istringstream iss("BUSES_FOR_STOP Vnukovo");
        iss >> query;
        assert(query.stop == "Vnukovo");
    }
    {
        Query query;
        istringstream iss("STOPS_FOR_BUS 272");
        iss >> query;
        assert(query.bus == "272");
    }
}


struct BusesForStopResponse {
    string bus;
    vector<string> stops;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    return os;
}

struct StopsForBusResponse {
    string stop;
    vector<string> busses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    return os;
}

struct AllBusesResponse {
    // Наполните полями эту структуру
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        map<string, vector<string>> buses_to_stops, stops_to_buses;
        buses_to_stops[bus] = stops;
        for (const string stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    //BusesForStopResponse GetBusesForStop(const string& stop) const {
    //    // Реализуйте этот метод
    //}

    //StopsForBusResponse GetStopsForBus(const string& bus) const {
    //    // Реализуйте этот метод
    //}

    //AllBusesResponse GetAllBuses() const {
    //    // Реализуйте этот метод
    //};
};





// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    TestQuery();
    int query_count;
    Query q;

    cin >> query_count;

   /* BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NEW_BUS:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BUSES_FOR_STOP:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::STOPS_FOR_BUS:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::ALL_BUSES:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }*/

    return 0;
}



#include <iostream>
#include <sstream>
#include <cassert>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
    ErrorQueryType
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

QueryType stringToQuery(const string& queryType) {
    if (queryType == "NEW_BUS") {
        return QueryType::NewBus;
    }
    if (queryType == "BUSES_FOR_STOP") {
        return QueryType::BusesForStop;
    }
    if (queryType == "STOPS_FOR_BUS") {
        return QueryType::StopsForBus;
    }
    if (queryType == "ALL_BUSES") {
        return QueryType::AllBuses;
    }
    return QueryType::ErrorQueryType;
}

istream& operator>>(istream& is, Query& q) {
    string queryType;
    is >> queryType;
    q.type = stringToQuery(queryType);
    switch (q.type) {
    case QueryType::NewBus: {
        int stop_count;
        is >> q.bus >> stop_count;
        q.stops.clear();
        for (int i = 0; i < stop_count; ++i) {
            string stop;
            is >> stop;
            q.stops.push_back(stop);
        }
        break;
    }
    case QueryType::BusesForStop:
        is >> q.stop;
        break;
    case QueryType::StopsForBus:
        is >> q.bus;
        break;
    case QueryType::AllBuses:
    case QueryType::ErrorQueryType:
        break;
    }
    return is;
}

template <typename T, typename U>
void Assert(const T& t, const U& u) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        string msg = os.str();
        cerr << msg << endl;  // Выводим сообщение об ошибке в стандартный поток ошибок
        throw runtime_error(msg);
    }
}

void TestQuery() {
    {
        Query query;
        istringstream iss("NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo");
        cout << "Running test: NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo" << endl;
        iss >> query;
        Assert(query.bus, "31");
        Assert(query.stops[0], "Tolstopaltsevo");
        Assert(query.stops[1], "Marushkino");
        Assert(query.stops[2], "Vnukovo");
        cout << "Test NEW_BUS passed!" << endl;
    }
    {
        Query query;
        istringstream iss("BUSES_FOR_STOP Vnukovo");
        cout << "Running test: BUSES_FOR_STOP Vnukovo" << endl;
        iss >> query;
        Assert(query.stop, "Vnukovo");
        cout << "Test BUSES_FOR_STOP passed!" << endl;
    }
    {
        Query query;
        istringstream iss("STOPS_FOR_BUS 272");
        cout << "Running test: STOPS_FOR_BUS 272" << endl;
        iss >> query;
        Assert(query.bus, "272");
        cout << "Test STOPS_FOR_BUS passed!" << endl;
    }
}

int main() {
    cout << "Starting tests..." << endl;
    TestQuery();
    cout << "All tests passed!" << endl;
    return 0;
}
