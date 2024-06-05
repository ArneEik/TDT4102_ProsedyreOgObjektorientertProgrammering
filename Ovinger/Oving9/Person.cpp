#include "Person.h"

Person::Person(const std::string& name, const std::string& email, unique_ptr<Car> car)
    : _name(name), _email(email), _car(std::move(car))
{}

std::ostream& operator<<(std::ostream& os, const Person& p){
    string hasCar;
    string hasSeats = "";
    if (p._car != nullptr){
        hasCar = "has car";
        if (p._car->hasFreeSeats()){
            hasSeats = " and has seats";
        }else{
            hasSeats = ", but dont have seats";
        }
    } else{
        hasCar = "dont have car";
    }
    os<<"name: "<<p.getName()<<"\nemail: "<<p.getEmail()<<endl<<hasCar<<hasSeats<<endl;
    return os;
}