#pragma once
#include "std_lib_facilities.h"

class CourseCatalog
{
public:
	void addCourse(const string& key, const string& value);
	void removeCourse(const string& key);
	string getCourse(const string& key) const;
	friend ostream& operator<<(ostream& os, const CourseCatalog& cc);

	void saveToFile(const filesystem::path& filename) const;
	void loadFromFile(const filesystem::path& filename);

private:
	map<string, string> courses;
};
