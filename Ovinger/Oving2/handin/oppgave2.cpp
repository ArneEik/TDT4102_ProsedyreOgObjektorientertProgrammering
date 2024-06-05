#include "subprojects\std_lib_facilities\std_lib_facilities.h"
#include "oppgave2.h"
//a)
int Oppgave2::sumTall(){
    int n;
    int t;
    cout<<"kor mange tall vil du summere?";
    cin>>n;
    int sum{0};
    for(int i = 0; i<n; i++){
        cout<< "skriv tall nr"<<i+1<<": ";
        cin>>t;
        sum +=t;
    }
    return t;
}
//b)
void Oppgave2::sumWhileNotZero(){
    int t;
    int count = 1;
    int sum{0};
    bool validChoice = false;
    cout<< "teller til du skriver 0\n";
    while(!validChoice){
        cout<< "skriv tall nr"<< count<<": ";
        cin>>t;
        if(t==0){
            validChoice = true;
        }
        sum +=t;
        count++;
        cout<<endl;
    }
    cout<< "summen vart: "<< sum<<endl;
}
//c) dei eg brukte

//d)
double Oppgave2::inputDouble(){
    double t;
    cout<<"skriv eit deismaltal(bruk '.'): ";
    cin>>t;
    return t;
}
//e)
void Oppgave2::NOKtoEURO(){
    double OneNokInEuro = 9.75;
    double nok;
    bool validChoice = false;
    while (!validChoice)
    {
        cout<< "skriv tall nr : ";
        cin>>nok;
        if (nok>=0){
            validChoice = true;
        }
        cout<< "må vere positivt \n";
    }
    double NokToEuro = nok/OneNokInEuro;
    cout<< fixed << setprecision(2)<<NokToEuro<<"EUR\n";
}
//f)
//Brkte void så eg slapp å skrive noko i main (sku eg retunert tall, måtte eg brukt double)
//må bruke double fordi desimal

//g)
void Oppgave2::multiplucationTable() {
    int width, height;
    cout << "Enter width: ";
    cin >> width;
    cout << "Enter height: ";
    cin >> height;

    MultiplicationTable table(width, height);
    cout << table;
}

ostream& operator<<(ostream& os, const Oppgave2::MultiplicationTable& mt) {
    for (int i = 1; i <= mt.height; ++i) {
        for (int j = 1; j <= mt.width; ++j) {
            os << setw(4) << i * j;
        }
        os << endl;
    }
    return os;
}
void Oppgave2::chooseTask() {
    int pick;
    bool validPick = false;

    while (!validPick) { 
        cout << "Velg funksjon: \n"
             << "0) Tilbake\n"
             << "1) (a) sumTall\n"
             << "2) (b) sumWhileNotZero\n"
             << "3) inputDouble\n"
             << "4) Konverter NOK til EURO\n"
             << "5) multiplucationTable\n"
             << "Angi valg (0-5): ";
        cin >> pick;

        switch (pick) {
            case 0:
                validPick = true;
                break;
            case 1:
                cout << Oppgave2::sumTall() << endl;
                break;
            case 2:
                Oppgave2::sumWhileNotZero();
                break;
            case 3:
                cout << Oppgave2::inputDouble() << endl;
                break;
            case 4:
                Oppgave2::NOKtoEURO();
                break;
            case 5:
                Oppgave2::multiplucationTable();
                break;
            default:
                cout << "Ikke gyldig valg, prøv igjen\n";
                break;
        }
    }
}
