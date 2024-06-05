#pragma once


class Car{
private:
    int _freeSeats;

public:
    Car(int freeSeats) : _freeSeats(freeSeats) {};
    
    bool hasFreeSeats() const {return _freeSeats >= 1;};
    void reserveFreeSeat() {if (hasFreeSeats()) { --_freeSeats; }};


};