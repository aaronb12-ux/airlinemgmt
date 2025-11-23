

class Reservation { 
    public:
        Passenger passenger;
        int seatrow;
        char seatcol;

        Reservation(Passenger p, int r, int c) : passenger {p}, seatrow {r}, seatcol {static_cast<char>(c)} {}
};