#include "test.h"

void Test::testAnimal(){vector<unique_ptr<Animal>> animals; animals.emplace_back(make_unique<Cat>("Pus", 3));animals.emplace_back(make_unique<Dog>("Peet", 15));for(const auto& animal : animals) {cout << animal->toString() << endl;}}
