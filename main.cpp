#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <format>
#include <filesystem>
#include <map>
#include <typeinfo>
#include <tuple>
#include "Passenger.hpp"
#include "Flight.hpp"
#include "Reservation.hpp"

void displayWelcome()
{
    std::cout << "|--------------------------|" << std::endl;
    std::cout << "|Airline Reservation System|" << std::endl;
    std::cout << "|--------------------------|" << std::endl;
    std::cout << "|1. Book Flight            |" << std::endl;
    std::cout << "|2. View Reservations      |" << std::endl;
    std::cout << "|3. Cancel Booking         |" << std::endl;
    std::cout << "|4. Exit                   |" << std::endl;
    std::cout << "|--------------------------|" << std::endl;
}

void showAvailableSeats(int flightnumber)
{

    // get available seats but for flight number... implement this later
    // get all reservations by flight number
    // get all seats and then fill in with x if taken

    std::cout << "\n";
    std::cout << "      AIRPLANE SEATING CHART" << std::endl;
    std::cout << "     =========================" << std::endl;
    std::cout << "\n";
    std::cout << "           [COCKPIT]" << std::endl;
    std::cout << "     _____________________" << std::endl;
    std::cout << "    |                     |" << std::endl;
    std::cout << "    |  A  B     C  D  E   |" << std::endl;
    std::cout << "    |                     |" << std::endl;
    std::cout << " 1  |  O  O     O  O  O   |" << std::endl;
    std::cout << " 2  |  O  O     O  O  O   |" << std::endl;
    std::cout << " 3  |  O  O     O  O  O   |" << std::endl;
    std::cout << " 4  |  O  O     O  O  O   |" << std::endl;
    std::cout << " 5  |  O  O     O  O  O   |" << std::endl;
    std::cout << " 6  |  O  O     O  O  O   |" << std::endl;
    std::cout << " 7  |  O  O     O  O  O   |" << std::endl;
    std::cout << " 8  |  O  O     O  O  O   |" << std::endl;
    std::cout << " 9  |  O  O     O  O  O   |" << std::endl;
    std::cout << "10  |  O  O     O  O  O   |" << std::endl;
    std::cout << "    |                     |" << std::endl;
    std::cout << "    |_____________________|" << std::endl;
    std::cout << "\n";
    std::cout << "    O = Available   X = Taken" << std::endl;
    std::cout << "\n";
}

int showFlights(std::vector<Flight> flights)
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
    { // failed to open file
        std::cerr << "Failed to open file: flights.csv " << std::endl;
        return flights;
    }

    std::string line;

    while (std::getline(file, line))
    {

        std::vector<std::string> row; // vector of strings
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell);
        }

        Flight newFlight(std::stoi(row[0]), row[1], row[2], row[3], row[4]); // constructing new flight
        flights.push_back(newFlight);
    }
    file.close();

    return flights;
}

bool seatIsTaken(int flightnum, int r, char c)
{
    // query reservations.csv by flight number
    // find all reservatons by flight number and store in std::vector<Reservations>

    std::ifstream file("reservations.csv");

    if (!file.is_open())
    {
        std::cerr << "failed to open 'reservations.csv'" << std::endl;
        return false;
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

        std::string new_cell = row[3];
        char char_row = new_cell[0];


        if (std::stoi(row[0]) == flightnum && (std::stoi(row[2]) == r && char_row == c))
        {
            return true;
        }
            
    }
    return false;
}

void writeToReservationCSV(Reservation reservation)
{
    std::ofstream outputFile;
    outputFile.open("reservations.csv", std::ios::app); // for appending to file

    if (!outputFile.is_open())
    {
        std::cerr << "error opening file. terminating program";
    }

    std::cout << reservation.passenger.firstName;

    outputFile << reservation.flightNum << "," << reservation.passenger.firstName << "," << reservation.passenger.lastName << "," << reservation.seatrow << "," << reservation.seatcol << "\n";
    outputFile.close();
}

std::pair<int, char> getRowandCol()
{

    int row;
    char col;

    std::cout << "Select a row 1 - 10: ";
    std::cin >> row;
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

        // SAFE lookup
        auto passIt = passengers.find(passengerID);

        if (passIt == passengers.end())
        {
            std::cerr << "Passenger ID " << passengerID
                      << " not found in passengers map!\n";
            continue;
        }

        const Passenger &p = passIt->second; // no copy

        // Extract reservation details
        int flightNum = std::stoi(row[0]);
        int rowNum = std::stoi(row[2]);
        char seatCol = row[3][0];

        // Build reservation
        Reservation r(flightNum, p, rowNum, seatCol);

        // Insert directly into vector (auto-creates if missing)
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

    std::cout << "Enter your unique id";
    std::cin >> id;

    return {first, last, id};
}

Passenger isValidPassenger(std::string first, std::string last, int id, std::map<int, Passenger> &passengers)
{

    auto passIt = passengers.find(id);

    if (passIt == passengers.end())
    {
        std::cerr << "Passenger ID " << id
                  << " not found in passengers map! Did you enter the correct ID?\n";
    }
    else
    {
        if (passIt->second.firstName == first && passIt->second.lastName == last)
        {
            return passIt->second;
        }
    }
}

bool makeReservation(Passenger p, int flightNumber)
{

    bool validSeat = false;

    while (!validSeat)
    {
        auto [row, col] = getRowandCol();

        std::cout << "the type of row is: " << typeid(row).name() << std::endl;
        std::cout << "the data of row is: " << row << std::endl;

        std::cout << "the type of col is: " << typeid(col).name() << std::endl;
        std::cout << "the data of col is: " << col << std::endl;

        
        if (seatIsTaken(flightNumber, row, col))
        {
            std::cout << "seat is taken" << std::endl;
        }
        else
        {
            bool validSeat = true;

            Reservation r(flightNumber, p, row, col);

            writeToReservationCSV(r);
            return true;
        }
    }
}

int main()
{

    displayWelcome();
    std::map<int, Passenger> passengers = getPassengers(); // map that maps id to a passenger
    std::vector<Flight> flights = getFlights();
    std::map<int, std::vector<Reservation>> reservations = getReservations(passengers);

    char choice = makeChoice();

    if (choice == '1') // booking a flight
    {

        int flightNumber = showFlights(flights); // showing flights and getting flight number
        showAvailableSeats(flightNumber);        // showing available seats for flight number

        std::cout << "Above is the available seating for flight " << flightNumber << std::endl;
        ;

        bool validSeat = false;

        while (!validSeat)
        {

            char firstReservation = askFirstReservation();

            if (firstReservation)
            {

                auto [first, last, id] = getUserInfo();

                Passenger p = isValidPassenger(first, last, id, passengers);

                bool success = makeReservation(p, flightNumber);
            }
        }
    }

    return 0;
}
