#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

class GameScene : public Scene {
public:
	void Init();
	void UnInit();
	void Update();
	CAudioClip* m_pBGM;
	//Drawは機能追加が今回ないため作成していない
	//継承元のDrawが呼ばれる
};

enum {
	CameraLayer,
	FieldLayer,
	PlayerLayer,
};

#endif // !GAME_SCENE_H_
