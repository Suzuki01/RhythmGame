#ifndef SONG_SELECTION_SCENE_H_
#define SONG_SELECTION_SCENE_H_

#include "main.h"
#include "manager.h"
#include "input.h"
#include "polygon.h"
#include "scene.h"
#include "audio_clip.h"
#include "game_scene.h"
#include "thumbnail.h"
#include "sound.h"
#include "notes.h"



static char* url[] = {
	{"asset/kurumiwari.png"},
	{"asset/oni_jigoku_kama.png"},
};

class SongSelectionScene : public Scene {
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
private:
	typedef enum PHASE_INDEX {
		PHASE_INDEX_START,
		PHASE_INDEX_SELECT,
		PHASE_INDEX_LEVEL_DECISION,
		PHASE_INDEX_OPTION,
		PHASE_INDEX_DECISION,
		PHASE_INDEX_MAX,
	};
	CAudioClip* m_SE;
	int m_level;
	int m_songNumber;
	int m_stage;
	std::list<CPolygon*> m_pPolygon;
	std::list<CPolygon*> m_pThumbnailPolygon;
	std::list<CPolygon*> m_pSelectSongFrame;
	PHASE_INDEX m_Phase;
	int DecisionNumber();
	void SelectSongFrameCreate(int level, int stage, int songNumber);
};

#endif // !SONG_SELECTION_SCENE_H_
