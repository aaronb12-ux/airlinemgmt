

class Reservation { 
    public:
        int flightNum;
        Passenger passenger;
        int seatrow;
        char seatcol;

        Reservation(int fn, Passenger p, int r, char c) : flightNum{fn}, passenger {p}, seatrow {r}, seatcol {static_cast<char>(c)} {}
};