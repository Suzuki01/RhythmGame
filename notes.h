#ifndef NOTES_H_
#define NOTES_H_

#include <list>

#define NOTES_MAX	(900)

typedef struct {
	float time;
	int rane;
	bool isCreate;
}Note;

class Notes {
private:
	static std::vector<std::string> split(std::string& input, char delimiter);
	static int maxNotes;
	static Note m_Notes[];
	static int m_playingNoteNumber;
	static int m_createLeadNoteNumber;
public:
	static void Load(char* fileName);
	static void Draw();
	static void Update();
	static int GetMaxNotes();
	static float GetNotesTime(int index);
	static bool IsCreateNotes(int index);
	static void Create(int index);
	static void Destory();
	static float GetCurrentNotesTime();
	static float GetFirstNotesTime();
};

#endif // !NOTES_H_
