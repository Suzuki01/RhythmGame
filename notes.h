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
#define JUDGMENT_IMAGE_MAX	(20)

struct Note{
	CModel* m_pModel;
	float time;
	int rane;
	bool isCreate;
	bool operator<(const Note& n){
		return time < n.time;
	}
	Note(float time, int rane, bool isCreate) : time(time),rane(rane),isCreate(isCreate){};
//	~Note() { delete m_pModel; };
};

typedef struct {
	BillBoard* billBoard;
	int justiceImageCount;
	bool isDisplay;
}JudgmentImage;

class Notes {
private:
	Notes();
	~Notes();
	static int ID; //Œ»Ý“Ç‚Ýž‚ñ‚Å‚¢‚é•ˆ–Ê‚ÌID
	static std::vector<std::string> split(std::string& input, char delimiter);
	static Note m_Notes1;
	static int m_playingNoteNumber;
	static int m_createLeadNoteNumber[];
	static std::vector<Note*> m_Notes;
	static JudgmentImage judgementImage[JUDGMENT_IMAGE_MAX];
	static void Judgement(int rane);
	static void Perfect(int rane);
	static void Attack(int rane);
	static void Miss(int rane);
	static bool isEnd;
	static int endCount;
	static void SetJusticeImage(int index, int rane);
	static void ResetJusticeImage(int index);
	static void Delete(int rane);
	static void DataSave();
public:
	static bool isEditorMode;
	static void Next();
	static int m_CurrentNoteNum;
	static Note* m_CurrentNoteData;
	static int maxNotes;
	static void Init();
	static void Draw();
	static void UnInit();
	static void Update();
	static void Update(float currentBeats);
	static void Load(int id);
	static int GetMaxNotes();
	static float GetNotesTime(int index);
	static bool IsCreateNotes(int index);
	static void Create(int rane, float time);
	static void Destory();
	static float GetCurrentNotesTime(int rane);
	static float GetFirstNotesTime();
	static bool EndCheck();
	static bool Save();
	static bool CheckNotes(XMFLOAT3 pos,float range,int rane);
	static void DrawCurrentPosition();
/*	bool operator()(Note& n,float posZ, float range) {
		return n.m_pModel->Position.z < posZ + range || n.m_pModel->Position.z > posZ - range;
	}*/
};

#endif // !NOTES_H_
