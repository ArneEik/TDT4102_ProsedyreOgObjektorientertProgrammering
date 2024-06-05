
#include "Meeting.h"

std::vector<std::string> Meeting::getParticipantList()
{
    std::vector<std::string> ParticipanlList;
    for( const auto & member : _participants){ //E kanskje feil med & her, ane ikkje kvifor
        ParticipanlList.push_back(member->getName());
    }
    return ParticipanlList;
}
std::vector<std::shared_ptr<Person>> Meeting::findPotentialCoDriving(const Meeting& m) const
{
	std::vector<shared_ptr<Person>> potentialDrivers;
	if (m._location == _location && m._day == _day
		&& abs(m._startTime - this->_startTime) <= 1 && abs(m._endTime - _endTime) <= 1) {

		for (const shared_ptr<Person> &p : m._participants) {
			if (p->hasAvailableSeats()) {
				potentialDrivers.push_back(p);
			}
		}
	}

	return potentialDrivers;
}
std::ostream& operator<<(std::ostream& os, Meeting& m)
{
	os << m.getSubject() << "-meeting at " << m.getLocation() << " campus, "
	   << "from " << m.getStartTime() << " to " << m.getEndTime() << " by " << m.getLeader()->getName()
	   << "\n > Participants:";

	auto participants{m.getParticipantList()};
	for (const auto& p : participants) { // Alternativt: for (const string& p:. participants)
		os << " " << p;
	}

	return os;
}





