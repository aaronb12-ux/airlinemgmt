

class Reservation { 
    public:
        int flightNum;
        Passenger passenger;
        int seatrow;
        char seatcol;
        int confirmation;

        Reservation(int fn, Passenger p, int r, char c, int confirmation) : flightNum{fn}, passenger {p}, seatrow {r}, seatcol {static_cast<char>(c)}, confirmation {confirmation} {}
};