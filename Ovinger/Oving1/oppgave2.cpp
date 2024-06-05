#include "headerfiles/oppgave2.h"
#include <iostream>
#include <string>

/*oppgave 2a*/
int maxOfTwo(int a, int b) {
    if (a > b) {
        std::cout << "a er storre enn b" << std::endl;
        return a;
    } else {
        std::cout << "b er storre eller lik a" << std::endl;
        return b;
    }
}

/*oppgave 2b*/
void oppgaveB() {
    std::string melding = "har eg ikkje kinda gjort det?";
    std::cout << melding << std::endl;
}

/*oppgave 2c*/
int fibonacci(int n) {
    int a = 0;
    int b = 1;
    std::cout<<"Fibonacci nummer:"<< std::endl;
    for(int i=1; i< (n+1); i++){
        std::cout<<i<<" "<<b<< std::endl;
        int temp = b;
        b += a;
        a = temp;
    }
    std::cout<<"----"<< std::endl;
    return b;
}

/*oppgave 2d*/
int squareNumberSum(int n){
    int sum = 0;
    for(int i = 1;i<n+1;i++){
        sum += i*i;
        std::cout<<i*i<< std::endl;
    }
    std::cout<<sum<< std::endl;
    return sum;
}

/*oppgave 2e*/
int triangleNumbersBelow(int n){
    int acc = 1;
    int num = 2;
    std::cout<<"Triangle numbers below "<< n<< ":"<<std::endl;
    while (acc<n){
        std::cout<<acc<< std::endl;
        acc += num;
        num += 1;
    }
    std::cout<<" "<< std::endl;
    return 0;
}
/* nei, det er ikkje mulig å retunere verdien til ein void funksjon til
skjerm då den ikkje retunerer noko verdi.

ein void funksjon har som hensikt å utføre ein oppgaåve utan å gi informasjon tilbake til kalleren
den kan dog utføre operasjoner slik som eg f.eks har brukt void til å kalle påmdissa deloppgåvefunksjonane
som igjen kalles av main.cpp
men den avslutter uten å bruke return-setning for å sende en verdi tilbake.
*/

/*oppgave 2f*/
bool isPrime(int n){
    for(int j =2;j<n;j++){
        if (n%j == 0){
          /*std::cout<< n << " er delig med "<< j<< std::endl;*/  
            return false;
        }
    }
    return true;
}

/*oppgave 2g*/
void naivePrimeNumberSearch(int n){
    for(int i = 2; i <= n; i++){
        /*std::cout<< " eg kjorer gang nr:"<< i << std::endl; */ 
        if (isPrime(i)){
            std::cout<< i << " is a prime" << std::endl;  
        }
    }
}

/*oppgave 2h*/
void inputAndPrintNameAndAge(){
    std::string name;
    std::string age;
    std::cout << "Skriv inn eit navn: ";
    std::cin >> name;
    std::cout << "\nSkriv inn alderen til "<<name<< ": ";
    std::cin >> age;
    std::cout<<"\n"<<name<<" er "<<age<<" aor gammal."<<std::endl;
}



void Oppgave2::run_a() {
    std::cout << "\nKjorer Oppgave 2.a" << std::endl;

    int a = 5;
    int b = 3;
    int max = maxOfTwo(a, b);

    std::cout << "Det storste tallet er ((a,b) = ("<<a<<","<<b<<")): " << max << std::endl;
}

void Oppgave2::run_b() {
    std::cout << "\n" << "Kjorer Oppgave 2.b" << std::endl;
    oppgaveB();
}

void Oppgave2::run_c() {
    std::cout << "\n" << "Kjorer Oppgave 2.c" << std::endl;
    int n = 5;
    int fib = fibonacci(n);
    std::cout << fib << std::endl;
}

void Oppgave2::run_d() {
    std::cout << "\n" << "Kjorer Oppgave 2.d" << std::endl;
    int n = 5;
    int sum = squareNumberSum(n);
    std::cout << sum << std::endl;
}

void Oppgave2::run_e() {
    std::cout << "\n" << "Kjorer Oppgave 2.e" << std::endl;
    int n = 30;
    triangleNumbersBelow(n);

}

void Oppgave2::run_f() {
    std::cout << "\n" << "Kjorer Oppgave 2.f" << std::endl;
    int n = 30;
    bool result = isPrime(n);
    if (result) {
        std::cout << n << " is a prime" << std::endl;
    } else {
        std::cout << n << " is not a prime" << std::endl;
    }
}

void Oppgave2::run_g() {
    std::cout << "\n" << "Kjorer Oppgave 2.g" << std::endl;
    int n = 30;
    naivePrimeNumberSearch(n);
}

void Oppgave2::run_h() {
    std::cout << "\n" << "Kjorer Oppgave 2.h" << std::endl;
    inputAndPrintNameAndAge();
    std::cout << "\n" << "FERDIG" << std::endl;

}