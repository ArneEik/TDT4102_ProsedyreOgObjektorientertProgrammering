#include "subprojects\std_lib_facilities\std_lib_facilities.h"
#include "subprojects\animationwindow\include\AnimationWindow.h"
#include "oppgave5.h"

vector<int> Oppgave5::calculateBalance(int deposit, int interest, int years) {
    vector<int> balances(years + 1);
    balances[0] = deposit;

    for (int year = 1; year <= years; year++) {
        double balance = deposit * pow((1 + static_cast<double>(interest) / 100), year);
        balances[year] = static_cast<int>(round(balance));
    }
    return balances;
}

void Oppgave5::printBalance() {
    int deposit, interest, years;
    cout << "Angi innskudd: ";
    cin >> deposit;
    cout << "Angi rente (i prosent): ";
    cin >> interest;
    cout << "Angi antall år: ";
    cin >> years;

    BankAccountBalances bab(calculateBalance(deposit, interest, years));
    cout << bab;
}

ostream& operator<<(ostream& os, const Oppgave5::BankAccountBalances& bab) {
    os << "Aor  Saldo\n";
    for (int i = 0; i < bab.balances.size(); ++i) {
        os << setw(2) << i << "  " << setw(6) << bab.balances[i] << endl;
    }
    return os;
}


void Oppgave5::chooseTask() {
    int pick;
    bool validPick = false;

    while (!validPick) { 
        cout << "Velg funksjon: \n"
             << "0) Tilbake\n"
             << "1) Berekn og skriv ut saldo\n"
             << "Angi valg (0-1): ";
        cin >> pick;

        switch (pick) {
            case 0:
                validPick = true;
                break;
            case 1:
                Oppgave5::printBalance();
                break;
            default:
                cout << "Ikke gyldig valg, prøv igjen\n";
                break;
        }
    }
}