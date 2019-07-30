#include <list>
#include "main.h"
#include "notes.h"

int Notes::maxNotes;
int Notes::m_createLeadNoteNumber;
int Notes::m_playingNoteNumber;
Note Notes::m_Notes[NOTES_MAX];
std::vector <Note> g_Notes;

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
	m_createLeadNoteNumber = 0;
	std::vector<std::string> strvec;

	int cnt = 0;
	while (std::getline(ifs, line)) {
		strvec = split(line, ',');
		Note note;
		for (int i = 0; i < strvec.size(); i += strvec.size()) {
			note.time = stof(strvec.at(i));
			note.rane = stoi(strvec.at(i + 1));
			note.isCreate = false;
			g_Notes.push_back(note);
			maxNotes++;
		}
	}
}

void Notes::Draw() {
}

void Notes::Update() {
}

int Notes::GetMaxNotes()
{
	return maxNotes;
}

float Notes::GetNotesTime(int index) {
	return g_Notes[index].time;
}

bool Notes::IsCreateNotes(int index)
{
	return g_Notes.begin()->isCreate;
}

void Notes::Create(int index) {
	g_Notes[m_createLeadNoteNumber].isCreate = true;
//	m_Notes[index].isCreate = true;
	m_createLeadNoteNumber++;
}

void Notes::Destory() {
//	g_Notes.swap(g_Notes.begin, g_Notes.end);
	g_Notes.pop_back();	
}

float Notes::GetCurrentNotesTime() {
	return g_Notes[m_createLeadNoteNumber].time;
}

float Notes::GetFirstNotesTime()
{
	return g_Notes.begin()->time;
}

