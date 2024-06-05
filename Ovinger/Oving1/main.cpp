#include "std_lib_facilities.h"
#include "include.h"
#include <iostream>
#include <cstdlib>  // For system()

int main() {
    // Kjører Python-baserte oppgaver
    cout << "\n--- Oppgave 1 (Python) ---\n";
    system("python3 ../oppgave1.py");
    
    cout << "\n--- Oppgave 2 (C++) ---\n";
    Oppgave2 oppgave2;
    oppgave2.run_a();  
    oppgave2.run_b();
    oppgave2.run_c(); 
    oppgave2.run_d(); 
    oppgave2.run_e();   
    oppgave2.run_f(); 
    oppgave2.run_g(); 
    oppgave2.run_h(); 

    return 0;
}

/*
Ser at handind.zip ikkje tar med alle deler av programet (det som ikkje ligger i root)
hovudsakelig tar den ikkje med headerfila til oppgave 2 
som ser slik ut:
--------------------------
#ifndef OPPGAVE2_H
#define OPPGAVE2_H

class Oppgave2 {
public:
    void run_a();  
    void run_b();  
    void run_c();  
    void run_d();  
    void run_e();  
    void run_f(); 
    void run_g();  
    void run_h();  
};

#endif
-----------------------

I dinna oppgava er oppgave 1 besvart i python (oppgave1.py) og brukt system() 
for å compile med main fila.
Oppgave2 er besvart i oppgave2.cpp og  bruker header fila oppgave2.h (utsnitt over)
som egentlig ligger i mappa headerfiles der klassen: oppgave2, er definert
*/