#include "animal.h"

// ANIMAL
Animal::Animal(string name, int age) : name(name), age(age) {
}
// string Animal::toString() {
//     return "Animal: " + name + ", " + to_string(age);
// }

//CAT
Cat::Cat(string name, int age) : Animal(name, age) {
}
string Cat::toString() {
    return "Cat: " + name + ", " + to_string(age);
}


//DOG
Dog::Dog(string name, int age) : Animal(name, age) {
}
string Dog::toString() {
    return "Dog: " + name + ", " + to_string(age);
}
