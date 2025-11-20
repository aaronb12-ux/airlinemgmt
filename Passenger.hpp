#include <iostream>
#include <string>

class Passenger {
    
    public:
        std::string firstName;
        std::string lastName;
        Passenger(std::string first, std::string last) : firstName {first}, lastName {last} {} //constructor

};