#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "field.h"
#include "mesh_field.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "notes.h"
#include "polygon.h"
#include "notes_object.h"
#include "bill_board.h"
#include "sound.h"
#include "audio_clip.h"
#include "sound_manager.h"
#include "scene.h"
#include "result_scene.h"
#include "manager.h"
#include "notes.h"
#include "thumbnail.h"
#include "mesh_sky.h"
#include "score.h"



class GameScene : public Scene {
private:
	typedef enum PHASE_INDEX {
		PHASE_INDEX_READY,
		PHASE_INDEX_GO,
		PHASE_INDEX_START,
		PHASE_INDEX_MAX,
	};
	char* m_pFileName;
	PHASE_INDEX m_Phase;
	CPolygon* ready;
	CPolygon* go;
	int count;
public:
//	GameScene(char* fileName) : m_pFileName(fileName) {};
	void Init();
	void UnInit();
	void Update();
	void Draw();
	CAudioClip* m_pBGM;
	//DrawÇÕã@î\í«â¡Ç™ç°âÒÇ»Ç¢ÇΩÇﬂçÏê¨ÇµÇƒÇ¢Ç»Ç¢
	//åpè≥å≥ÇÃDrawÇ™åƒÇŒÇÍÇÈ
};


enum {
	CameraLayer,
	FieldLayer,
	SkyDomeLayer,
	JusticeFieldLayer,
	PlayerLayer,
	BillboardLayer,
	PolygonLayer,
};

#endif // !GAME_SCENE_H_
