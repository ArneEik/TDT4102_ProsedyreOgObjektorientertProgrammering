#include "include.h"

void Tests::testCallByValue() {
int v0 = 5;
int increment = 2;
int iterations = 10;
int result = utils.incrementByValueNumTimes(v0, increment, iterations);
cout << "v0: " << v0
<< " increment: " << increment
<< " iterations: " << iterations
<< " result: " << result << endl;
}
void Tests::testCallByReference() {
    int v0 = 5;
    int increment = 2;
    int iterations = 10;
    utils.incrementByValueNumTimesRef(v0, increment, iterations);
    cout << "v0: " << v0
         << " increment: " << increment
         << " iterations: " << iterations << endl;
}
void Tests::testSwapAB(){
    int a, b;
    cout<<"velg a: ";
    cin>>a;
    cout<<"velg b:";
    cin>>b;
    utils.swapNumbers(a,b);
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
}
void Tests::testString(){
    int n = 8;
    vector<int> gradeCount(6, 0);  // Vektor med 6 elementer (A-F), initialisert til 0
    string grades = utils.randomizeString(n, 'A', 'G');// må ha med G for å få med F
    //cout << "Grades string: " << grades << endl;

    // Teller forekomster av hver karakter
    for (char grade = 'A'; grade <= 'F'; ++grade) {
        gradeCount[grade - 'A'] = utils.countChar(grades, grade);
    }

    // Beregner gjennomsnittskarakteren
    double average = 0.0;
    for (int i = 0; i < 6; ++i) {
        // A tilsvarende 6, B tilsvarende 5, osv.
        average += (6 - i) * gradeCount[i];
    }
    average /= n;  // Dividerer med totalt antall karakterer

    cout << "Average grade: " << average << endl;
}
