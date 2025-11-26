#include <iostream>
#include <string>

class Passenger {
    
    public:
        std::string firstName;
        std::string lastName;
        int id;
        Passenger(std::string first, std::string last, int id) : firstName {first}, lastName {last}, id {id} {} //constructor

};