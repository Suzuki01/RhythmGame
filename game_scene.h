#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

class GameScene : public Scene {
private:
	char* m_pFileName;
public:
//	GameScene(char* fileName) : m_pFileName(fileName) {};
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
	BillboardLayer,
};

#endif // !GAME_SCENE_H_
