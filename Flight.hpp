#include <string>
class Flight {

    public:
        int flightID;
        std::string source;
        std::string destination;
        std::string takeOffTime;
        std::string landTime;
        Flight(int id, std::string source, std::string destination, std::string takeoff, std::string land) : flightID {id}, source {source}, destination {destination}, takeOffTime {takeoff}, landTime {land} {}

};