#include "query.h"
#include "bus_manager.h"
#include "tests.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
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
