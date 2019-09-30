#ifndef NOTES_H_
#define NOTES_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <list>
#include "main.h"
#include "game_object.h"
#include "model.h"
#include "bill_board.h"
#include "score.h"
#include "sound.h"
#include "input.h"

#define NOTES_MAX	(900)
#define JUDGMENT_IMAGE_MAX	(3)

typedef struct {
	CModel* m_pModel;
	float time;
	int rane;
	bool isCreate;
}Note;

typedef struct {
	BillBoard* billBoard;
	int justiceImageCount;
	bool isDisplay;
}JudgmentImage;

class Notes {
private:
	static std::vector<std::string> split(std::string& input, char delimiter);
	static int maxNotes;
	static Note m_Notes1;
	static int m_playingNoteNumber;
	static int m_createLeadNoteNumber[];
	static JudgmentImage judgementImage[][JUDGMENT_IMAGE_MAX];
	static int Judgement(int rane);
	static void Perfect(int rane);
	static void Attack(int rane);
	static void Miss(int rane);
	static bool isEnd;
	static int endCount;
	static void SetJusticeImage(int index, int rane);
	static void ResetJusticeImage(int index,int cnt);
	static void Delete(int rane);
	static void DataSave();
public:
	static void Init();
	static void Draw();
	static void UnInit();
	static void Update();
	static void Update(float currentBeats);
	static void Load(int id);
	static int GetMaxNotes();
	static float GetNotesTime(int index);
	static bool IsCreateNotes(int index);
	static void Create(int index);
	static void Destory();
	static float GetCurrentNotesTime(int rane);
	static float GetFirstNotesTime();
	static bool EndCheck();
	
};

#endif // !NOTES_H_
