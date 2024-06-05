#pragma once
#include "Car.h"
#include <memory>
#include <string>
#include <iostream>
#include "std_lib_facilities.h"

class Person{
private:
    std::string _name;
    std::string _email;
    std::unique_ptr<Car> _car;

public:
    Person(const std::string& name, const std::string& email, unique_ptr<Car> car = nullptr);

    std::string getName() const {return _name;}
    std::string getEmail() const {return _email;}

    void getEmail(std::string email) {_email = email;}

    bool hasAvailableSeats() {return _car->hasFreeSeats();}

    friend std::ostream& operator<<(std::ostream &os, const Person& p);
};