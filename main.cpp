#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <format>
#include <filesystem>
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

void showAvailableSeats(int flightnumber) {

    //get available seats but for flight number... implement this later

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

int showFlights(std::vector<Flight> flights) {

    for (const auto& flight : flights) {
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

int convertCol(char col) {

    switch (col) {
        case 'A':
            return 1;
        case 'B':
            return 2;
        case 'C':
            return 3;
        case 'D':
            return 4;
        case 'E':
            return 5;
        default:
            break;
    }
    return col;
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

        Flight newFlight(std::stoi(row[0]), row[1], row[2], row[3], row[4]); //constructing new flight
        flights.push_back(newFlight);
    }
    file.close();

    return flights;
}

bool seatIsTaken(int flightnum, int r, char c) {
    //query reservations.csv by flight number
    //find all reservatons by flight number and store in std::vector<Reservations>

    std::ifstream file("reservations.csv");

    if (!file.is_open()) {
        std::cerr << "failed to check reservations" << std::endl;
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

        std::string new_cell = row[4];
        char char_row = new_cell[0];

        if (std::stoi(row[0]) == flightnum && (std::stoi(row[3]) == r && char_row == c))  {
                return true;
        }
         
    }
    return false;
}

int main()
{

    displayWelcome();
    char choice = makeChoice();

    if (choice == '1') //booking a flight
    {
        // load in flight info from flights.csv
        // store in vector of Flight objects
        auto flights = getFlights();
        int flightNumber = showFlights(flights);
        showAvailableSeats(flightNumber);

        std::cout << "Above is the available seating for flight ";
        std::cout << flightNumber << std::endl;
        
        int row;
        char col;

        std::cout << "Select a row 1 - 10: ";
        std::cin >> row;
        std::cout << "Select a column A - E: ";
        std::cin >> col;
      
        if (seatIsTaken(flightNumber, row, col)) {
            //checking if the seat is taken
            std::cout << "seat is taken";
        } else {
            std::cout << "seat is not taken";
            //save char col to file, not int col
        }
    
    }

    return 0;
}
