#pragma once;
#include "std_lib_facilities.h"

template<typename T, int Size>
class myArray{
    private:
    T elements[Size];
    public:
    int getSize() const {return Size;}

    T &at(int index) {
        if (index < 0 || index>= Size){
            throw out_of_range("out of range");
        }
        return elements[index];
    }
    void fill(T &value){
        for(auto& element:elements){
            element = value;
        }
    }
};
