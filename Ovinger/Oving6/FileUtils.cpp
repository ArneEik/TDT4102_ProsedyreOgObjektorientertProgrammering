#include "FileUtils.h"

void writeUserInputToFile()
{
	const filesystem::path filename{"outputfile.txt"};
	ofstream outFile{filename};
	if (!outFile)
	{
		cout << "Couldn't open file: " << filename << endl;
	}

	cout << "Write some words, they will be output in the file"
			" \"outputfile.txt\", every word on separate lines."
			" quit exits\n> ";

	for (string word; cin >> word && word != "quit";)
	{
		outFile << word << '\n';
	}
}

void addLineNumbers(const filesystem::path& filename)
{
	ifstream inFile{filename};
	if (!inFile)
	{
		cout << "Couldn't open file: " << filename << endl;
	}

	ofstream outFile{filename.string() + ".linum"};
	if (!outFile)
	{
		cout << "Couldn't open file: " << filename.string() +".linum" << endl;
	}

	int lineNumber = 1;
	for (string line; getline(inFile, line); ++lineNumber)
	{
		outFile << lineNumber << ": " << line << '\n';
	}
}