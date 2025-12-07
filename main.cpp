#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <format>
#include <filesystem>
#include <map>
#include <fstream>
#include <typeinfo>
#include <tuple>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include "Passenger.hpp"
#include "Flight.hpp"
#include "Reservation.hpp"

void displayWelcome()
{
    std::cout << "\n╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║            AIRLINE RESERVATION SYSTEM                      ║\n";
    std::cout << "╠════════════════════════════════════════════════════════════╣\n";
    std::cout << "║ 1. Book Flight                                             ║\n";
    std::cout << "║ 2. View Reservations                                       ║\n";
    std::cout << "║ 3. Cancel Booking                                          ║\n";
    std::cout << "║ 4. Exit                                                    ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n\n";
}

void showAvailableSeats(int flightnumber, std::map<int, std::vector<std::tuple<int, char>>> seats)
{

    std::vector<std::tuple<int, char>> flightSeats; //create empty vector for case of missing map key
    auto it = seats.find(flightnumber); ///.find() returns an iterator that points to an element in the map

    if (it != seats.end()) { //if flightnumber exists as a key in the map, seat flightSeats to its value tuple<row,col>
        flightSeats = it->second; 
    }
 
    //lambda function to quickly check if a seat is taken
    auto checkIfTaken = [&flightSeats](int checkedRow, char checkedCol) 
    {
        for (const auto &takenSeat : flightSeats)
        {
            if (std::get<0>(takenSeat) == checkedRow && std::get<1>(takenSeat) == checkedCol)
            {
                return true;
            }
        }
        return false;
    };

    //main seating chart
    std::cout << "\n╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║              AIRPLANE SEATING CHART                        ║\n";
    std::cout << "╠════════════════════════════════════════════════════════════╣\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║                      [COCKPIT]                             ║\n";
    std::cout << "║                _____________________                       ║\n";
    std::cout << "║               |                     |                      ║\n";
    std::cout << "║               |  A  B     C  D  E   |                      ║\n";
    std::cout << "║               |                     |                      ║\n";

    for (int i = 0; i < 10; i++) { //iterate through 10 rows (top to bottom)
        std::cout << "║               |  "; 
        for (int j = 0; j < 5; j++) { //iterate through 5 cols (left to right)
       
            if (j == 2) {std::cout << "   ";}
            if (checkIfTaken(i + 1, 'A' + j)) { std::cout << "X  "; }
            else { std::cout << "O  "; }

        }
        std::cout << " |                      ║\n";
    }

    std::cout << "║               |                     |                      ║\n";
    std::cout << "║               |_____________________|                      ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "║               O = Available   X = Taken                    ║\n";
    std::cout << "║                                                            ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n\n";
}

int showFlights(std::vector<Flight> &flights)
{

    for (const auto &flight : flights)
    {
        std::cout << "\n";
        std::cout << "Flight Number: " + std::to_string(flight.flightID) << std::endl;
        std::cout << "Source: " + flight.source << std::endl;
        std::cout << "Destination: " + flight.destination << std::endl;
        std::cout << "Take Off: " + flight.takeOffTime << std::endl;
        std::cout << "Landing: " + flight.landTime << std::endl;
    }
    std::cout << "\n";

    int flightnum;
    std::cout << "Select a flight number to see available seeting: ";
    std::cin >> flightnum;
    return flightnum;

}

char makeChoice()
{
    char choice;
    std::cout << "Make your selection: ";
    std::cin >> choice;
    return choice;
}

std::vector<Flight> getFlights()
{
    std::vector<Flight> flights;

    std::ifstream file("flights.csv");

    if (!file.is_open())
    { 
        std::cerr << "Failed to open file: flights.csv " << std::endl;
        return flights;
    }

    std::string line;

    while (std::getline(file, line)) //reading each line in the file and storing it into 'line' 
    {
        std::stringstream ss(line); //storing the 'line' into the string stream 
        std::string cell; //cell will store each CSV individual value

        std::vector<std::string> row; //row will contain the cells

        while (std::getline(ss, cell, ',')) //reading from ss with ',' delimeter and storing each value into cell
        {
            row.push_back(cell); //push cell into the 'row' array
        }

        Flight newFlight(std::stoi(row[0]), row[1], row[2], row[3], row[4]); //constructing new flight
        flights.push_back(newFlight);
    }

    file.close();

    return flights;
}

bool seatIsTaken(int flightnum, int r, char c, std::map<int, std::vector<std::tuple<int, char>>>  seats)
{

    auto it = seats.find(flightnum);

    for (const auto& seatTuple : it->second) {
        
        if (std::get<0>(seatTuple) == r && std::get<1>(seatTuple) == c) {
            return true;
        }
    }

    return false;

}

void writeToReservationCSV(Reservation reservation)
{
    std::ofstream outputFile;
    outputFile.open("reservations.csv", std::ios::app); //for appending to file

    if (!outputFile.is_open())
    {
        std::cerr << "error opening file. terminating program";
    }

    outputFile << reservation.flightNum << "," << reservation.passenger.id << "," << reservation.seatrow << "," << reservation.seatcol << "," << reservation.confirmation << "\n";
    outputFile.close();
}

std::pair<int, char> getRowandCol()
{

    int row;
    char col;

    std::cout << "Select a row 1 - 10: ";
    std::cin >> row;
    std::cout << "you selected row:" << row;
    std::cout << "Select a column A - E: ";
    std::cin >> col;

    return {row, col};
}

std::pair<std::string, std::string> getFirstandLast()
{

    std::string first;
    std::string last;

    std::cout << "Enter your first name: ";
    std::cin >> first;

    std::cout << "Enter your last name: ";
    std::cin >> last;

    return {first, last};
}

std::map<int, std::vector<Reservation>> getReservations(const std::map<int, Passenger> &passengers)
{
    std::map<int, std::vector<Reservation>> reservations;

    std::ifstream file("reservations.csv");
    if (!file.is_open())
    {
        std::cerr << "Failed to open reservations.csv\n";
        return reservations; // return empty
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        if (row.size() < 4)
        {
            std::cerr << "Malformed row: " << line << "\n";
            continue;
        }

        int passengerID = std::stoi(row[1]);

        //SAFE lookup
        auto passIt = passengers.find(passengerID);

        if (passIt == passengers.end())
        {
            std::cerr << "Passenger ID " << passengerID
                      << " not found in passengers map!\n";
            continue;
        }

        const Passenger &p = passIt->second; // no copy

        //Extract reservation details
        int flightNum = std::stoi(row[0]);
        int rowNum = std::stoi(row[2]);
        char seatCol = row[3][0];
        int confirmation = std::stoi(row[4]);

        //Build reservation
        Reservation r(flightNum, p, rowNum, seatCol, confirmation);

        //Insert directly into vector (auto-creates if missing)
        reservations[p.id].push_back(r);
    }

    return reservations;
}

std::map<int, Passenger> getPassengers()
{
    // read passengers to csv
    // create a map that maps the id -> passenger
    std::ifstream file("passengers.csv");
    std::map<int, Passenger> passengers;

    if (!file.is_open())
    {
        std::cerr << "failed to open 'passengers.csv'" << std::endl;
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        Passenger p(row[0], row[1], std::stoi(row[2]));

        passengers.insert({std::stoi(row[2]), p});
    }
    return passengers;
}

bool askFirstReservation()
{
    char response;

    std::cout << "Have you made a reservation with us before? Enter 'Y' (Yes) or 'N' (No): ";

    std::cin >> response;

    std::cout << "\n";

    return response == 'Y';
}

std::tuple<std::string, std::string, int> getUserInfo()
{

    std::string first;
    std::string last;
    int id;

    std::cout << "Checking to see if you are in our system..." << std::endl;

    std::cout << "Enter your first name: ";
    std::cin >> first;

    std::cout << "Enter your last name: ";
    std::cin >> last;

    std::cout << "Enter your unique id: ";
    std::cin >> id;
    std::cout << "\n";

    return {first, last, id};
}

std::tuple<Passenger, bool> isValidPassenger(std::string first, std::string last, int id, std::map<int, Passenger> &passengers)
{

    auto passIt = passengers.find(id);

    if (passIt == passengers.end()) // user enters wrong ID
    {
        std::cerr << "Passenger ID " << id << " not found in passengers map! Did you enter the correct ID?\n"
                  << std::endl;
        ;
        return {passIt->second, false};
    }
    else if (passIt != passengers.end() && passIt->second.firstName != first || passIt->second.lastName != last) // user enters correct ID, but wrong name
    {
        std::cerr << "ID does not map to passenger name. " << "Did you enter the correct first and last name?\n"
                  << std::endl;
        ;
        return {passIt->second, false};
    }
    else
    {
        if (passIt->second.firstName == first && passIt->second.lastName == last)
        {
            std::cout << "Passenger verified. Hello " << passIt->second.firstName << " " << passIt->second.lastName << std::endl;
            return {passIt->second, true};
        }
    }
}

int generateRandom()
{

    std::random_device rd;                            // non-deterministic random seed
    std::mt19937 gen(rd());                           // mersenne twister engine
    std::uniform_int_distribution<> dist(1000, 5000); // range [1000, 5000]

    int randomNum = dist(gen);

    return randomNum;
}

bool makeReservation(Passenger p, int flightNumber, std::map<int, std::vector<std::tuple<int, char>>> seats)
{

    bool validSeat = false;

    while (!validSeat)
    {

        auto [row, col] = getRowandCol();
        
        if (seatIsTaken(flightNumber, row, col, seats))
        {
            std::cout << "That seat is taken. Enter a new seat.\n"
                      << std::endl;
        }
        else
        {
            int confirmation = generateRandom();

            Reservation r(flightNumber, p, row, col, confirmation);

            writeToReservationCSV(r);

            return true;
        }
    }
}

void displayReservations(std::vector<Reservation> r)
{
    if (r.empty())
    {
        std::cout << "\n╔════════════════════════════════════════╗\n";
        std::cout << "║     No Reservations Found              ║\n";
        std::cout << "╚════════════════════════════════════════╝\n";
        return;
    }

    std::cout << "\n╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                    RESERVATION DETAILS                     ║\n";
    std::cout << "╠════════════════════════════════════════════════════════════╣\n";

    for (size_t i = 0; i < r.size(); i++)
    {
        const auto &res = r[i];

        std::cout << "║ Flight Number: " << std::left << std::setw(42)
                  << res.flightNum << "║\n";

        std::cout << "║ Passenger:     " << std::setw(42)
                  << (res.passenger.firstName + " " + res.passenger.lastName) << "║\n";

        std::string seat = std::to_string(res.seatrow) + res.seatcol;
        std::cout << "║ Seat:          " << std::setw(42) << seat << "║\n";

        std::string con = std::to_string(res.confirmation);
        std::cout << "║ Confirmation:  " << std::setw(42) << con << "║\n";

        if (i < r.size() - 1)
        {
            std::cout << "╟────────────────────────────────────────────────────────────╢\n";
        }
    }

    std::cout << "╚════════════════════════════════════════════════════════════╝\n\n";
}

Passenger createNewPassenger()
{

    std::string first;
    std::string last;
    int id;

    std::cout << "Registering..." << std::endl;

    std::cout << "Enter your first name: ";
    std::cin >> first;

    std::cout << "Enter your last name: ";
    std::cin >> last;

    std::random_device rd;                            // non-deterministic random seed
    std::mt19937 gen(rd());                           // mersenne twister engine
    std::uniform_int_distribution<> dist(1000, 5000); // range [1000, 5000]

    size_t randomNum = dist(gen);

    Passenger p(first, last, randomNum);

    return p;
}

void writeToPassengerCSV(Passenger p)
{
    std::ofstream outputFile;
    outputFile.open("passengers.csv", std::ios::app); // for appending to file

    if (!outputFile.is_open())
    {
        std::cerr << "error opening file. terminating program";
    }

    outputFile << p.firstName << "," << p.lastName << "," << p.id << "\n";
    outputFile.close();
}

bool updateReservationsFile(std::map<int, std::vector<Reservation>> allReservations,
                            int userID, int reservationConfirmation)
{

    std::ofstream newFile("reservationstemp.csv");

    if (!newFile.is_open())
    {
        std::cerr << "Error: Could not create file...\n";
        return false;
    }

    for (const auto &id : allReservations)
    {
        for (const auto &res : id.second)
        {
            if (id.first == userID && res.confirmation == reservationConfirmation)
            {
                continue;
            }
            else
            {
                newFile << res.flightNum << "," << res.passenger.id << ","
                        << res.seatrow << "," << res.seatcol << ","
                        << res.confirmation << "\n";
            }
        }
    }

    newFile.close();

    // Replace the original file with the temp file
    if (std::remove("reservations.csv") != 0)
    {
        std::cerr << "Error deleting original file\n";
        return false;
    }
    if (std::rename("reservationstemp.csv", "reservations.csv") != 0)
    {
        std::cerr << "Error renaming temp file\n";
        return false;
    }

    return true;
}

bool deleteReservation(std::map<int, std::vector<Reservation>> allReservations, std::vector<Reservation> userReservations, int userID)
{
    // r is all reservations for specific passenger

    int chosenConfirmation;
    std::cout << "Enter in a reservation confirmation to delete: ";
    std::cin >> chosenConfirmation;

    for (const auto &reservation : userReservations)
    {
        if (reservation.confirmation == chosenConfirmation)
        {
            // user entered valid reservation -> now update the file
            if (updateReservationsFile(allReservations, userID, chosenConfirmation))
            {
                return true;
            }
        }
    }

    return false;
}

std::map<int, std::vector<std::tuple<int, char>>> getSeats()
{

    std::map<int, std::vector<std::tuple<int, char>>> seats;

    // iterate through reservations file

    std::ifstream file("reservations.csv");
    if (!file.is_open())
    {
        std::cerr << "Failed to open reservations.csv\n";
        return seats; // return empty
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        if (row.size() < 5)
        {
            std::cerr << "Malformed row: " << line << "\n";
            continue;
        }

        int flightNum = std::stoi(row[0]);

        // SAFE lookup
        auto seatIt = seats.find(flightNum);

        // Extract seats details
        int rowNum = std::stoi(row[2]);
        char seatCol = row[3][0];

        std::tuple<int, char> seatTuple(rowNum, seatCol);

        // Insert directly into vector (auto-creates if missing)
        seats[flightNum].push_back(seatTuple);
    }

    return seats;
}

int main()
{
    displayWelcome();
    std::map<int, Passenger> passengers = getPassengers();                              // map that maps id to a passenger
    std::vector<Flight> flights = getFlights();                                         // getting all flight info
    std::map<int, std::vector<Reservation>> reservations = getReservations(passengers); // getting all reservatioms
    std::map<int, std::vector<std::tuple<int, char>>> seats = getSeats();      
    
    char choice = makeChoice();

    if (choice == '1') // making a reservation
    {
        int flightNumber = showFlights(flights); // showing flights and getting flight number
        showAvailableSeats(flightNumber, seats); // showing available seats for flight number

        std::cout << "Above is the available seating for flight " << flightNumber << std::endl;
        std::cout << "\n"
                  << std::endl;

        bool validSeat = false;

        while (!validSeat)
        {
            char notfirstReservation = askFirstReservation();

            if (notfirstReservation) // passenger claims they have made a reservation with us before
            {
                auto [first, last, id] = getUserInfo();

                auto [p, isvalid] = isValidPassenger(first, last, id, passengers);

                if (isvalid)
                {

                    bool success = makeReservation(p, flightNumber, seats);

                    if (success)
                    {
                        validSeat = true;
                    }
                }
            }
            else
            { // first reservation: get first, last name and generate an ID

                Passenger p = createNewPassenger();

                writeToPassengerCSV(p);

                std::cout << "Successfully registered: " << p.firstName << " " << p.lastName << " " << "with id: " << p.id << std::endl;

                bool success = makeReservation(p, flightNumber, seats);

                if (success)
                {
                    validSeat = true;
                }
            }
        }
        std::cout << "\nSeat successfully reserved!" << std::endl;
        ;
    }

    if (choice == '2' || choice == '3')
    {
        std::cout << "\n";

        bool validPassenger = false;

        while (!validPassenger)
        {

            auto [first, last, id] = getUserInfo();

            auto [p, isvalid] = isValidPassenger(first, last, id, passengers);

            if (isvalid)
            {
                // now get reservations based off passenger

                std::vector<Reservation> r = reservations.at(p.id);

                displayReservations(r);

                validPassenger = true;

                if (choice == '3')
                {
                    if (deleteReservation(reservations, r, id))
                    {
                        std::cout << "Successfully deleted reservation!";
                    }
                }
            }
        }
    }

    return 0;
}
