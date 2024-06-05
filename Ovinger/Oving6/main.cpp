#include "std_lib_facilities.h"
#include "CourseCatalog.h"
#include "FileUtils.h"
#include "bouncingBall.h"

void testCourseCatalog();

int main()
{
	// Skriver brukerinput til fil
	writeUserInputToFile();
	
	// Leser fra fil og skriver innholdet til ny fil,<filename>.linum med linjenummer 
	addLineNumbers("outputfile.txt");

	testCourseCatalog();
	cout << "\n";

	bouncingBall();

	return 0;
}

void testCourseCatalog() {
	CourseCatalog cc;
	filesystem::path filename = "coursecatalog.txt";

	// CourseCatalog::loadFromFile() vil kaste et unntak hvis filen ikke eksiterer
	try {
		cc.loadFromFile(filename);
		cout << "These courses are already in the catalog loaded from " << filename << ":\n";
		cout << cc;
	}
	catch (exception& e) {
		cout << e.what() << '\n';
	}


	cout << "\nAdding/updating the catalog.\n";
	cc.addCourse("TDT4110", "Informasjonsteknologi grunnkurs");
	cc.addCourse("TDT4102", "Prosedyre- og objektorientert programmering");
	cc.addCourse("TMA4100", "Matematikk 1");
	cout << cc;

	cout << "\nUpdating course name for TDT4102:\n";
	cc.addCourse("TDT4102", "C++");
	cout << cc;

	cc.saveToFile(filename);
	cout << "\nCourse catalog is stored in " << filename << '\n';
}
