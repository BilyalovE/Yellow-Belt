#include "query.h"

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

