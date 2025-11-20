#include "ReservationManager.hpp"
#include "Passenger.hpp"
#include "Reservation.hpp"

ReservationManager::ReservationManager(Reservation r, Passenger p) : reservation {r}, passenger {p} {};

int ReservationManager::makeReservation(Reservation r, Passenger p) {
    return 0; //implement this
}

int ReservationManager::cancelReservation(Reservation r, Passenger p) {
    return 0; //implement this
}

void ReservationManager::viewReservations(Passenger p) {
    //implement this
}
