#ifndef OPPGAVE2_H
#define OPPGAVE2_H
#include "subprojects\std_lib_facilities\std_lib_facilities.h"

class Oppgave2{
public:
    class MultiplicationTable {
    private:
        int width, height;

    public:
        MultiplicationTable(int w, int h) : width(w), height(h) {}
        friend ostream& operator<<(ostream& os, const MultiplicationTable& mt);
    };

    MultiplicationTable table;
    void chooseTask();
    int sumTall(); //a
    void sumWhileNotZero(); //b
    double inputDouble(); //c
    void NOKtoEURO(); //d
    void multiplucationTable();//g
    Oppgave2() : table(0, 0) {}
};


#endif