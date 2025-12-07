# Airline Reservation System

A C++ console application for managing flight reservations with seat selection and booking capabilities.

## Features

- **Flight Management**: View available flights and seat availability
- **Seat Reservation**: Interactive seat selection with visual seating chart
- **Booking System**: Create and manage passenger reservations
- **Persistent Storage**: Save and load reservation data using file handling
- **Visual Interface**: ASCII-based airplane seating chart display

## Technical Implementation

- **Object-Oriented Design**: Utilizes classes and encapsulation for flights, passengers, and reservations
- **STL Containers**: Implements `std::map`, `std::vector`, and `std::tuple` for efficient data management
- **File I/O**: Persistent data storage using C++ file handling streams
- **Modern C++**: Leverages `auto`, lambda functions, and standard library features

## Requirements

- C++11 or later
- Standard C++ compiler (g++, clang++, MSVC)

## Usage

Compile and run the program to access the main menu with options for:
- Viewing available flights
- Booking seats
- Checking reservation status
- Managing flight data

## Data Structures

- Flights stored as key-value pairs with flight numbers and seat assignments
- Seat representation using tuples for row and column positions
- Efficient lookup and modification using STL containers
