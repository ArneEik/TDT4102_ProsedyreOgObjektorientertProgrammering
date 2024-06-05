#include "include.h"

int Utilities::incrementByValueNumTimes(int v0, int  increment, int iterations){
    for (int i = 0; i < iterations; i++) {
        v0 += increment;
        }
        return v0;
}
void Utilities::incrementByValueNumTimesRef(int& startValue, int increment, int numTimes) {
    for (int i = 0; i < numTimes; i++) {
        startValue += increment;
    }
}
void Utilities::swapNumbers(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
void Utilities::printStudent(const Student& student) {
    cout<< "Name: " << student.name << "\n"
        << "Study Program: " << student.studyProgram << "\n"
        << "Age: " << student.age << endl;
}
bool Utilities::isInProgram(const Student& student, const string& program) {
    return student.studyProgram == program;
}
Student Utilities::createStudent(const string& name, const string& studyProgram, int age) {
    Student newStudent;
    newStudent.name = name;
    newStudent.studyProgram = studyProgram;
    newStudent.age = age;
    return newStudent;
}
double Utilities::randomWithLimits(double lower, double upper) {
    random_device rd;  
    default_random_engine generator(rd()); 
    uniform_real_distribution<double> distribution(lower, upper); 
    return distribution(generator);  
}
string Utilities::randomizeString(int length, char lowerLimit, char upperLimit) {
    string randomizedString;
    for (int i = 0; i < length; ++i) {
        char randomChar = static_cast<char>(Utilities::randomWithLimits(lowerLimit, upperLimit));
        randomizedString += randomChar;
    }
    return randomizedString;
}
string Utilities::readInputToString(int n, char lowerLimit, char upperLimit){
    string result;
    bool valid = false;

    while (!valid) {
        cout << "\nSkriv inn " << n << " tegn mellom " << lowerLimit << " og " << upperLimit << ": ";
        getline(std::cin, result);

        if (result.length() != n) {
            std::cout << "\nInndata må være nøyaktig " << n << " tegn lang. ";
            continue; // Be om inndata på nytt
        }

        for (char &c : result) {
            c = toupper(c);
        }

        if (all_of(result.begin(), result.end(), 
            [lowerLimit, upperLimit](char c) { 
                return c >= toupper(lowerLimit) && c <= toupper(upperLimit); 
            })) {
            valid = true; // Gyldig inndata
        } else {
            cout << "\nUgyldig inndata. ";
        }
    }
    return result;
}

int Utilities::countChar(const string& str, char c) {
    int count = 0;
    for (char ch : str) {
        if (ch == c) {
            count++;
        }
    }
    return count;
}
