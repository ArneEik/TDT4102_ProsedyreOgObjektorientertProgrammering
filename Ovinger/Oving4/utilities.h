#pragma once

struct Student{
public:
    string name;
    string studyProgram;
    int age;
};

class Utilities{
private:

public:
    int incrementByValueNumTimes(int v0, int  increment, int iterations);
    void incrementByValueNumTimesRef(int& startValue, int increment, int numTimes);
    void swapNumbers(int& a, int& b);
    void printStudent(const Student& student);
    bool isInProgram(const Student& student, const std::string& program);
    Student createStudent(const std::string& name, const std::string& studyProgram, int age);
    string randomizeString(int length, char lowerLimit, char upperLimit);
    double randomWithLimits(double lower, double upper);
    string readInputToString(int n, char lowerLimit, char upperLimit);
    int countChar(const string& str, char c);

};


// Frie funksjoner
