#include <Reservation.hpp>
#include <Passenger.hpp>

#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

class ReservationManager {

    public:
        Reservation reservation;
        Passenger passenger;

        ReservationManager(Reservation r, Passenger p);
        int makeReservation(Reservation r, Passenger p); 
        int cancelReservation(Reservation r, Passenger p);
        void viewReservations(Passenger p);

};

#endif