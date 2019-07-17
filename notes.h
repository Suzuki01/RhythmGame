#ifndef NOTES_H_
#define NOTES_H_

#define NOTES_MAX	(900)

typedef struct {
	float time;
	int rane;
}Note;

class Notes {
private:
	static std::vector<std::string> split(std::string& input, char delimiter);
	static int maxNotes;
	static Note m_Notes[];
public:
	static void Load(char* fileName);
};

#endif // !NOTES_H_
