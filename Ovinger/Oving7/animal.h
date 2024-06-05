#pragma once
#include "std_lib_facilities.h"
// subprojects\std_lib_facilities\std_lib_facilities.h

class Animal{
protected:
    string name;
    int age;

public:
    Animal(string name, int age);    
    virtual ~Animal(){};
    virtual string toString() = 0;  //virtual string toString();
};

class Cat : public Animal{
public:
    Cat(string name, int age);
    virtual string toString() override;
};

class Dog : public Animal { // Arver public fra Animal
public:
    Dog(string name, int age); 
    virtual string toString() override; // Overstyrer toString()-funksjonen
};