#include <iostream>
#include "Passenger.hpp"
#include "Flight.hpp"

// keep function as-is; tests will link against this TU by including a forward declaration
void displayWelcome() {
    std::cout << "|--------------------------|" << std::endl;
    std::cout << "|Airline Reservation System|" << std::endl;
    std::cout << "|--------------------------|" << std::endl;
    std::cout << "|1. Book Flight            |" << std::endl;
    std::cout << "|2. View Reservations      |" << std::endl; 
    std::cout << "|3. Cancel Booking         |" << std::endl;
    std::cout << "|4. Exit                   |" << std::endl;
    std::cout << "|--------------------------|" << std::endl;
}

int main() {

    displayWelcome();
    int choice;
    std::cout << "Make your selection: ";
    std::cin >> choice;

    Passenger p1("aaron", "bernstein");

    std::cout << p1.firstName;

    return 0;
}
