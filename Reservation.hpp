

class Reservation { 
    public:
        Passenger passenger;
        int confirmationNumber;
        int seatrow;
        char seatcol;

        Reservation(Passenger p, int cn, int r, int c) : passenger {p}, confirmationNumber {cn}, seatrow {r}, seatcol {static_cast<char>(c)} {}
};