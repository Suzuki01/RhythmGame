#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

class GameScene : public Scene {
public:
	void Init();
	void UnInit();
	void Update();
	CAudioClip* m_pBGM;
	//Draw‚Í‹@”\’Ç‰Á‚ª¡‰ñ‚È‚¢‚½‚ßì¬‚µ‚Ä‚¢‚È‚¢
	//Œp³Œ³‚ÌDraw‚ªŒÄ‚Î‚ê‚é
};

enum {
	CameraLayer,
	FieldLayer,
	PlayerLayer,
};

#endif // !GAME_SCENE_H_
