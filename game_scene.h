#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

class GameScene : public Scene {
public:
	void Init();
	void UnInit();
	void Update();
	CAudioClip* m_pBGM;
	//Draw�͋@�\�ǉ�������Ȃ����ߍ쐬���Ă��Ȃ�
	//�p������Draw���Ă΂��
};

enum {
	CameraLayer,
	FieldLayer,
	PlayerLayer,
};

#endif // !GAME_SCENE_H_
