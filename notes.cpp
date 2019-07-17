#include "main.h"
#include "notes.h"

int Notes::maxNotes;
Note Notes::m_Notes[NOTES_MAX];

std::vector<std::string> Notes::split(std::string& input, char delimiter)
{
	std::istringstream stream(input);
	std::string field;
	std::vector <std::string> result;
	while (getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}

void Notes::Load(char* fileName) {
	std::ifstream ifs(fileName);
	std::string line;
	maxNotes = 0;
	std::vector<std::string> strvec;

	int cnt = 0;
	while (std::getline(ifs, line)) {
		strvec = split(line, ',');
		for (int i = 0; i < strvec.size(); i += strvec.size()) {
			m_Notes[maxNotes].time = stof(strvec.at(i));
			m_Notes[maxNotes].rane = stoi(strvec.at(i + 1));
			maxNotes++;
		}
	}
}