#ifndef OPPGAVE5_H
#define OPPGAVE5_H
#include "subprojects\std_lib_facilities\std_lib_facilities.h"

class Oppgave5 {
public:
    class BankAccountBalances {
    public:
        vector<int> balances;
        BankAccountBalances(const vector<int>& balances) : balances(balances){}//konstruktør
        friend ostream& operator<<(ostream& os, const BankAccountBalances& bab);
    };
    BankAccountBalances currentBalances;
    Oppgave5() : currentBalances(vector<int>{}) {}//konstruktør
    
    void chooseTask(); 
    vector<int> calculateBalance(int deposit, int interest, int years);
    void printBalance();
    
};

#endif
