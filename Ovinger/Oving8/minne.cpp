#include <iostream>
#include <cassert>
#include "minne.h"

void fib(int* result, int length){
    assert(length >= 1);
    result[0] = 0;
    if (length == 1){return;}

    result[1] = 1;
    for (int i = 2;i<length;i++){
        result[i] = result[i-1] + result[i-2];
    }
}

void printArray(int* arr, int length){
        for (int i = 0; i<length; i++){
        std::cout<<arr[i]<<", ";
    }
    std::cout<<std::endl;
}

void lagfib()
{
    int n{0};
    std::cout<<"kor mange tall?: \n";
    std::cin>>n;

    int* result = new int[n];
    fib(result, n);
    printArray(result, n);
    delete[] result;
    result = nullptr;

}