#include <Passenger.hpp>
#include <Flight.hpp>

class Reservation { 
    public:
        Passenger passenger;
        Flight flight;
        int confirmationNumber;

        Reservation(Passenger p, Flight f, int c) : passenger {p}, flight {f}, confirmationNumber {c} {}
};