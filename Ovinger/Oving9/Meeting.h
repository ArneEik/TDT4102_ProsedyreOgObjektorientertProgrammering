#pragma once
#include "Person.h"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "std_lib_facilities.h"

enum class Campus{tro, aal, gjo};

const std::unordered_map<Campus, std::string> campusToString{
        {Campus::tro,"Trondheim"},
        {Campus::aal, "Aalesund"},
        {Campus::gjo, "Gjovik"}
};

std::ostream& operator<<(ostream& os, Campus c){
    return os<<campusToString.at(c);
}

class Meeting {
private:
    int _day;
    int _startTime;
    int _endTime;
    Campus _location;
    std::string _subject;
    const std::shared_ptr<Person> _leader;
    vector<std::shared_ptr<Person>> _participants;

public:
    Meeting(int day, int startTime, int endTime, Campus location, std::string subject, std::shared_ptr<Person> leader) :
    _day(day), _startTime(startTime), _endTime(endTime), _location(location), _subject(subject), _leader(leader)
    {
        _participants.push_back(leader);
    } 

    int getDay(){return _day;}
    int getStartTime(){return _startTime;}
    int getEndTime(){return _endTime;}
    Campus getLocation(){return _location;}
    std::string getSubject(){return _subject;}
    auto getLeader() {return _leader;}

    void addParticipant(std::shared_ptr<Person> p){_participants.push_back(p);}
    std::vector<std::string> getParticipantList();
    std::vector<std::shared_ptr<Person>> findPotentialCoDriving(const Meeting& m) const;
};

std::ostream& operator<<(std::ostream& os, Meeting& m);