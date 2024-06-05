#pragma once
#include <iostream>
#include <utility>
class Dummy {
public:
    int *num;
    Dummy() {
        num = new int{0};
    }
    ~Dummy() {
        delete num;
    }
    Dummy(const Dummy & rhs) : Dummy{} {
        *num =  *rhs.num;
    }
    Dummy &operator=(Dummy &rhs){
        std::swap(this->num, rhs.num);
        return *this;
    }
};