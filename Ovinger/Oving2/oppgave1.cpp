#include "subprojects\std_lib_facilities\std_lib_facilities.h"
#include "oppgave1.h"

//b)
void Oppgave1::inputAndPrintInteger(){
    int bTall;
    cout<<"velg eit tall: ";
    cin>>bTall;
    cout<<"Du skrev: " << bTall<< endl;
}
//c)
string Oppgave1::inputInteger(){
    int bTall;
    string output;
    cout<<"velg eit tall: ";
    cin>>bTall;
    output = "Du skrev: " + to_string(bTall); 
    return output;
}
//d)
int Oppgave1::inputIntegersAndPrintSum(){
    int a;
    int b;
    cout<<"skriv ditt første tall: ";
    cin>>a;
    cout<<"\nskriv dit andre tall: ";
    cin>>b;
    return a+b;
    
}
//e) fordi c retunerer string ditt problem
//f)
bool Oppgave1::isOdd(int n){
    if (n%2 ==0){
        return false;
    }
    return true;
} 

//a)
void Oppgave1::chooseTask() {
    int pick;
    bool validPick = false;

    while (!validPick) { 
        cout << "Velg funksjon: \n"
             << "0) Tilbake\n"
             << "1) Summer to tall\n"
             << "2) Summer flere tall\n"
             << "3) Konverter NOK til EURO\n"
             << "4) InputAndPrintInteger\n"
             << "5) InputInteger\n"
             << "6) InputIntegersAndPrintSum\n"
             << "7) IsOdd\n"
             << "Angi valg (0-7): ";
        cin >> pick;

            switch (pick) {
                case 0:
                    cout << "Du har avsluttet\n";
                    validPick = true;
                    break;
                case 1:
                    cout<<"veit ikkje koffor den sku vere her??\nkjem i oppgave 2"<<endl;
                    break;
                case 2:
                    cout<<"veit ikkje koffor den sku vere her??\nkjem i oppgave 2"<<endl;
                    break;
                case 3:
                    cout<<"veit ikkje koffor den sku vere her??\nkjem i oppggave 2"<<endl;
                    break;
                case 4:
                    cout<<Oppgave1::inputInteger()<<endl;
                    break;
                case 5:
                    Oppgave1::inputAndPrintInteger();
                    break;
                case 6:
                    cout<<Oppgave1::inputIntegersAndPrintSum()<< endl;
                    break;
                case 7:
                    for(int i = 0; i<15; i++){
                        cout<<(Oppgave1::isOdd(i) ? "true\n" : "false\n");
                    }
                    break;
                default:
                    cout << "Ikke gyldig valg, prøv igjen\n";
                    break;
            }
    }
}
